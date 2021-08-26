//
// Created by huhua on 2021/8/25.
//

#ifndef EASYBOT_WINDOW_H
#define EASYBOT_WINDOW_H

#include <Windows.h>
#include <string>
#include <opencv2/opencv.hpp>

namespace eb {
    class Window {
    public:
        std::string title;
        cv::Rect2i rect;
        HWND hwnd;

        Window(HWND hwnd);

        void refresh();
    };
}


#endif //EASYBOT_WINDOW_H
