// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
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
extern "C" _declspec(dllexport) int tstdll(HINSTANCE hInstance, int nCmdShow, int a, int b){
	int ret = tstdllMain(hInstance, nCmdShow, a, b);
	return ret;
} // //////////////////////////////////////////////////////////////////////////////////
extern "C" _declspec(dllexport) int openWindow1(HINSTANCE hInstance, int nCmdShow, int a, int b){
	openwnd(hInstance, nCmdShow);
	return a + b;
} // //////////////////////////////////////////////////////////////////////////////////

