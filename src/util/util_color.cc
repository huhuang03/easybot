//
// Created by huhua on 2021/8/14.
//

#include "easybot/util/util_color.h"

std::string eb::color_str(COLORREF c) {
  return "Color(r=" + std::to_string((int) GetRValue(c))
      + ", g=" + std::to_string((int) GetGValue(c))
      + ", b=" + std::to_string((int) GetBValue(c))
      + ")";
}
