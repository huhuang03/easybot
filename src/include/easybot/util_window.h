//
// Created by huhua on 2021/8/9.
//

#ifndef EASYBOT_UTIL_WINDOW_H
#define EASYBOT_UTIL_WINDOW_H
#include <Windows.h>
#include <string>

namespace eb {
    HWND findWindow(const std::string &windowName);

    /**
     * Find first window match the processName and windowName exactly
     * Caller close the resource.
     * @param processName the processName, pass "" will search for all process.
     * @param windowName the windowName
     * @return nullptr if not find.
     */
    HWND findWindow(const std::string& processName, std::string windowName);

    DWORD findProcessId(const std::string &processName);
}
#endif //EASYBOT_UTIL_WINDOW_H
