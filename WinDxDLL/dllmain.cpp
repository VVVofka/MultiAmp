// dllmain.cpp : Defines the entry point for the DLL application.
#include "NewEngine.h"
#include <Windows.h>
#include "mywnd.h"
#include "..\OptsTinyLib\structAll.h"
#include "Main.h"

BOOL APIENTRY DllMain(HMODULE hModule,
					   DWORD  ul_reason_for_call,
					   LPVOID lpReserved
){
	switch(ul_reason_for_call){
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}
	return TRUE;
} // /////////////////////////////////////////////////////////////////////
// TODO: rename
extern "C" _declspec(dllexport) int openWindow1json(HINSTANCE hInstance, int nCmdShow, structAll* cfg_all){
	int ret = 0;
	ret = mn(hInstance, nCmdShow, cfg_all);	// def in Main.h;  Body in DXInterOp.cpp
	//ret = mywnd::run(hInstance, nCmdShow, cfg_all);
	return ret;
} // //////////////////////////////////////////////////////////////////////////////////

