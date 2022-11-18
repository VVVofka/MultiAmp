// AMPEngine2Lib.cpp : Defines the functions for the static library.
#include <Windows.h>
#include "framework.h"
#include "AMPEngine2Lib.h"
#include "wndAMP.h"
#include "MDX/MDX2.h"
#include "..\OptsTinyLib\structAll.h"
namespace eng2{

	MDX2 mdx;			// use:	wndAMP.cpp
	HWND g_hWnd;		// use:	wndAMP.cpp
	structAll* cfgall;	// use:	wndAMP.cpp

	int runEngine2Lib(HINSTANCE hInstance, int nCmdShow, structAll* cfg_all){
		cfgall = cfg_all;
		if(FAILED(InitWindow(hInstance, nCmdShow)))
			return E_NOINTERFACE;
		if(FAILED(mdx.InitDevice(g_hWnd, cfg_all))){
			mdx.CleanupDevice();
			return E_FAIL;
		}
		int ret = MainLoop();
		return ret;
	} // ///////////////////////////////////////////////////////////////////////////////////////////

} // namespace eng2 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@