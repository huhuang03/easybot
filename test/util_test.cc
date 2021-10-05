//
// Created by huhua on 2021/10/5.
//
#include <iostream>
#include "./util_test.h"

HANDLE startNotepad() {
    PROCESS_INFORMATION pi;

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
            &pi
    );
    std::cout << "createRst: " << createRst << std::endl;
    if (!createRst) {
        std::cout << "code: " << GetLastError() << std::endl;
    }
    WaitForSingleObject(pi.hProcess, 1000);
    return pi.hProcess;
}

void stopNotepad(HANDLE handle) {
    TerminateProcess(handle, 0);
}

