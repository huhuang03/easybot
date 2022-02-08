//
// Created by huhua on 2021/10/5.
//

#include "easybot/process.h"
#include <string>
#ifdef __APPLE__
#include <libproc.h>
#endif

namespace eb {
pid_t Process::PID_NOT_FOUND = 0;

eb::Process Process::findByName(const std::string &name) {
  return eb::Process(findPidByName(name));
}

pid_t Process::getPid() {
  return this->pid;
}

Process::Process(pid_t pid) : pid(pid) {}

struct EnumWindowsGetWindowsParam {
  std::vector<eb::Window> *rst;
  DWORD pid;
};

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

/**
 * Strange, I remember I have write this method once?
 * @param processName
 * @return
 */
DWORD eb::findProcessId(const std::string &processName) {
  auto thSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  if (!thSnap) {
    return 0;
  }
  PROCESSENTRY32 pe;

  // need close pe?
  if (!Process32Next(thSnap, &pe)) {
    CloseHandle(thSnap);
    return 0;
  }

  do {
    if (processName == pe.szExeFile) {
      CloseHandle(thSnap);
      return pe.th32ProcessID;
    }
  } while (Process32Next(thSnap, &pe));

  CloseHandle(thSnap);
  return 0;
}

DWORD eb::getBaseAddr(DWORD processId, const std::string &moduleName) {
  if (processId <= 0) {
    return 0;
  }
  // ok, let's do the logic
  auto thSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE32 | TH32CS_SNAPMODULE, processId);
  if (!thSnap) {
    std::cout << "why thSnap is empty" << std::endl;
    return 0;
  }

  MODULEENTRY32 me{0};
  me.dwSize = sizeof(MODULEENTRY32);
  // need close pe?
  if (!Module32First(thSnap, &me)) {
    CloseHandle(thSnap);
    return 0;
  }

  DWORD rst = 0;
  do {
    if (moduleName == me.szModule) {
      CloseHandle(thSnap);
      rst = reinterpret_cast<DWORD>(me.modBaseAddr);
      break;
    }
  } while (Module32Next(thSnap, &me));

  CloseHandle(thSnap);
  return rst;
}

static BOOL CALLBACK enumWindowsGetWindows(HWND hwnd, LPARAM param) {
  auto *config = (EnumWindowsGetWindowsParam *) param;
  DWORD processId;
  GetWindowThreadProcessId(hwnd, &processId);
  if (processId == config->pid) {
    // throw exception at here?
    config->rst->push_back(eb::Window(hwnd));
  }
  return TRUE;
}
#endif

std::vector<eb::Window> Process::getWindows(bool ignoreIME, bool ignoreToolTips) {
  std::vector<eb::Window> allWindows;
  if (this->pid == PID_NOT_FOUND) {
    return allWindows;
  }

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
  struct EnumWindowsGetWindowsParam param{
      &allWindows,
      this->pid,
  };
  EnumWindows(enumWindowsGetWindows, reinterpret_cast<LPARAM>(&param));

  // remove or copy??
  std::vector<eb::Window> rst;
  for (const auto &w : allWindows) {
    if (ignoreIME) {
      if (w.title == eb::Window::TITLE_MSCTFIME_UI
          || w.title == eb::Window::TITLE_DEFAULT_IME) {
        continue;
      }
    }
    if (ignoreToolTips) {
      if (w.className == "tooltips_class32") {
        continue;
      }
    }
    rst.push_back(w);
  }
  return rst;
#endif

  auto windowList = CGWindowListCopyWindowInfo(kCGWindowListOptionOnScreenOnly, kCGNullWindowID);
//  std::cout << "pid: " << this->pid << std::endl;
  for (auto i = 0; i < CFArrayGetCount(windowList); i++) {
    // how to do?
    auto item = (CFDictionaryRef)CFArrayGetValueAtIndex(windowList, i);
    pid_t _pid;
    CFNumberGetValue((CFNumberRef)CFDictionaryGetValue(item, kCGWindowOwnerPID),
                     kCFNumberSInt32Type, &_pid);
    if (_pid == this->pid) {
      CGWindowID wid;
      CFNumberGetValue((CFNumberRef)CFDictionaryGetValue(item, kCGWindowNumber),
                       kCFNumberSInt32Type, &wid);
      allWindows.emplace_back(wid);
    }
  }
  CFRelease(windowList);
  return allWindows;
}

eb::Window Process::getBiggestWindow() {
  if (this->pid == PID_NOT_FOUND) {
    throw std::runtime_error("Process id is 0");
  }

  auto windows = this->getWindows();
  if (windows.empty()) {
    throw std::runtime_error("Has no any window in Process::getBiggestWindow");
  }

  auto rst = windows[0];
  for (const auto &window : windows) {
    // so this has a copy construct
    rst = window;
  }
  return rst;
}

pid_t Process::findPidByName(const std::string &name) {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
  auto thSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  if (!thSnap) {
    return 0;
  }
  PROCESSENTRY32 pe;

  // need close pe?
  if (!Process32Next(thSnap, &pe)) {
    CloseHandle(thSnap);
    return 0;
  }

  do {
    if (processName == pe.szExeFile) {
      CloseHandle(thSnap);
      return pe.th32ProcessID;
    }
  } while (Process32Next(thSnap, &pe));

  CloseHandle(thSnap);
  return 0;
#endif

  pid_t pids[1024];
  int bytes = proc_listallpids(pids, sizeof(pids));
  int nProc = bytes / int(sizeof(pids[0]));
  for (int i = 0; i < nProc; i++) {
    struct proc_bsdinfo proc{};
    int st = proc_pidinfo(pids[i], PROC_PIDTBSDINFO, 0,
                          &proc, PROC_PIDTBSDINFO_SIZE);
    if (st == PROC_PIDTBSDINFO_SIZE) {
//      std::cout << "proc name: " << proc.pbi_name << std::endl;
      if (std::strcmp(name.c_str(), proc.pbi_name) == 0) {
        return pids[i];
      }
    }
  }

  return Process::PID_NOT_FOUND;
}

void Process::printAllProcess() {
  int length = 1024;
  auto pids = new pid_t[length];
  int bytes = proc_listallpids(pids, length * sizeof(pids[0]));
  
  while (bytes >= length) {
    length *= 2;
    delete []pids;

    pids = new pid_t[length];
    bytes = proc_listallpids(pids, length * sizeof(pids[0]));
  }

  if (bytes > 0) {
    int nProc = bytes / int(sizeof(pids[0]));
    std::cout << "Process(" << nProc << ")" << ": " << nProc << std::endl;
    for (int i = 0; i < nProc; i++) {
      struct proc_bsdinfo proc{};
      int st = proc_pidinfo(pids[i], PROC_PIDTBSDINFO, 0,
                            &proc, PROC_PIDTBSDINFO_SIZE);
      std::cout << "id: " << pids[i] << ", ";
      if (st == PROC_PIDTBSDINFO_SIZE) {
        std::cout << "comm: " << proc.pbi_comm << ", ";
        std::cout << "name: " << proc.pbi_name << std::endl;
      } else {
        std::cout << "size: " << st << std::endl;
      }
    }
  }
  delete []pids;
}

}
