// --------------------------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// --------------------------------------------------------------------------------------
#pragma once
#include "pch.h"
#ifdef MODEA

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <exception>
#include "Masks.h"
#include "MDX2.h"
#include "Model2D.h"
#include "Utils.h"
#include "Options.h"

// --------------------------------------------------------------------------------------
// Global Variables
HINSTANCE                   g_hInst = NULL;
HWND                        g_hWnd = NULL;
// Forward declarations
HRESULT             InitWindow(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

MDX2 mdx;
Model2D model = Model2D();

#endif  // MODEA

