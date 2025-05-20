#include "ui.h"
#include "brush.h"
#include "commonh.h"

void GenerateUI(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){

    printf("GenerateUI\n");

    HINSTANCE hInstance = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);
    if (hInstance == NULL){
        MessageBox(NULL, "Failed to load hInstance", "Error", MB_ICONEXCLAMATION | MB_OK);
        return;
    }

    vector2i size = {40, 40};

    CreateButton(hwnd, hInstance, (vector2i) {0, 0}, size, "WHITE", IDC_PREDEF_COLOR_WHITE, &SelectColor);
    CreateButton(hwnd, hInstance, (vector2i) {50, 0}, size, "GREEN", IDC_PREDEF_COLOR_GREEN, &SelectColor);
    CreateButton(hwnd, hInstance, (vector2i) {100, 0}, size, "BLACK", IDC_PREDEF_COLOR_BLACK, &SelectColor);
    CreateButton(hwnd, hInstance, (vector2i) {150, 0}, size, "YELLOW", IDC_PREDEF_COLOR_YELLOW, &SelectColor);
    CreateButton(hwnd, hInstance, (vector2i) {200, 0}, size, "BLUE", IDC_PREDEF_COLOR_BLUE, &SelectColor);
}

HWND CreateButton(HWND hwnd, HINSTANCE hInstance, vector2i pos, vector2i size, char name[], int id, callback* cbfun){
    HWND hwndButton = CreateWindowEx(
        //0,
        BS_OWNERDRAW,
        "BUTTON",
        name,
        WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_OWNERDRAW,
        //WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        pos.x, pos.y,
        size.x, size.y,
        hwnd,
        (HMENU)(UINT_PTR)id,
        hInstance,
        NULL
    );
    funcCallbacks[funcIdCounter] = cbfun;
    funcIds[funcIdCounter] = id;
    funcIdCounter++; // increase global ID counter for next element

    if (hwndButton == NULL){
        MessageBox(NULL, "Button init failed.", "Error", MB_ICONEXCLAMATION | MB_OK);
        return NULL;
    }

    return hwndButton;
}

void SelectColor(HWND hwnd, int idc){
    selectedColor = GetButtonColor(idc);
    printf("%d = %d %d %d\n", selectedColor, CHANNEL_R(selectedColor), CHANNEL_G(selectedColor), CHANNEL_B(selectedColor));
}

COLORREF GetButtonColor(UINT idc){
    switch (idc){
        case (IDC_PREDEF_COLOR_WHITE):
            return colors[WHITE];
            break;
        case (IDC_PREDEF_COLOR_BLACK):
            return colors[BLACK];
            break;
        case (IDC_PREDEF_COLOR_LIGHT_GREY):
            return colors[LIGHT_GREY];
            break;
        case (IDC_PREDEF_COLOR_DARK_GREY):
            return colors[DARK_GREY];
            break;
        case (IDC_PREDEF_COLOR_RED):
            return colors[RED];
            break;
        case (IDC_PREDEF_COLOR_ORANGE):
            return colors[ORANGE];
            break;
        case (IDC_PREDEF_COLOR_YELLOW):
            return colors[YELLOW];
            break;
        case (IDC_PREDEF_COLOR_LIME):
            return colors[LIME];
            break;
        case (IDC_PREDEF_COLOR_GREEN):
            return colors[GREEN];
            break;
        case (IDC_PREDEF_COLOR_LIGHT_BLUE):
            return colors[LIGHT_BLUE];
            break;
        case (IDC_PREDEF_COLOR_BLUE):
            return colors[BLUE];
            break;
        case (IDC_PREDEF_COLOR_PURPLE):
            return colors[PURPLE];
            break;
        case (IDC_PREDEF_COLOR_PINK):
            return colors[PINK];
            break;

        default:
            break;
    }
}

COLORREF ToWinColor(uint32_t color){
    return (COLORREF)color;
}