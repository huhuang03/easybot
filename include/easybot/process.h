//
// Created by huhua on 2021/10/5.
//

#ifndef MH_TOOL_PROCESS_H
#define MH_TOOL_PROCESS_H
#include <vector>
#include "./window.h"

namespace eb {
    class Process {
    private:
        DWORD pid;

    public:
        explicit Process(DWORD pid);

        static DWORD PID_NOT_FOUND;
        /**
         * return pid = 0 if not found
         */
        static Process findByName(const std::string &name);

        std::vector<eb::Window> getWindows();

        DWORD getPid();
    };
}

#endif //MH_TOOL_PROCESS_H
