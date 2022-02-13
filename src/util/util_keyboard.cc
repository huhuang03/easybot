//
// Created by huhua on 2021/8/15.
//

#include "easybot/util/util_keyboard.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <windows.h>
#endif

void eb::clickMouseLeft() {
  #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
  INPUT input{0};
  input.type = INPUT_MOUSE;
  input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
  SendInput(1, &input, sizeof(input));
  ZeroMemory(&input, sizeof(input));

  input.type = INPUT_MOUSE;
  input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
  SendInput(1, &input, sizeof(input));
  #endif
}

void eb::inputKey(char c) {
  #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
  INPUT input{0};
  input.type = INPUT_KEYBOARD;
  input.ki.wVk = VkKeyScanA(c);
  SendInput(1, &input, sizeof input);

  ZeroMemory(&input, sizeof input);
  input.type = INPUT_KEYBOARD;
  input.ki.wVk = VkKeyScanA(c);
  input.ki.dwFlags = KEYEVENTF_KEYUP;
  SendInput(1, &input, sizeof input);
  #endif
}
