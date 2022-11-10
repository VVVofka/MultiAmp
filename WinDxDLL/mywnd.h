#pragma once
#include "NewEngine.h"
#include "..\OptsTinyLib\structAll.h"
#include <Windows.h>
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <algorithm>
//#include <iterator>
//#include <exception>
//#include "Masks.h"
//#include "Model2D.h"
//#include "Utils.h"
//#include "Options.h"

namespace mywnd{
	LRESULT CALLBACK tmpWndProc(HWND, UINT, WPARAM, LPARAM);

	int run(HINSTANCE hInstance, int nCmdShow, structAll* cfg_all);

	HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);

	int work();
}

