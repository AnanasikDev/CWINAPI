#include "commonh.h"
#include "ui.h"
#include <memory.h>
#include <stdlib.h>
#include <stdint.h>
//#include <windef.h>

const char gClassName[] = "MyWindowClass";
BOOL askToQuit = 0;
const int funcIdsNumber = 1;
int* funcIds = NULL;
callback** funcCallbacks = NULL;
int funcId = 0;

// struct vector4{
//     LONG x;
//     LONG y;
//     LONG z;
//     LONG w;
// } padding;
// padding = {10, 10, 10, 10};

//struct tagRECT pad;
//pad.left = 10;
struct tagRECT pad = {50, 50, 50, 50};

static BITMAPINFO frame_bitmap_info;
static HBITMAP frame_bitmap = 0;
static HDC frame_device_context = 0;

struct {
    int width;
    int height;
    uint32_t *pixels;
} frame = {0};

void Init(){
    funcIds = (int*)malloc(funcIdsNumber * sizeof(int));
    funcCallbacks = (callback**)malloc(funcIdsNumber * sizeof(int));
}

void Quit(HWND hwnd){
    free(funcIds);
    free(funcCallbacks);

    DestroyWindow(hwnd);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
    switch (msg){

        case WM_CREATE:{

            GenerateUI(hwnd, msg, wParam, lParam);
        }
        return 0;

        case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            int wmEvent = HIWORD(wParam);

            for (int i = 0; i < funcIdsNumber; i++){
                if (wmId == funcIds[i]){
                    if (wmEvent == BN_CLICKED){
                        (*funcCallbacks[i])(hwnd);
                        return 0;
                    }
                }
            }
        }

            break;
        case WM_RBUTTONDOWN:
            ; // avoids macros problems
            int x = GET_X_LPARAM(lParam);
            int y = GET_Y_LPARAM(lParam);
            char buf[50];
            snprintf(buf, 50, "x = %i, y = %i", x, y);
            MessageBox(NULL, buf, "You are sneaky:D", MB_ICONINFORMATION);
            break;
        case WM_CLOSE:
            if (!askToQuit || MessageBox(NULL, "Really quit?", "Quit?", MB_ICONQUESTION | MB_YESNO) == IDYES){
                Quit(hwnd);
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_PAINT: {
            static PAINTSTRUCT paint;
            static HDC device_context;
            device_context = BeginPaint(hwnd, &paint);
            BitBlt(device_context,
                    
                    paint.rcPaint.left + pad.left, 
                    paint.rcPaint.top + pad.top,
                    paint.rcPaint.right - (paint.rcPaint.left + pad.left) - pad.right, 
                    paint.rcPaint.bottom - (paint.rcPaint.top + pad.top) - pad.bottom,

                    frame_device_context,
                    paint.rcPaint.left, paint.rcPaint.top,
                    SRCCOPY);
            EndPaint(hwnd, &paint);
        } break;

        case WM_SIZE: {
            frame_bitmap_info.bmiHeader.biWidth  = LOWORD(lParam);
            frame_bitmap_info.bmiHeader.biHeight = HIWORD(lParam);

            if(frame_bitmap) DeleteObject(frame_bitmap);
            frame_bitmap = CreateDIBSection(NULL, &frame_bitmap_info, DIB_RGB_COLORS, (void**)&frame.pixels, 0, 0);
            SelectObject(frame_device_context, frame_bitmap);

            frame.width =  LOWORD(lParam);
            frame.height = HIWORD(lParam);
        } break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow){

    Init();

    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = gClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    
    if (!RegisterClassEx(&wc)){
        MessageBox(NULL, "Window registration failed!:(", "ERROR!!!!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    frame_bitmap_info.bmiHeader.biSize = sizeof(frame_bitmap_info.bmiHeader);
    frame_bitmap_info.bmiHeader.biPlanes = 1;
    frame_bitmap_info.bmiHeader.biBitCount = 32;
    frame_bitmap_info.bmiHeader.biCompression = BI_RGB;
    frame_device_context = CreateCompatibleDC(0);

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE, 
        gClassName, 
        "Title of my window:3", // title
        WS_OVERLAPPEDWINDOW, // style
        CW_USEDEFAULT, CW_USEDEFAULT, // x, y
        500, 500, // width, height
        NULL, // hparent
        NULL,
        hInstance,
        NULL
    );
    
    if (hwnd == NULL){
        MessageBox(NULL, "Oh no you fucked up!", "Yeah you did", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&Msg, NULL, 0, 0) > 0 ){
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
        
        for (int p = 0; p < frame.width * frame.height; p++){
            frame.pixels[p] = (COLOR(128, 128, 0));
        }

        InvalidateRect(hwnd, NULL, FALSE);
        UpdateWindow(hwnd);
    }

    return Msg.wParam;
}
