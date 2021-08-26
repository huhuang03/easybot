//
// Created by huhua on 2021/8/25.
//
#include "easybot/util_cv.h"

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

