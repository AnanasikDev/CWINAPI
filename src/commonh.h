#pragma once

#include <stdio.h>
#include <windows.h>
#include <windowsx.h>

#define COLOR(r,g,b) (r << 16) + (g << 8) + b

// =============================

typedef void callback(HWND hwnd);

extern const int funcIdsNumber;
extern int* funcIds;
extern callback** funcCallbacks;
extern int funcId;

struct vector2i{
    int x;
    int y;
};