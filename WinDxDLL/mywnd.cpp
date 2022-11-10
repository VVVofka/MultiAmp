#include "mywnd.h"
#include "MDX2.h"
namespace mywnd{
	bool pauseRender;
	MDX2 mdx;
	Model2D model2;
	HINSTANCE g_hInst;
	HWND g_hWnd;
		int run(HINSTANCE hInstance, int nCmdShow, structAll* cfg_all){
		if(model2.Create() == false)
			return E_POINTER;
		if(FAILED(InitWindow(hInstance, nCmdShow)))
			return E_NOINTERFACE;

#ifndef NEW_ENGINE
		if(FAILED(mdx.InitDevice(g_hWnd, model2.v_scr))){
#else // NEW_ENGINE
		if(FAILED(mdx.InitDevice(g_hWnd, cfg_all))){
#endif // NEWENINE
			mdx.CleanupDevice();
			return E_FAIL;
		}
		return work();
	} // ///////////////////////////////////////////////////////////////////////////////////////////
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
					mdx.Render();	// MAIN !!!
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
		mdx.CleanupDevice();
		return (int)msg.wParam;
	} // /////////////////////////////////////////////////////////////////////////////
	HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow){  // Register class and create window
		// Register class
		static WNDCLASSEX wcex{};
		if(wcex.lpfnWndProc == 0){
			wcex.cbSize = sizeof(WNDCLASSEX);
			wcex.style = CS_HREDRAW | CS_VREDRAW;
			wcex.lpfnWndProc = tmpWndProc;
			wcex.cbClsExtra = 0;
			wcex.cbWndExtra = 0;
			wcex.hInstance = hInstance;
			wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
			wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
			wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
			wcex.lpszMenuName = NULL;
			wcex.lpszClassName = L"AMPC++WindowClass";
			wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
			if(!RegisterClassEx(&wcex))
				return E_FAIL;
		}
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
	LRESULT CALLBACK tmpWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
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
				if(model2.options.showDlg()){
					model2.Create();
					mdx.CleanupDevice();
#ifndef NEW_ENGINE // not NEW_ENGINE
					mdx.InitDevice(g_hWnd, model2.v_scr);
#else // NEW_ENGINE
					mdx.InitDevice(g_hWnd, mdx.cfg_all);
#endif // NEW_ENGINE
				}
				pauseRender = false;
				break;
			}
			case VK_PAUSE:
				break;
			default:
				model2.setConsole();
				printf("%d\n", (int)wParam);
				break;
			}
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		return 0;
	} // ////////////////////////////////////////////////////////////////////////////////////
}
