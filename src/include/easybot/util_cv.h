//
// Created by huhua on 2021/8/25.
//

#ifndef EASYBOT_UTIL_CV_H
#define EASYBOT_UTIL_CV_H

#include <opencv2/opencv.hpp>
#include <Windows.h>

namespace eb {
    cv::Rect2i rectWin2cv(const RECT &rect);

    RECT rectCv2win(const cv::Rect2i &rect);
}

#endif //EASYBOT_UTIL_CV_H