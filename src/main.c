#include <memory.h>
#include <stdlib.h>
#include <stdint.h>
#include "commonh.h"
#include "ui.h"
#include "graphics.h"
#include "input.h"
#include "brush.h"

// ============= SETTINGS =============
const char gClassName[] = "MyWindowClass";
BOOL askToQuit = 0;
struct tagRECT padding = {50, 50, 50, 50};
uint32_t selectedColor = COLOR(255, 0, 0);
// ====================================

int* funcIds = NULL;
callback** funcCallbacks = NULL;
int funcIdCounter = 0;
struct tagPOINT windowCursorPosition = {0, 0};
struct tagPOINT drawingCursorPosition = {0, 0};

static BITMAPINFO frame_bitmap_info;
static HBITMAP frame_bitmap = 0;
static HDC frame_device_context = 0;

int* colors = NULL;

struct sframe frame = {0, 0, NULL};

void Init(){
    printf("Init\n");
    funcIds =           (int*)malloc(DYNAMIC_ELEMENTS_COUNT * sizeof(int));
    funcCallbacks =     (callback**)malloc(DYNAMIC_ELEMENTS_COUNT * sizeof(int));
    colors =            (int*)malloc(MAX_PREDEF_COLORS * sizeof(int));
    colors[0] = COLOR(255, 255, 255); // white
    colors[1] = COLOR(0, 0, 0);       // black
    colors[2] = COLOR(140, 140, 140); // light grey
    colors[3] = COLOR(80, 80, 80);    // dark grey
    colors[4] = COLOR(255, 0, 0);     // red
    colors[5] = COLOR(255, 128, 0);   // orange
    colors[6] = COLOR(255, 255, 0);   // yellow
    colors[7] = COLOR(80, 255, 83);   // lime
    colors[8] = COLOR(0, 255, 0);     // green
    colors[9] = COLOR(128, 128, 255); // light blue
    colors[10] = COLOR(0, 0, 255);    // blue
    colors[11] = COLOR(255, 0, 255);  // purple
    colors[12] = COLOR(255, 128, 230);  // pink
}

void FREE(void* block){
    if (block == NULL){
        printf("block cannot be freed; it is NULL\n");
        return;
    }
    printf("block successfully freed\n");
    free(block);
}

void Quit(HWND hwnd){
    FREE(funcIds);
    for (int c = 0; c < DYNAMIC_ELEMENTS_COUNT; c++){
        funcCallbacks[c] = NULL;
    }
    FREE(funcCallbacks);
    FREE(colors);
    printf("Quit");
    DestroyWindow(hwnd);
}

void Update();

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

            for (int i = 0; i < funcIdCounter; i++){
                if (wmId == funcIds[i]){
                    if (wmEvent == BN_CLICKED){
                        (*funcCallbacks[i])(hwnd, wmId);
                        return 0;
                    }
                }
            }
        }

            break;
        case WM_LBUTTONDOWN:
            ;
            isLMBdown = TRUE;
            break;
        case WM_LBUTTONUP:
            isLMBdown = FALSE;
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
                    
                    paint.rcPaint.left + padding.left, 
                    paint.rcPaint.top + padding.top,
                    paint.rcPaint.right - (paint.rcPaint.left + padding.left) - padding.right, 
                    paint.rcPaint.bottom - (paint.rcPaint.top + padding.top) - padding.bottom,

                    frame_device_context,
                    paint.rcPaint.left, paint.rcPaint.top,
                    SRCCOPY);
            EndPaint(hwnd, &paint);
        } break;

        case WM_DRAWITEM:
        {
            LPDRAWITEMSTRUCT lpDrawItem = (LPDRAWITEMSTRUCT)lParam;

            // Check if this message is for one of YOUR owner-drawn buttons
            // Use the button's control ID to identify it
            if (lpDrawItem->CtlID >= IDC_PREDEF_COLOR_WHITE && lpDrawItem->CtlID <= IDC_PREDEF_COLOR_PINK) // Assuming your button IDs are in a range
            {
                // --- Perform Custom Drawing Here ---
                printf("%d\n", lpDrawItem->CtlID);

                HDC hdc = lpDrawItem->hDC;           // Device context to draw on
                RECT rc = lpDrawItem->rcItem;         // Rectangle defining the button's area
                UINT itemState = lpDrawItem->itemState; // State flags (pressed, hovered, focused, etc.)
                UINT buttonID = lpDrawItem->CtlID;    // The ID of the button being drawn

                COLORREF buttonColor = GetButtonColor(buttonID); // Your function to get color
                HBRUSH hBrush = CreateSolidBrush(buttonColor);
                FillRect(hdc, &rc, hBrush);
                DeleteObject(hBrush);
            }
            break;
        }

        case WM_SIZE: {
            frame_bitmap_info.bmiHeader.biWidth  = LOWORD(lParam);
            frame_bitmap_info.bmiHeader.biHeight = HIWORD(lParam);

            if(frame_bitmap) DeleteObject(frame_bitmap);
            // uint32_t* oldColors = NULL;
            // for (int i = 0; i < frame.width * frame.height; i++){
            //     oldColors[i] = frame.pixels[i];
            // }
            frame_bitmap = CreateDIBSection(NULL, &frame_bitmap_info, DIB_RGB_COLORS, (void**)&frame.pixels, 0, 0);
            SelectObject(frame_device_context, frame_bitmap);
            
            // for (int i = 0; i < frame.width * frame.height; i++){
            //     frame.pixels[i] = oldColors[i];
            // }

            frame.width =  LOWORD(lParam);
            frame.height = HIWORD(lParam);
            //InvalidateRect(hwnd, NULL, TRUE);
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
        GetCursorPos(&windowCursorPosition);
        MapWindowPoints(NULL, hwnd, &windowCursorPosition, 1);
        drawingCursorPosition.x = windowCursorPosition.x - padding.left;
        drawingCursorPosition.y = frame.height - (windowCursorPosition.y - padding.top);

        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
        
        Update();
        
        InvalidateRect(hwnd, NULL, FALSE);
        UpdateWindow(hwnd);
    }

    return Msg.wParam;
}

void Update(){

    if (isLMBdown){
        int radius = 10;
        PSetPixelsRect(drawingCursorPosition.x - radius / 2, drawingCursorPosition.y - radius / 2, radius, radius, selectedColor);
    }
}