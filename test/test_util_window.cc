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

void startNotepad(PROCESS_INFORMATION *ppi) {
    STARTUPINFO si;
    si.cb = sizeof (si);
    ZeroMemory( &si, sizeof(si) );
    auto createRst = CreateProcess(
            R"(C:\WINDOWS\system32\notepad.exe)",
            nullptr,
            nullptr,
            nullptr,
            false,
            0,
            nullptr,
            nullptr,
            &si,
            ppi
            );
    std::cout << "createRst: " << createRst << std::endl;
    if (!createRst) {
        std::cout << "code: " << GetLastError() << std::endl;
    }
    WaitForSingleObject(ppi->hProcess, 1000);
}


TEST(UtilWindow, findWindow) {
    PROCESS_INFORMATION pi;
    ZeroMemory( &pi, sizeof(pi) );
    startNotepad(&pi);
    // ok, can we start the notepad?
    HWND window = eb::findWindow("notepad.exe", "无标题 - 记事本");
    std::cout << "window: " << window << std::endl;
    ASSERT_TRUE(window != nullptr);
    TerminateProcess(pi.hProcess, 0);
}
