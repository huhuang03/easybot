//
// Created by huhua on 2021/8/25.
//
#include "easybot/util/util_cv.h"


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
cv::Rect2i eb::rectWin2cv(const RECT &rect) {
  cv::Rect2i rst;
  rst.x = rect.left;
  rst.width = rect.right - rect.left;
  rst.y = rect.top;
  rst.height = rect.bottom - rect.top;
  return rst;
}

RECT eb::rectCv2win(const cv::Rect2i &rect) {
  return RECT{rect.x, rect.y, rect.x + rect.width, rect.y + rect.height};
}

std::string eb::to_string(const RECT &rect) {
  return "Rect(" + std::to_string(rect.left) + "," + std::to_string(rect.top)
      + " - " + std::to_string(rect.right - rect.left) + "x" + std::to_string(rect.bottom - rect.top)
      + ")";
}
#endif

std::string eb::to_string(const cv::Rect2i &rect) {
  return "Rect(" + std::to_string(rect.x) + "," + std::to_string(rect.y)
      + " - " + std::to_string(rect.width) + "x" + std::to_string(rect.height)
      + ")";
}

