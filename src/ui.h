#pragma once

#include "commonh.h"
#define IDC_SOMEBUTTON 101

int GenerateUI(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
HWND CreateButton(HWND hwnd, HINSTANCE hInstance, char name[], int id, callback* cbfun);
void OnButtonClicked(HWND hwnd);