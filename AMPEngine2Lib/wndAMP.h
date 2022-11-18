#pragma once
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

namespace eng2{
	HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
	int MainLoop();
	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
} // namespace eng2 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

