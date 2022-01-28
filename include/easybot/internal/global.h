//
// Created by th on 2022/1/27.
//

#ifndef EASYBOT_GLOBAL_H
#define EASYBOT_GLOBAL_H

#define IS_WIN defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#else
#define DWORD long
#endif

#endif //EASYBOT_GLOBAL_H
