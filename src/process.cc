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
}
