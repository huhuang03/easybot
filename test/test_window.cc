//
// Created by huhua on 2021/8/27.
//

#include <gtest/gtest.h>
#include <easybot/util_process.h>
#include <iostream>
#include <easybot/window.h>

TEST(WindowTest, getTopVisibleWindow) {
    auto windows = eb::Window::getTopVisibleWindows();
    // what this & means?
    for (auto &window: windows) {
        std::cout << "window: " << window.title << std::endl;
    }
}
