//
// Created by huhua on 2021/8/15.
//

#include <easybot/util_keyboard.h>
#include <Windows.h>

void eb::clickMouseLeft() {
    INPUT input{0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &input, sizeof(input));
    ZeroMemory(&input, sizeof(input));

    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &input, sizeof(input));
}

void eb::inputKey(char c) {
    INPUT input{0};
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = VkKeyScanA(c);
    SendInput(1, &input, sizeof input);

    ZeroMemory(&input, sizeof input);
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = VkKeyScanA(c);
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof input);
}
