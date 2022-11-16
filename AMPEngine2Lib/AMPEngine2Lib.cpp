// AMPEngine2Lib.cpp : Defines the functions for the static library.
#include <Windows.h>
#include "framework.h"
#include "AMPEngine2Lib.h"
#include "wndAMP.h"
#include "MDX/MDX2.h"
namespace eng2{
	int runEngine2Lib(HINSTANCE hInstance, int nCmdShow, structAll* cfg_all){
		if(FAILED(InitWindow(hInstance, nCmdShow)))
			return E_NOINTERFACE;
		if(FAILED(mdx.InitDevice(g_hWnd, cfg_all))){
		//	mdx.CleanupDevice();
			return E_FAIL;
		}
		//return work();
		return 8;
	} // ///////////////////////////////////////////////////////////////////////////////////////////

} // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@