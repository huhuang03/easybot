//
// Created by huhua on 2021/8/9.
//

#ifndef EASYBOT_UTIL_WINDOW_H
#define EASYBOT_UTIL_WINDOW_H
#include <Windows.h>
#include <string>

namespace eb {
    /**
     * Find first window match the processName and windowName exactly
     * Caller close the resource.
     * @param processName the processName
     * @param windowName the windowName
     * @return nullptr if not find.
     */
    HWND findWindow(std::string processName, std::string windowName);

    int findProcessId(const std::string &processName);
}
#endif //EASYBOT_UTIL_WINDOW_H
