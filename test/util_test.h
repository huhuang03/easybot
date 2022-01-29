//
// Created by huhua on 2021/10/5.
//

#ifndef EASYBOT_UTIL_TEST_H
#define EASYBOT_UTIL_TEST_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <Windows.h>

HANDLE startNotepad();
void stopNotepad(HANDLE handle);
#endif
#endif //EASYBOT_UTIL_TEST_H
