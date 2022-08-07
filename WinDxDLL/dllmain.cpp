// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "Main.h"

BOOL APIENTRY DllMain(HMODULE hinstDLL, DWORD  fdwReason, LPVOID lpvReserved){
	switch(fdwReason){
	case DLL_PROCESS_ATTACH:	// DLL load due to process initialization or LoadLibrary
	case DLL_THREAD_ATTACH:     // The attached process creates a new thread
	case DLL_THREAD_DETACH:     // The thread of the attached process terminates
	case DLL_PROCESS_DETACH:    // DLL unload due to process termination or FreeLibrary
    default:
        break;
	}
	return TRUE;
    UNREFERENCED_PARAMETER(hinstDLL);
    UNREFERENCED_PARAMETER(lpvReserved);
} // /////////////////////////////////////////////////////////////////////

