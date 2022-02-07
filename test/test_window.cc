//
// Created by huhua on 2021/8/27.
//

#include <gtest/gtest.h>
#include <iostream>
#include <easybot/window.h>
#include <easybot/process.h>

TEST(WindowTest, printAllWindows) {
  eb::Window::printAllWindow();
}

TEST(WindowTest, snapshot) {
  auto p = eb::Process::findByName("TextEdit");
  auto window = p.getBiggestWindow();
  cv::Mat mat;
  window.screenshot(mat);
}

TEST(WindowTest, getTopVisibleWindow) {
//  auto windows = eb::Window::getTopVisibleWindows();
//  // what this & means?
//  for (auto &window : windows) {
//    std::cout << "window: " << window.title
//              << ", hwnd: " << window.hwnd << ", className: " << window.className
//              << ", rect: " << window.rect
//              << std::endl;
//  }
}
