#include "ui.h"
#include "brush.h"
#include "commonh.h"

int GenerateUI(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){

    HINSTANCE hInstance = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);
    if (hInstance == NULL){
        MessageBox(NULL, "Failed to load hInstance", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    //HWND hwndButton = CreateButton(hwnd, hInstance, "BTN??", IDC_SOMEBUTTON, &OnButtonClicked);
    HWND hwndButton1 = CreateButton(hwnd, hInstance, (vector2i) {0, 0}, (vector2i) {50, 50}, "WHITE", IDC_PREDEF_COLOR_WHITE, &SelectColor);
    HWND hwndButton2 = CreateButton(hwnd, hInstance, (vector2i) {0, 100}, (vector2i) {50, 50}, "GREEN", IDC_PREDEF_COLOR_GREEN, &SelectColor);

    if (hwndButton1 == NULL || hwndButton2 == NULL){
        MessageBox(NULL, "Button init failed.", "ERror", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
}

HWND CreateButton(HWND hwnd, HINSTANCE hInstance, vector2i pos, vector2i size, char name[], int id, callback* cbfun){
    HWND hwndButton = CreateWindowEx(
        0,
        "BUTTON",
        name,
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        pos.x, pos.y,
        size.x, size.y,
        hwnd,
        (HMENU)id,
        hInstance,
        NULL
    );
    funcCallbacks[funcIdCunter] = cbfun;
    funcIds[funcIdCunter] = id;
    funcIdCunter++; // increase global ID counter for next element

    return hwndButton;
}

void SelectColor(HWND hwnd, int idc){
    switch (idc){
        case (IDC_PREDEF_COLOR_WHITE):
            selectedColor = colors[WHITE];
            break;
        case (IDC_PREDEF_COLOR_RED):
            selectedColor = colors[RED];
            break;
        case (IDC_PREDEF_COLOR_BLACK):
            selectedColor = colors[BLACK];
            break;
        case (IDC_PREDEF_COLOR_GREEN):
            selectedColor = colors[GREEN];
            break;
        default:
            break;
    }
}