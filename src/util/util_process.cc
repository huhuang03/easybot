//
// Created by huhua on 2021/8/15.
//

#include "easybot/util/util_process.h"
#include <TlHelp32.h>
#include <iostream>

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


