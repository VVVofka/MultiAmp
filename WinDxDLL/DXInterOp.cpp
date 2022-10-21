// File: InterOp.cpp
// https://hackmag.com/coding/computing-with-gpu/
// This application demonstrates the usage of AMP C++ interOp APIs with Direct3D 11. 
// It displays the animation of a triangle rotation. 
//
// Copyright (c) Microsoft Corporation. All rights reserved.
// --------------------------------------------------------------------------------------
#include "pch.h"

//#include <windows.h>
#include "DXInterOp.h"
static bool pauseRender = false;

// --------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
#pragma warning(suppress : 28251)
//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow){
int mn(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, structAll* cfg_all){
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	if(FAILED(model.Create(cfg_all)))
		return E_POINTER;
	if(FAILED(InitWindow(hInstance, nCmdShow)))
		return E_NOINTERFACE;
	if(FAILED(mdx.InitDevice(g_hWnd, model.v_scr))){
		mdx.CleanupDevice();
		return E_FAIL;
	}
	int work();
	return work();
} // ////////////////////////////////////////////////////////////////////////////
int work(){
	//model.Create(szlay0, 1024 * 2, 0.035, Sigma);

	// Main message loop
	MSG msg = {0};
	time_t ltime;
	time(&ltime);
	int cnt = 0;
	while(WM_QUIT != msg.message){
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else{
			if(!pauseRender){
				mdx.Render();	// MAIN !!!
				cnt++;
				time_t ctime;
				time(&ctime);
				const int interval = 5;
				if(ctime - ltime >= interval){
					ltime = ctime;
					char buf[32];
					sprintf_s(buf, 32, "fps: %d", cnt / interval);
					SetWindowTextA(g_hWnd, buf);
					cnt = 0;
				}
			}
		}
	}
	mdx.CleanupDevice();
	return (int)msg.wParam;
} // /////////////////////////////////////////////////////////////////////////////
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow){  // Register class and create window
	// Register class
	WNDCLASSEX wcex{};
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"AMPC++WindowClass";
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	if(!RegisterClassEx(&wcex))  return E_FAIL;

	// Create window
	g_hInst = hInstance;
	RECT rc = {0, 0, 900, 900};
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	g_hWnd = CreateWindow(L"AMPC++WindowClass", L"AMPC++ and Direct3D 11 InterOp Sample",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance,
		NULL);
	if(!g_hWnd)
		return E_FAIL;
	ShowWindow(g_hWnd, nCmdShow);
	return S_OK;
} // //////////////////////////////////////////////////////////////////////////////////////////////
// Called every time the application receives a message
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	switch(message){
	case WM_PAINT:
		PAINTSTRUCT ps;
		BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch(wParam){
		case VK_ESCAPE:
			SendMessage(hWnd, WM_CLOSE, 0, 0);
			break;
		case 79:{ // key 'o'  // I=73
			pauseRender = true;
			if(model.options.showDlg()){
				model.Create(model.cfgAll);
				mdx.CleanupDevice();
				mdx.InitDevice(g_hWnd, model.v_scr);
			}
			pauseRender = false;
			break; }
		case VK_PAUSE:
			break;
		default:
			setConsole();
			printf("%d\n", (int)wParam);
			break;
		}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
} // ////////////////////////////////////////////////////////////////////////////////////
