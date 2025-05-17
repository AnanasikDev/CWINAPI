#pragma once

#include <stdio.h>
#include <windows.h>
#include <windowsx.h>
#include <stdint.h>

#define COLOR(r,g,b) (r << 16) + (g << 8) + b
#define CHANNEL_R(i) i >> 16 
#define CHANNEL_G(i) (i >> 8) & 255
#define CHANNEL_B(i) i & 255

// =============================

typedef void callback(HWND hwnd, int idc);

extern int* funcIds;
extern callback** funcCallbacks;
extern int funcIdCounter;

typedef struct{
    int x;
    int y;
} vector2i;