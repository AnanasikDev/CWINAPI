#pragma once

#include <stdint.h>

enum BRUSH{
    SQUARE,
    CIRCLE
};

enum PREDEF_COLOR{
    WHITE,
    BLACK,
    LIGHT_GREY,
    DARK_GREY,
    RED,
    ORANGE,
    YELLOW,
    LIME,
    GREEN,
    TEAL,
    LIGHT_BLUE,
    BLUE,
    PURPLE,
    PINK,
};
#define MAX_PREDEF_COLORS 14

extern COLORREF* colors;
extern COLORREF selectedColor;