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

    vector2i size = {20, 20};

    CreateButton(hwnd, hInstance, (vector2i) {0, 0}, size, "WHITE", IDC_PREDEF_COLOR_WHITE, &SelectColor);
    CreateButton(hwnd, hInstance, (vector2i) {20, 0}, size, "BLACK", IDC_PREDEF_COLOR_BLACK, &SelectColor);
    CreateButton(hwnd, hInstance, (vector2i) {40, 0}, size, "LIGHT GREY", IDC_PREDEF_COLOR_LIGHT_GREY, &SelectColor);
    CreateButton(hwnd, hInstance, (vector2i) {60, 0}, size, "DARK GREY", IDC_PREDEF_COLOR_DARK_GREY, &SelectColor);
    CreateButton(hwnd, hInstance, (vector2i) {80, 0}, size, "RED", IDC_PREDEF_COLOR_RED, &SelectColor);
    CreateButton(hwnd, hInstance, (vector2i) {100, 0}, size, "ORANGE", IDC_PREDEF_COLOR_ORANGE, &SelectColor);
    CreateButton(hwnd, hInstance, (vector2i) {120, 0}, size, "YELLOW", IDC_PREDEF_COLOR_YELLOW, &SelectColor);
    CreateButton(hwnd, hInstance, (vector2i) {0, 20}, size, "LIME", IDC_PREDEF_COLOR_LIME, &SelectColor);
    CreateButton(hwnd, hInstance, (vector2i) {20, 20}, size, "GREEN", IDC_PREDEF_COLOR_GREEN, &SelectColor);
    CreateButton(hwnd, hInstance, (vector2i) {40, 20}, size, "TEAL", IDC_PREDEF_COLOR_TEAL, &SelectColor);
    CreateButton(hwnd, hInstance, (vector2i) {60, 20}, size, "LIGHT BLUE", IDC_PREDEF_COLOR_LIGHT_BLUE, &SelectColor);
    CreateButton(hwnd, hInstance, (vector2i) {80, 20}, size, "BLUE", IDC_PREDEF_COLOR_BLUE, &SelectColor);
    CreateButton(hwnd, hInstance, (vector2i) {100, 20}, size, "PURPLE", IDC_PREDEF_COLOR_PURPLE, &SelectColor);
    CreateButton(hwnd, hInstance, (vector2i) {120, 20}, size, "PINK", IDC_PREDEF_COLOR_PINK, &SelectColor);
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
        case (IDC_PREDEF_COLOR_TEAL):
            return colors[TEAL];
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