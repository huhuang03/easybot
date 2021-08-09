//
// Created by huhua on 2021/8/9.
//

#ifndef EASYBOT_UTIL_WINDOW_H
#define EASYBOT_UTIL_WINDOW_H
#include <Windows.h>
#include <string>

namespace eb {
HWND findWindow(std::string processName, std::string windowName);
}
#endif //EASYBOT_UTIL_WINDOW_H
