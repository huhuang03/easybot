//
// Created by huhua on 2021/8/25.
//

#include "window.h"
#include <easybot/util_cv.h>

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
