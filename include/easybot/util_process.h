//
// Created by huhua on 2021/8/15.
//

#ifndef EASYBOT_UTIL_PROCESS_H
#define EASYBOT_UTIL_PROCESS_H
#include <string>
#include <Windows.h>

namespace eb {
    DWORD findProcessId(const std::string &processName);
    DWORD getBaseAddr(DWORD processId, const std::string &moduleName);
}
#endif //EASYBOT_UTIL_PROCESS_H
