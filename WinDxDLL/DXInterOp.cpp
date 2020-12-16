// File: InterOp.cpp
// https://hackmag.com/coding/computing-with-gpu/
// This application demonstrates the usage of AMP C++ interOp APIs with Direct3D 11. 
// It displays the animation of a triangle rotation. 
//
// Copyright (c) Microsoft Corporation. All rights reserved.
// --------------------------------------------------------------------------------------
#include "pch.h"
#ifdef MODEA

//#include <windows.h>
#include "DXInterOp.h"
static bool pauseRender = false;

// --------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
#pragma warning(suppress : 28251)
//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow){
int mn(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow){
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	if(FAILED(InitWindow(hInstance, nCmdShow)))
		return 0;
#ifdef MY2D
	vertices[0].Pos = DirectX::XMFLOAT2(-0.25f, 0.0f);
	vertices[1].Pos = DirectX::XMFLOAT2(0.0f, -0.5f);
	vertices[2].Pos = DirectX::XMFLOAT2(-0.5f, -0.5f);
	if(FAILED(mdx.InitDevice(g_hWnd, vertices))){
		mdx.CleanupDevice();
		return E_FAIL;
	}
#elif MY3D // MY2D
	vertices[0].Pos = DirectX::XMFLOAT3(-0.25f, 0.0f, 0.0f);
	vertices[1].Pos = DirectX::XMFLOAT3(0.0f, -0.5f, -0.3f);
	vertices[2].Pos = DirectX::XMFLOAT3(-0.5f, -0.5f, 0.3f);
	if(FAILED(mdx.InitDevice(g_hWnd, vertices))){
		mdx.CleanupDevice();
		return E_FAIL;
	}
#else 
	//INT2 szlay0 = INT2(1, 1);
	////model.Create(szlay0, 1024 * 1, 0.06); //8 - ???
	//DBL2 Sigma(0.15, 0.15);
	//model.Create(szlay0, 1024 * 2, 0.015, Sigma); //8 - ???
	//if(FAILED(mdx.InitDevice(g_hWnd, model.lastPoss()))){
	//	mdx.CleanupDevice();
	//	return E_FAIL;
	//}
#endif // MY2D
	int work();
	return work();
} // ////////////////////////////////////////////////////////////////////////////
int work(){
	//model.Create(szlay0, 1024 * 2, 0.035, Sigma);
	model.Create();
	if(FAILED(mdx.InitDevice(g_hWnd, model.lastPoss()))){
		mdx.CleanupDevice();
		return E_FAIL;
	}

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
				mdx.Render();
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
	PAINTSTRUCT ps;	HDC hdc;
	switch(message){
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
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
						model.Create();
						mdx.CleanupDevice();
						mdx.InitDevice(g_hWnd, model.lastPoss());
					}
					pauseRender = false;
					break; }
				case VK_PAUSE:
					break;
				default:
					setConsole();			printf("%d\n", (int)wParam);
					break;
			}
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
} // ////////////////////////////////////////////////////////////////////////////////////
#endif  // MODEA
