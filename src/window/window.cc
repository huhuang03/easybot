//
// Created by huhua on 2021/8/25.
//

#include "easybot/window.h"
#include <easybot/util_cv.h>
#include <dwmapi.h>

eb::Window::Window(HWND hwnd): hwnd(hwnd) {
    this->refresh();
}

void eb::Window::refresh() {
    auto len = GetWindowTextLength(hwnd);
    auto pszMem = (PSTR) VirtualAlloc((LPVOID) NULL,
                                      (DWORD) (len + 1), MEM_COMMIT,
                                      PAGE_READWRITE);
    GetWindowText(hwnd, pszMem,
                  len + 1);
    this->title = std::string(pszMem);
    VirtualFree(pszMem, (DWORD)(len + 1), MEM_DECOMMIT);

    RECT r;
    GetWindowRect(this->hwnd, &r);
    this->rect = rectWin2cv(r);
}

static BOOL WINAPI enumWindowGetTopVisibleWindows(HWND hwnd, LPARAM param) {
    auto *windows = (std::vector<eb::Window>*)param;
    // should I check?
    // I still can't find the top level window.
    // A window that has no parent, or whose parent is the desktop window, is called a top-level window.
    auto window = eb::Window(hwnd);

    // For now we don't check screen region because it seems need check many screen.
    if (window.isTopLevel() && window.isVisible()) {
        windows->push_back(window);
    }
    return true;
}

std::vector<eb::Window> eb::Window::getTopVisibleWindows() {
    auto rst = std::vector<Window>();
    EnumWindows(enumWindowGetTopVisibleWindows, (LPARAM)&rst);
    return rst;
}

bool eb::Window::isTopLevel() {
    return this->hwnd ==GetAncestor(this->hwnd,GA_ROOT);
}

std::string eb::Window::str() {
    return "not impl";
}

bool eb::Window::isCloaked() {
    BOOL isCloaked = FALSE;
    return SUCCEEDED(DwmGetWindowAttribute(hwnd,  DWMWA_CLOAKED,
                                            &isCloaked, sizeof(isCloaked))) && isCloaked;
}

bool eb::Window::isVisible() {
    if (this->isCloaked()) {
        return false;
    }
    return !IsIconic(hwnd) && IsWindowVisible(hwnd);
}
