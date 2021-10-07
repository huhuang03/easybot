//
// Created by huhua on 2021/8/9.
//
#include <gtest/gtest.h>
#include <easybot/util_process.h>
#include <easybot/util_window.h>
#include <easybot/util_keyboard.h>
#include <iostream>
#include "util_test.h"



TEST(UtilWindow, getProcessId) {
    DWORD id = eb::findProcessId("svchost.exe");
    ASSERT_TRUE(id > 0);
}



TEST(UtilWindow, findWindow) {
    auto handler = startNotepad();
    // ok, can we start the notepad?
    HWND window = eb::findWindow("notepad.exe", "无标题 - 记事本");
    std::cout << "window: " << window << std::endl;
    ASSERT_TRUE(window != nullptr);
    stopNotepad(handler);
}

TEST(UtilProcess, getModuleBase) {
    auto pi = startNotepad();

    auto pid = eb::findProcessId("notepad.exe");
    ASSERT_TRUE(pid > 0);
    auto baseAddr = eb::getBaseAddr(pid, "notepad.exe");
    std::cout << "baseAddr: " << baseAddr << std::endl;
    ASSERT_GT(baseAddr, 0);

    stopNotepad(pi);
}

TEST(UtilWindow, capture) {
    auto pi = startNotepad();
    // ok, can we start the notepad?
    // 黑屏，明天看看问题吧。
    HWND window = eb::findWindow("无标题 - 记事本");
    eb::inputKey('A');
    eb::inputKey('B');
    Sleep(500);
    ASSERT_TRUE(window != nullptr);
    cv::Mat mat;
    eb::screenshot(window, mat);
    cv::imshow("img", mat);
    // cv::waitKey(0);
    // how to assert you?
    auto lastColor = mat.at<cv::Vec4b>(mat.rows - 1, mat.cols - 1);
    ASSERT_TRUE(lastColor[0] != 255 && lastColor[0] != 0);
    cv::waitKey(0);
    ASSERT_TRUE(window != nullptr);
    stopNotepad(pi);
}
