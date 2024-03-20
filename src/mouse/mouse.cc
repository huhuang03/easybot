//
// Created by huhua on 10/5/2022.
//

#include <easybot/mouse/mouse.h>
#ifdef _WIN32
#include <Windows.h>
#endif

void eb::smartClick() {
  click();
}

void eb::click() {
#ifdef _WIN32
  INPUT Inputs[2] = {0};
  Inputs[0].type = INPUT_MOUSE;
  Inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

  Inputs[1].type = INPUT_MOUSE;
  Inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

  SendInput(sizeof(Inputs) / sizeof(INPUT), Inputs, sizeof(INPUT));
#endif
}