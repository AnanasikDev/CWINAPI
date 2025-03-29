#include "ui.h"

const char gClassName[] = "MyWindowClass";
#define IDC_SOMEBUTTON 101
BOOL askToQuit = 0;

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

            switch (wmId){
                case IDC_SOMEBUTTON:
                    if (wmEvent == BN_CLICKED){
                        MessageBox(NULL, "You pressed my button!", "Heh", MB_ICONINFORMATION | MB_OK);
                        return 0;
                    }
                    break;
                default:
                    break;
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
                DestroyWindow(hwnd);
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow){
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
    }

    return Msg.wParam;
}
