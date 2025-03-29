#include "ui.h"

int GenerateUI(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){

    HINSTANCE hInstance = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);
    if (hInstance == NULL){
        MessageBox(NULL, "Failed to load hInstance", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwndButton = CreateWindowEx(
        0,
        "BUTTON",
        "Button ig?",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        10, 10,
        60, 25,
        hwnd,
        NULL,
        hInstance,
        NULL
    );

    if (hwndButton == NULL){
        MessageBox(NULL, "Button init failed.", "ERror", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    
}