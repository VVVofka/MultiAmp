// DlgMaskA.cpp : Defines the functions for the static library.
#include "pch.h"
#include "framework.h"
#include "DlgMaskA.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CWinApp theApp;     // The one and only application object
using namespace std;
int main(){
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(nullptr);

	if(hModule != nullptr){
		// initialize MFC and print and error on failure
		if(!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0)){
			// TODO: code your application's behavior here.
			wprintf(L"Fatal Error: MFC initialization failed\n");
			nRetCode = 1;
		} else{
			// TODO: code your application's behavior here.
		}
	} else{
		// TODO: change error code to suit your needs
		wprintf(L"Fatal Error: GetModuleHandle failed\n");
		nRetCode = 1;
	}

	return nRetCode;
}
// TODO: This is an example of a library function
void fnDlgMaskA(){}
