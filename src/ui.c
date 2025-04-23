#include "ui.h"

int GenerateUI(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){

    HINSTANCE hInstance = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);
    if (hInstance == NULL){
        MessageBox(NULL, "Failed to load hInstance", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    HWND hwndButton = CreateButton(hwnd, hInstance, "BTN??", IDC_SOMEBUTTON, &OnButtonClicked);

    if (hwndButton == NULL){
        MessageBox(NULL, "Button init failed.", "ERror", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
}

HWND CreateButton(HWND hwnd, HINSTANCE hInstance, char name[], int id, callback* cbfun){
    HWND hwndButton = CreateWindowEx(
        0,
        "BUTTON",
        name,
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        10, 10,
        60, 25,
        hwnd,
        (HMENU)id,
        hInstance,
        NULL
    );
    funcCallbacks[funcId] = cbfun;
    funcIds[funcId] = id;
    funcId++; // increase global ID counter for next element

    return hwndButton;
}

void OnButtonClicked(HWND hwnd){
    MessageBox(NULL, "CUSTOM CALLBACK!!!", "meow", MB_ICONINFORMATION | MB_OK);
}