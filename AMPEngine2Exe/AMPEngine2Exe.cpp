// AMPEngine2Exe.cpp : Defines the entry point for the application.
//#include "pch.h"
#include <time.h>
#include <windows.h>
#include <strsafe.h>
//#include "framework.h" // in pch.h
#include "AMPEngine2Exe.h"
#include "CommandCenter.h"
#include "ParseCmdLine.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND hWnd;
bool pauseRender = false;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
int					MainMessageLoop(HINSTANCE hInstance);
int mymain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow);

CommandCenter command_center;
//bool to_exit = false;
// ////////////////////////////////////////////////////////////////////////////////////
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,	_In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine,_In_ int nCmdShow){
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_AMPENGINE2EXE, szWindowClass, MAX_LOADSTRING);
	return mymain(hInstance,hPrevInstance,lpCmdLine,nCmdShow);
} // ///////////////////////////////////////////////////////////////////////////////////
int mymain(HINSTANCE hInstance,	HINSTANCE hPrevInstance,LPWSTR lpCmdLine,int nCmdShow){
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// My start
	ParseCmdLine prs;
	command_center.tick_cnt = prs.parse(lpCmdLine);
	if(prs.fname.size() > 0)
		command_center.structall.load(prs.fname.c_str());
	// My finish

	MyRegisterClass(hInstance);
	if(!InitInstance(hInstance, nCmdShow))
		return FALSE;
	return MainMessageLoop(hInstance);
} // ////////////////////////////////////////////////////////////////////////////////////
int MainMessageLoop(HINSTANCE hInstance){
	MSG msg = {0};
	//HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_AMPENGINE2EXE));
	//while(GetMessage(&msg, nullptr, 0, 0)){
	//	if(!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)){
	//		TranslateMessage(&msg);
	//		DispatchMessage(&msg);
	//	}
	//}
	time_t ltime;
	time(&ltime);
	int cnt = 0;
	std::string sfps = "fps:";
	while(WM_QUIT != msg.message){
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else{
			if(!pauseRender){
				// mdx.Render();	// MAIN !!!
				//model2.cfgAll->misc.curIteration++;
				cnt++;
				time_t ctime;
				time(&ctime);
				const int interval = 5;
				if(ctime - ltime >= interval){
					ltime = ctime;
					SetWindowTextA(hWnd, (sfps + std::to_string(cnt / interval)).c_str());
					cnt = 0;
				}
				//if(command_center.tick_cnt > 0){
				//	if(--command_center.tick_cnt == 0)
				//		to_exit = true;
				//}
			} else{
				SetWindowTextA(hWnd, "Pause");
			}
		}
	}
	//		mdx.CleanupDevice();
	return (int)msg.wParam;
} // ////////////////////////////////////////////////////////////////////////////////////
void ErrorExit(){
	// Retrieve the system error message for the last-error code

	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
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
	StringCchPrintf((LPTSTR)lpDisplayBuf, LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("failed with error %d: %s"), dw, lpMsgBuf);
	MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
	ExitProcess(dw);
} // //////////////////////////////////////////////////////////////////////////////////////////
ATOM MyRegisterClass(HINSTANCE hInstance){
	static WNDCLASSEXW wcex{};
	if(wcex.lpfnWndProc == 0){
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_AMPENGINE2EXE));
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_AMPENGINE2EXE);
		wcex.lpszClassName = szWindowClass;
		wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	}
	auto ret = RegisterClassExW(&wcex);
	if(ret == 0)
		ErrorExit();
	return ret;
} // ////////////////////////////////////////////////////////////////////////////////////
//   FUNCTION: InitInstance(HINSTANCE, int)
//   PURPOSE: Saves instance handle and creates main window
//   COMMENTS:
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow){
	hInst = hInstance; // Store instance handle in our global variable
	hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
	if(!hWnd){
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
} // ////////////////////////////////////////////////////////////////////////////////////
//  PURPOSE: Processes messages for the main window.
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	switch(message){
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch(wmId){
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_KEYDOWN:
		switch(wParam){
		case VK_ESCAPE:
			DestroyWindow(hWnd);	// SendMessage(hWnd, WM_CLOSE, 0, 0);
			break;
		case 79:{ // key 'o'  // I=73
			//pauseRender = true;
			//if(model2.options.showDlg()){
			//	model2.Create();
			//	mdx.CleanupDevice();
			//	mdx.InitDevice(g_hWnd, mdx.cfg_all);
			//}
			//pauseRender = false;
			break;
		}
		case VK_PAUSE:
		case 80: // key 'p'  
			pauseRender = !pauseRender;
			break;
		default:
			_RPT1(0, "%d\n", (int)wParam);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		if(--command_center.tick_cnt == 0)
			DestroyWindow(hWnd);
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
} // ////////////////////////////////////////////////////////////////////////////////////
// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam){
	UNREFERENCED_PARAMETER(lParam);
	switch(message){
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if(LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL){
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
} // ////////////////////////////////////////////////////////////////////////////////////
