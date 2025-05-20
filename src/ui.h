#pragma once

#include "commonh.h"

#define IDC_PREDEF_COLOR_WHITE          1010
#define IDC_PREDEF_COLOR_BLACK          1011
#define IDC_PREDEF_COLOR_LIGHT_GREY     1012
#define IDC_PREDEF_COLOR_DARK_GREY      1013
#define IDC_PREDEF_COLOR_RED            1014
#define IDC_PREDEF_COLOR_ORANGE         1015
#define IDC_PREDEF_COLOR_YELLOW         1016
#define IDC_PREDEF_COLOR_LIME           1017
#define IDC_PREDEF_COLOR_GREEN          1018
#define IDC_PREDEF_COLOR_LIGHT_BLUE     1019
#define IDC_PREDEF_COLOR_TEAL           1020
#define IDC_PREDEF_COLOR_BLUE           1021
#define IDC_PREDEF_COLOR_PURPLE         1022
#define IDC_PREDEF_COLOR_PINK           1023

#define DYNAMIC_ELEMENTS_COUNT 14

void GenerateUI(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
HWND CreateButton(HWND hwnd, HINSTANCE hInstance, vector2i pos, vector2i size, char name[], int id, callback* cbfun);
void SelectColor(HWND hwnd, int idc);
COLORREF GetButtonColor(UINT idc);
COLORREF ToWinColor(uint32_t color);