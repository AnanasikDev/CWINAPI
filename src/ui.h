#include "commonh.h"
#define IDC_SOMEBUTTON 101

HWND hwndButton;
int GenerateUI(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
HWND CreateButton(HWND hwnd, HINSTANCE hInstance, char name[], int id);