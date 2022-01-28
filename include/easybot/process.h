//
// Created by huhua on 2021/10/5.
//

#ifndef MH_TOOL_PROCESS_H
#define MH_TOOL_PROCESS_H
#include <vector>
#include "./window.h"
#include <easybot/internal/global.h>

namespace eb {
class Process {
 private:
  DWORD pid;

 public:
  static DWORD findProcessId(const std::string &processName);
  static DWORD getBaseAddr(DWORD processId, const std::string &moduleName);
  explicit Process(DWORD pid);

  static DWORD PID_NOT_FOUND;

  /**
   * return pid = 0 if not found
   */
  static Process findByName(const std::string &name);

  std::vector<eb::Window> getWindows(bool ignoreIME = true, bool ignoreToolTips = true);

  // I want design a function that return the biggest window in this process.
  // But how can I do if I don't have any window. Throw an exception?
  eb::Window getBiggestWindow();

  DWORD getPid();
};
}

#endif //MH_TOOL_PROCESS_H
