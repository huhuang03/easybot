//
// Created by huhua on 2021/8/10.
//

#include <easybot/util_string.h>
#include <Windows.h>
#include <iostream>

void eb::printAsHex(const std::string &str) {
    const char* c = str.data();
    while (*c != 0) {
        // how to print as hex?
        printf("%02X", (unsigned char)*c);
        c += 1;
    }
    printf("%02X", *c);
    printf("\n");
}

std::string eb::gbk2utf8(const std::string &src) {
    return eb::gbk2utf8(src.c_str());
}

std::string eb::utf82gbk(const std::string &src) {
    return eb::utf82gbk(src.c_str());
}

std::string eb::gbk2utf8(const char *src) {
    // you can't handle space?
//    std::cout << "begin convert" << std::endl;
//    eb::printAsHex(src);
    // return the wchar_t len.
    int len = MultiByteToWideChar(CP_ACP, 0, src, -1, nullptr, 0);
//    std::cout << "strlen: " << strlen(src) << ", len: " << len << std::endl;
    // wrong len
    auto wstr = new wchar_t[len]{0};
    MultiByteToWideChar(CP_ACP, 0, src, -1, wstr, len);

    // 1-4byte per x
    int lenBuffer = len * 4 + 1;
    auto str = new char[lenBuffer]{0};
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, lenBuffer, nullptr, nullptr);
    std::string rst = str;
    delete[] wstr;
    delete[] str;
    return rst;
}

std::string eb::utf82gbk(const char *src) {
    int len = MultiByteToWideChar(CP_UTF8, 0, src, -1, nullptr, 0);
    auto wstr = new wchar_t[len + 1]{0};
    MultiByteToWideChar(CP_UTF8, 0, src, -1, wstr, len);

    // 1-4byte per x
    int lenBuffer = len * 4 + 1;
    auto str = new char[lenBuffer]{0};
    WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, lenBuffer, nullptr, nullptr);
    std::string rst = str;
    delete[] wstr;
    delete[] str;
    return rst;
}

