#include "graphics.h"
#include "commonh.h"
#include <math.h>
//#include <png.h>

void PSetPixel(int x, int y, uint32_t color){
    frame.pixels[x + y * frame.width] = color;
}

void PSetPixelsRect(int x, int y, int width, int height, uint32_t color){
    for (int _x = max(0, x); _x < min(x + width, frame.width); _x++){
        for (int _y = max(0, y); _y < min(y + height, frame.height); _y++){
            PSetPixel(_x, _y, color);
        }
    }
}