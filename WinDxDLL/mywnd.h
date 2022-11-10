#pragma once
//#include <minwindef.h>
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

namespace mywnd{
	int run(HINSTANCE hInstance, int nCmdShow, structAll* cfg_all);

	HINSTANCE g_hInst;
	HWND g_hWnd;
	HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);

	MDX2 mdx;
	Model2D model;

	int work();
	bool pauseRender;
}

