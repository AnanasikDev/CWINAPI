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
    LIGHT_BLUE,
    BLUE,
    PURPLE,
    PINK,
};
#define MAX_PREDEF_COLORS 13

extern int* colors;
extern uint32_t selectedColor;