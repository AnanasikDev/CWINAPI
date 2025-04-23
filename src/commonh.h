#pragma once

#include <stdio.h>
#include <windows.h>
#include <windowsx.h>

// =============================

typedef void callback(HWND hwnd);

extern const int funcIdsNumber;
extern int* funcIds;
extern callback** funcCallbacks;
extern int funcId;