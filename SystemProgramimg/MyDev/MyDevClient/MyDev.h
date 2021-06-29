#pragma once
#include "pch.h"
#include "framework.h"
#include <afxwin.h>
#include <afxdllx.h>
#include <stdlib.h>
#include <time.h>

extern "C" __declspec(dllexport) BOOL InitMyDev(int nLevel);
extern "C" __declspec(dllexport) int GetMyDevError(void);
extern "C" __declspec(dllexport) BOOL GetMyDevPosition(int* x, int* y);
extern "C" __declspec(dllexport) void ReleaseMyDev(void);

