//
// Created by huhua on 2021/8/9.
//

#include "easybot/util_window.h"
#include <TlHelp32.h>
#include <iostream>
#include <easybot/util_string.h>


static struct ParamEnumFindWindow {
    DWORD processId;
    std::string *windowName;
    HWND *hwnd = nullptr;
};

static BOOL enumFindWindow(HWND hwnd, LPARAM param) {
    // hwo to do?
    char title[1024];
    auto* config = (ParamEnumFindWindow*)param;
    GetWindowText(hwnd, (LPSTR)&title, 1023);
    DWORD processId;
    GetWindowThreadProcessId(hwnd, &processId);

    if (config->processId == processId
        && ((title == *config->windowName) || (eb::gbk2utf8(title) == *config->windowName))) {
        // how to let the window open?
        *config->hwnd = hwnd;
        return false;
    }
    return true;
}

HWND eb::findWindow(const std::string& processName, std::string windowName) {
    auto thSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (!thSnap) {
        return nullptr;
    }
    PROCESSENTRY32 pe;

    // need close pe?
    if (!Process32Next(thSnap, &pe)) {
        return nullptr;
    }

    const bool ignoreName= processName.empty();

    HWND rst = nullptr;
    do {
        if (ignoreName || processName == pe.szExeFile) {
            // ok, we find the process
            // but how can we get the window?
            struct ParamEnumFindWindow param {
                pe.th32ProcessID,
                &windowName,
                &rst
            };
            EnumWindows(enumFindWindow, reinterpret_cast<LPARAM>(&param));
        }
    } while (Process32Next(thSnap, &pe));

    CloseHandle(thSnap);
    return rst;
}

/**
 * Strange, I remember I have write this method once?
 * @param processName
 * @return
 */
DWORD eb::findProcessId(const std::string &processName) {
    auto thSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (!thSnap) {
        return 0;
    }
    PROCESSENTRY32 pe;

    // need close pe?
    if (!Process32Next(thSnap, &pe)) {
        return 0;
    }

    do {
        if (processName == pe.szExeFile) {
            CloseHandle(thSnap);
            return pe.th32ProcessID;
        }
    } while (Process32Next(thSnap, &pe));

    CloseHandle(thSnap);
    return 0;
}

HWND eb::findWindow(const std::string &windowName) {
    return eb::findWindow("", windowName);
}

