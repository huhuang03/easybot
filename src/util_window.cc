//
// Created by huhua on 2021/8/9.
//

#include "include/util_window.h"
#include <TlHelp32.h>

static bool enumFindWindow() {

}

HWND eb::findWindow(std::string processName, std::string windowName) {
    auto thSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (!thSnap) {
        return nullptr;
    }
    PROCESSENTRY32 pe;

    if (!Process32Next(thSnap, &pe)) {
        return nullptr;
    }

    do {
        if (processName == pe.szExeFile) {
            // ok, we find the process
            // but how can we get the window?
        }
    } while (Process32Next(thSnap, &pe));

    CloseHandle(thSnap);
    return nullptr;
}

