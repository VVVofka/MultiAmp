#include <strsafe.h>
#include "wndAMP.h"
#include "MDX/MDX2.h"
#include "..\OptsTinyLib\structAll.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
namespace eng2{
	// static file
	bool pauseRender;
	bool isQuit;

	// global (def in AMPEngine2Lib.cpp)
	extern MDX2 mdx;
	extern HWND g_hWnd;
	extern structAll* cfgall;

	void ErrorExit(LPCTSTR caption);

	// ////////////////////////////////////////////////////////////////////////////////////////////////////////
	HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow){  // Register class and create window
		// Register class
		const WCHAR szWindowClass[] = L"wndAMP_WindowClass";
		static WNDCLASSEX wcex{};
		if(wcex.lpfnWndProc == 0){
			wcex.cbSize = sizeof(WNDCLASSEX);
			wcex.style = CS_HREDRAW | CS_VREDRAW;
			wcex.lpfnWndProc = WndProc;
			wcex.cbClsExtra = 0;
			wcex.cbWndExtra = 0;
			wcex.hInstance = hInstance;
			//wcex.hInstance = NULL;
			wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
			wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
			wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
			wcex.lpszMenuName = NULL;
			wcex.lpszClassName = szWindowClass;
			wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
			ATOM retReg = RegisterClassEx(&wcex);
			if(retReg == 0)
				ErrorExit(TEXT("InitWindow RegisterClassEx"));
			if(!retReg)
				return E_FAIL;
		}
		// Create window
		RECT rc = {0, 0, 900, 900};
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
		g_hWnd = CreateWindow(szWindowClass, L"AMPC++ and Direct3D 11 InterOp Sample",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance,
			NULL);
		if(g_hWnd == 0)
			ErrorExit(TEXT("InitWindow CreateWindow"));
		if(!g_hWnd)
			return E_FAIL;
		ShowWindow(g_hWnd, nCmdShow);
		return S_OK;
	} // //////////////////////////////////////////////////////////////////////////////////////////////
	int MainLoop(){
		MSG msg = {0};
		time_t ltime;
		time(&ltime);
		int cnt = 0;
		isQuit = false;
		while(WM_QUIT != msg.message || !isQuit){
			if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			} else{
				if(!pauseRender){
					//mdx.Render();	// MAIN !!!
										//model2.cfgAll->misc.curIteration++;
					cnt++;
					time_t ctime;
					time(&ctime);
					const int interval = 1;
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
	void ErrorExit(LPCTSTR caption){	// Retrieve the system error message for the last-error code
		LPVOID lpMsgBuf, lpDisplayBuf;
		DWORD dw = GetLastError();

		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			dw,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf,
			0, NULL);

		// Display the error message and exit the process
		lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, (lstrlen((LPCTSTR)lpMsgBuf) + 40) * sizeof(TCHAR));
#pragma warning(push)
#pragma warning(disable:28183 6067) 
		StringCchPrintf((LPTSTR)lpDisplayBuf, LocalSize(lpDisplayBuf) / sizeof(TCHAR),
			TEXT("failed with error %d: %s"), dw, lpMsgBuf);
#pragma warning(pop)
		MessageBox(NULL, (LPCTSTR)lpDisplayBuf, (LPCTSTR)(caption), MB_OK);

		LocalFree(lpMsgBuf);
		LocalFree(lpDisplayBuf);
		ExitProcess(dw);
	} // //////////////////////////////////////////////////////////////////////////////////////////
} // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	switch(message){
	case WM_PAINT:
		PAINTSTRUCT ps;
		BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		switch(wParam){
		case VK_ESCAPE:
			eng2::isQuit = true;
			SendMessage(hWnd, WM_CLOSE, 0, 0);
			break;
		case 79:{ // key 'o'  // I=73
			eng2::pauseRender = true;
			//if(model2.options.showDlg()){
			//	model2.Create();
			//	mdx.CleanupDevice();
			//	mdx.InitDevice(g_hWnd, mdx.cfg_all);
			//}
			eng2::pauseRender = false;
			break;
		}
		case VK_PAUSE:
			break;
		default:
			//				model2.setConsole();
			printf("%d\n", (int)wParam);
			break;
		}
	case WM_DESTROY:
		eng2::isQuit = true;
		PostQuitMessage(0);	// close application
		//SendMessage(hWnd, WM_QUIT, 0, 0);
		break;
		//return 0;
	default:
		if(--eng2::cfgall->misc.cntForStop <= 0)
			DestroyWindow(hWnd);
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
} // ////////////////////////////////////////////////////////////////////////////////////
