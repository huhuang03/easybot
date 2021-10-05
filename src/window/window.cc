//
// Created by huhua on 2021/8/25.
//

#include "easybot/window.h"
#include <easybot/util_cv.h>
#include <dwmapi.h>

// yes, I think this go in program
// Program is the class name of Program Manager
const std::vector<std::string> eb::Window::VISIBLE_IGNORE_CLASS{"Progman"};

eb::Window::Window(HWND hwnd): hwnd(hwnd) {
    this->refresh();
}

void eb::Window::refresh() {
    this->title = this->getTitle();

    RECT r;
    GetWindowRect(this->hwnd, &r);
    this->rect = rectWin2cv(r);

    TCHAR cName[MAX_PATH + 1];
    GetClassName(hwnd, cName, _countof(cName));
    this->className = std::string(cName);
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

std::string eb::Window::str() const {
    return "Window(title: " + this->title + ", rect: " + eb::to_string(this->rect) + ")";
}

bool eb::Window::isCloaked() const {
    BOOL isCloaked = FALSE;
    return SUCCEEDED(DwmGetWindowAttribute(hwnd,  DWMWA_CLOAKED,
                                            &isCloaked, sizeof(isCloaked))) && isCloaked;
}

bool eb::Window::isVisible() const {
    if (this->isCloaked()) {
        return false;
    }
    if (std::count(Window::VISIBLE_IGNORE_CLASS.begin(), Window::VISIBLE_IGNORE_CLASS.end(), this->className)) {
        return false;
    }
    if (this->rect.width == 0 || this->rect.height == 0) {
        return false;
    }
    return !IsIconic(hwnd) && IsWindowVisible(hwnd);
}

std::string eb::Window::getTitle() {
    auto len = GetWindowTextLength(hwnd);
    auto pszMem = (PSTR) VirtualAlloc((LPVOID) NULL,
                                      (DWORD) (len + 1), MEM_COMMIT,
                                      PAGE_READWRITE);
    GetWindowText(hwnd, pszMem,
                  len + 1);
    auto rst = std::string(pszMem);
    VirtualFree(pszMem, (DWORD)(len + 1), MEM_DECOMMIT);
    return rst;
}

void eb::Window::screenShot(const cv::_OutputArray &output) {
}

std::ostream &eb::operator<<(std::ostream &out, const eb::Window &window) {
    out << window.str();
    return out;
}