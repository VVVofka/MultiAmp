// AMPEngine2Lib.cpp : Defines the functions for the static library.
#include "framework.h"
#include "AMPEngine2Lib.h"
namespace eng2{
	bool pauseRender;
	//MDX2 mdx;
	HINSTANCE g_hInst;
	HWND g_hWnd;

	int fnAMPEngine2Lib(){
		return 7;
	} // /////////////////////////////////////////////////////////////////////////////////////////////////////////
	int run(HINSTANCE hInstance, int nCmdShow, structAll* cfg_all){
		if(FAILED(InitWindow(hInstance, nCmdShow)))
			return E_NOINTERFACE;
		//if(FAILED(mdx.InitDevice(g_hWnd, cfg_all))){
		//	mdx.CleanupDevice();
		//	return E_FAIL;
		//}
		//return work();
		return 8;
	} // ///////////////////////////////////////////////////////////////////////////////////////////
	HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow){  // Register class and create window
	// Register class
		static WNDCLASSEX wcex{};
		if(wcex.lpfnWndProc == 0){
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
			wcex.lpszClassName = "AMPC++WindowClass";
			wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
			if(!RegisterClassEx(&wcex))
				return E_FAIL;
		}
		// Create window
		g_hInst = hInstance;
		RECT rc = {0, 0, 900, 900};
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
		g_hWnd = CreateWindow("AMPC++WindowClass", "AMPC++ and Direct3D 11 InterOp Sample",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance,
			NULL);
		if(!g_hWnd)
			return E_FAIL;
		ShowWindow(g_hWnd, nCmdShow);
		return S_OK;
	} // //////////////////////////////////////////////////////////////////////////////////////////////
	int work(){
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
					//					mdx.Render();	// MAIN !!!
										//model2.cfgAll->misc.curIteration++;
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
		//		mdx.CleanupDevice();
		return (int)msg.wParam;
	} // /////////////////////////////////////////////////////////////////////////////
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
				//if(model2.options.showDlg()){
				//	model2.Create();
				//	mdx.CleanupDevice();
				//	mdx.InitDevice(g_hWnd, mdx.cfg_all);
				//}
				pauseRender = false;
				break;
			}
			case VK_PAUSE:
				break;
			default:
				//				model2.setConsole();
				printf("%d\n", (int)wParam);
				break;
			}
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		return 0;
	} // ////////////////////////////////////////////////////////////////////////////////////
} // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@