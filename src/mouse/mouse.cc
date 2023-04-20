//
// Created by huhua on 10/5/2022.
//

#include <easybot/mouse/mouse.h>
#include <Windows.h>

void eb::smartClick() {
  click();
}

void eb::click() {
  INPUT Inputs[2] = {0};
//  Inputs[0].type = INPUT_MOUSE;
//  Inputs[0].mi.dx = ...; // desired X coordinate
//  Inputs[0].mi.dy = ...; // desired Y coordinate
//  Inputs[0].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;

  Inputs[0].type = INPUT_MOUSE;
  Inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

  Inputs[1].type = INPUT_MOUSE;
  Inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

  SendInput(sizeof(Inputs) / sizeof(INPUT), Inputs, sizeof(INPUT));
}