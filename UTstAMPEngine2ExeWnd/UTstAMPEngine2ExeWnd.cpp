#include "CppUnitTest.h"
#include "..\AMPEngine2Exe\AMPEngine2Exe.h"
#include <Windows.h>
#include <libloaderapi.h>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UTstAMPEngine2ExeWnd{
	TEST_CLASS(UTstAMPEngine2ExeWnd){
public:
	TEST_METHOD(TestMainEntry){
		//CoCreateInstanceFromApp()
#define MAX_LOADSTRING 100
		extern WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
		extern WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

		wcscpy_s(szTitle, L"myTitledbg");
		wcscpy_s(szWindowClass, L"myDbgWindClass");
		mymain(NULL, NULL, L"tst.xml");

	} // /////////////////////////////////////////////////////////////////////////////////////
	};
}
