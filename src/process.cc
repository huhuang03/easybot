//
// Created by huhua on 2021/10/5.
//

#include <easybot/process.h>
#include <easybot/util_process.h>

namespace eb {
    DWORD Process::PID_NOT_FOUND = 0;

    eb::Process Process::findByName(const std::string &name) {
        return eb::Process(findProcessId(name));
    }

    DWORD Process::getPid() {
        return this->pid;
    }

    Process::Process(DWORD pid): pid(pid) {}

    struct EnumWindowsGetWindowsParam {
        std::vector<eb::Window> *rst;
        DWORD pid;
    };

    static BOOL CALLBACK enumWindowsGetWindows(HWND hwnd, LPARAM param) {
        auto* config = (EnumWindowsGetWindowsParam*)param;
        DWORD processId;
        GetWindowThreadProcessId(hwnd, &processId);
        if (processId == config->pid) {
            // throw exception at here?
            config->rst->push_back(eb::Window(hwnd));
        }
        return TRUE;
    }

    std::vector<eb::Window> Process::getWindows() {
        std::vector<eb::Window> rst;
        if (this->pid == PID_NOT_FOUND) {
            return rst;
        }

        struct EnumWindowsGetWindowsParam param {
            &rst,
            this->pid,
        };
        EnumWindows(enumWindowsGetWindows, reinterpret_cast<LPARAM>(&param));
        return rst;
    }

    eb::Window Process::getBiggestWindow() {
        if (this->pid == PID_NOT_FOUND) {
            throw std::runtime_error("Process id is 0");
        }

        auto windows = this->getWindows();
        if (windows.empty()) {
            throw std::runtime_error("Has no any window in Process::getBiggestWindow");
        }
        auto rst = windows[0];
        for (const auto &window: windows) {
            if (window.rect.width > rst.rect.width) {
                rst = window;
            }
        }
        return rst;
    }
}
