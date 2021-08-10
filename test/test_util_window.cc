//
// Created by huhua on 2021/8/9.
//
#include <gtest/gtest.h>
#include <util_window.h>
#include <iostream>

TEST(UtilWindow, getProcessId) {
    DWORD id = eb::findProcessId("svchost.exe");
    ASSERT_TRUE(id > 0);
}

TEST(UtilWindow, findWindow) {
    HWND window = eb::findWindow("notepad.exe", "无标题 - 记事本");
    std::cout << "window: " << window << std::endl;
}
