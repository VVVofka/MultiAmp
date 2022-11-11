#pragma once
#include <Windows.h>
#include "..\OptsTinyLib\structAll.h"

namespace eng2{
		int fnAMPEngine2Lib();
		int run(HINSTANCE hInstance, int nCmdShow, structAll* cfg_all);
		HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
		LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
		int work();

}