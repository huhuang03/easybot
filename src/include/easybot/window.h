//
// Created by huhua on 2021/8/25.
//

#ifndef EASYBOT_WINDOW_H
#define EASYBOT_WINDOW_H

#include <Windows.h>
#include <string>
#include <opencv2/opencv.hpp>
#include <vector>

namespace eb {
    class Window {
    private:
        const static std::vector<std::string> VISIBLE_IGNORE_CLASS;
    public:
        std::string title;
        std::string className;
        cv::Rect2i rect;
        HWND hwnd;

        Window(HWND hwnd);

        void refresh();

        // A window that has no parent, or whose parent is the desktop window, is called a top-level window.
        bool isTopLevel();

        static std::vector<Window> getTopVisibleWindows();

        std::string str();

        bool isVisible();

        // https://devblogs.microsoft.com/oldnewthing/20200302-00/?p=103507
        bool isCloaked();
    };
}


#endif //EASYBOT_WINDOW_H
