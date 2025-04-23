#pragma once
#include <stdint.h>

struct sframe {
    int width;
    int height;
    uint32_t *pixels;
};

extern struct sframe frame;
void PSetPixel(int x, int y, uint32_t color);
void PSetPixelsRect(int x, int y, int width, int height, uint32_t color);