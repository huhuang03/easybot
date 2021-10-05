//
// Created by huhua on 2021/10/5.
//

#include <easybot/process.h>
#include <easybot/util_process.h>

namespace eb {
    Process::PID_NOT_FOUND = 0;

    Process Process::findByName(const std::string &name) {
        return Process(findProcessId(name))
    }

    Process(DWORD pid): pid(pid) { }

    DWORD Process::getPid() {
        return this->pid;
    }
}
