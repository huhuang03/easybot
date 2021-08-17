//
// Created by huhua on 2021/8/9.
//
#include <gtest/gtest.h>
#include <easybot/util_process.h>
#include <easybot/util_window.h>
#include <iostream>

static void startNotepad(PROCESS_INFORMATION *ppi) {
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

/**
 * let use the compiler sugar.
 */
static PROCESS_INFORMATION startNotepad() {
    PROCESS_INFORMATION pi;
    ZeroMemory( &pi, sizeof(pi) );
    startNotepad(&pi);
    return pi;
}

static void stopNotepad(PROCESS_INFORMATION &pi) {
    TerminateProcess(pi.hProcess, 0);
}


TEST(UtilWindow, getProcessId) {
    DWORD id = eb::findProcessId("svchost.exe");
    ASSERT_TRUE(id > 0);
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

TEST(UtilProcess, getModuleBase) {
    auto pi = startNotepad();

    auto pid = eb::findProcessId("notepad.exe");
    ASSERT_TRUE(pid > 0);
    auto baseAddr = eb::getBaseAddr(pid, "notepad.exe");
    std::cout << "baseAddr: " << baseAddr << std::endl;
    ASSERT_GT(baseAddr, 0);

    stopNotepad(pi);
}
