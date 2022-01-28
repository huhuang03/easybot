//
// Created by huhua on 2021/8/14.
//

#ifndef ZUMA_BOT_UTIL_COLOR_H
#define ZUMA_BOT_UTIL_COLOR_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <Windows.h>
#endif
#include <string>

namespace eb {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
std::string color_str(COLORREF c);
#endif
}

#endif //ZUMA_BOT_UTIL_COLOR_H
