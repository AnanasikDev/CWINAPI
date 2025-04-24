#pragma once

#include "commonh.h"
#define IDC_SOMEBUTTON 101
#define IDC_PREDEF_COLOR_WHITE 1010
#define IDC_PREDEF_COLOR_BLACK 1011
#define IDC_PREDEF_COLOR_RED   1012
#define IDC_PREDEF_COLOR_GREEN 1013

int GenerateUI(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
HWND CreateButton(HWND hwnd, HINSTANCE hInstance, vector2i pos, vector2i size, char name[], int id, callback* cbfun);
void SelectColor(HWND hwnd, int idc);