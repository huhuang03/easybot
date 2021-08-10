//
// Created by huhua on 2021/8/10.
//

#ifndef EASYBOT_UTIL_STRING_H
#define EASYBOT_UTIL_STRING_H

#include <string>

namespace eb {
    void printAsHex(const std::string& str);

    std::string gbk2utf8(const char *src);
    std::string utf82gbk(const char *str);
    std::string gbk2utf8(const std::string &src);
    std::string utf82gbk(const std::string &src);
}

#endif //EASYBOT_UTIL_STRING_H
