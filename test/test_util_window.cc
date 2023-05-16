//
// Created by huhua on 2021/8/9.
//
#include <gtest/gtest.h>
#include "easybot/process.h"
#include "easybot/window.h"
#include "easybot/util/util_keyboard.h"
#include <iostream>
#include "util_test.h"

TEST(UtilWindow, getProcessId) {
  auto pid = eb::Process::findPidByName("svchost.exe");
  ASSERT_TRUE(pid > 0);
}

//TEST(UtilWindow, findWindow) {
//  auto handler = startNotepad();
//  // ok, can we start the notepad?
//  HWND window = eb::findWindow("notepad.exe", "无标题 - 记事本");
//  std::cout << "window: " << window << std::endl;
//  ASSERT_TRUE(window != nullptr);
//  stopNotepad(handler);
//}

//TEST(UtilProcess, getModuleBase) {
//  auto pi = startNotepad();
//
//  auto pid = eb::Process::findPidByName("notepad.exe");
//  ASSERT_TRUE(pid > 0);
//  auto baseAddr = eb::getBaseAddr(pid, "notepad.exe");
//  std::cout << "baseAddr: " << baseAddr << std::endl;
//  ASSERT_GT(baseAddr, 0);
//
//  stopNotepad(pi);
//}

TEST(UtilWindow, capture) {
  auto pi = startNotepad();
  // ok, can we start the notepad?
  // 黑屏，明天看看问题吧。
  eb::Window out(nullptr);
  eb::Window::findWindow(&out, "无标题 - 记事本");
  eb::inputKey('A');
  eb::inputKey('B');
  Sleep(500);
//  ASSERT_TRUE(window != nullptr);
  cv::Mat mat;
  out.screenshot(mat);
//  eb::screenshot(window, mat);
  cv::imshow("img", mat);
  cv::waitKey(0);
  // how to assert you?
//  auto lastColor = mat.at<cv::Vec4b>(mat.rows - 1, mat.cols - 1);
//  ASSERT_TRUE(lastColor[0] != 255 && lastColor[0] != 0);
//  cv::waitKey(0);
//  ASSERT_TRUE(window != nullptr);
//  stopNotepad(pi);
}
