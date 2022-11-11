// AMPEngine2Lib.cpp : Defines the functions for the static library.
#include <Windows.h>
#include "framework.h"
#include "AMPEngine2Lib.h"
#include "wndAMP.h"

namespace eng2{

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

} // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@