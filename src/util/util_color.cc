//
// Created by huhua on 2021/8/14.
//

#include "easybot/util/util_color.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
std::string eb::color_str(COLORREF c) {
  return "Color(r=" + std::to_string((int) GetRValue(c))
      + ", g=" + std::to_string((int) GetGValue(c))
      + ", b=" + std::to_string((int) GetBValue(c))
      + ")";
}
#endif