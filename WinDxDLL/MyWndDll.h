#pragma once
#include <minwindef.h>
#include "..\OptsTinyLib\structAll.h"
#include "NewEngine.h"

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


class MyWndDll{
public:
	int run(HINSTANCE hInstance, int nCmdShow, structAll* cfg_all);

private:
	HINSTANCE                   g_hInst = NULL;
	HWND                        g_hWnd = NULL;
	// Forward declarations
	HRESULT             InitWindow(HINSTANCE hInstance, int nCmdShow);
	LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

	MDX2 mdx;
	Model2D model = Model2D();

	int work();
	bool pauseRender = false;

}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

