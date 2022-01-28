//
// Created by huhua on 2021/10/5.
//

#include <easybot/process.h>

namespace eb {
DWORD Process::PID_NOT_FOUND = 0;

eb::Process Process::findByName(const std::string &name) {
  return eb::Process(findProcessId(name));
}

DWORD Process::getPid() {
  return this->pid;
}

Process::Process(DWORD pid) : pid(pid) {}

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

  struct EnumWindowsGetWindowsParam param{
      &allWindows,
      this->pid,
  };
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
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
    if (window.rect.width > rst.rect.width) {
      rst = window;
    }
  }
  return rst;
}
}
