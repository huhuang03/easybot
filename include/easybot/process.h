//
// Created by huhua on 2021/10/5.
//

#ifndef MH_TOOL_PROCESS_H
#define MH_TOOL_PROCESS_H
#include <vector>
#include "./window.h"
#include <easybot/internal/global.h>

#ifdef __APPLE__
#include <libproc.h>
#else
#define pid_t DWORD
#endif

namespace eb {
class Process {
 private:
  pid_t pid;

 public:
  static DWORD findProcessId(const std::string &processName);

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
  static DWORD getBaseAddr(DWORD processId, const std::string &moduleName);
#endif

  explicit Process(pid_t pid);

  static pid_t PID_NOT_FOUND;

  /**
   * return pid = 0 if not found
   */
  static Process findByName(const std::string &name);

  std::vector<eb::Window> getWindows(bool ignoreIME = true, bool ignoreToolTips = true);

  // I want design a function that return the biggest window in this process.
  // But how can I do if I don't have any window. Throw an exception?
  eb::Window getBiggestWindow();

  pid_t getPid();
};
}

#endif //MH_TOOL_PROCESS_H
