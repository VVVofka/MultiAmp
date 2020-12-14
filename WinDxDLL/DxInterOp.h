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
#ifdef MY2D
#include "MDX2.h"
#include "Model2D.h"
#elif MY3D // MY2D
#include "MDX3.h"
#else // MY2D
#include "MDX2.h"
#include "Model2D.h"
#include "Utils.h"
#endif // MY2D
#include "Options.h"

// --------------------------------------------------------------------------------------
// Global Variables
HINSTANCE                   g_hInst = NULL;
HWND                        g_hWnd = NULL;
// Forward declarations
HRESULT             InitWindow(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

#ifdef MY2D
MDX2 mdx;
Model2D model;
std::vector<Vertex2D> vertices(3);
#elif MY3D // MY2D
MDX3 mdx;
std::vector<Vertex3D> vertices(3);
#else // MY2D
MDX2 mdx;
Model2D model = Model2D();
#endif // MY2D

#endif  // MODEA

