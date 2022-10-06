#include "pch.h"
#include "CppUnitTest.h"
#include "..\FileNames\FileNames.h"

//#include <windows.h>
//#include <stdio.h>
//
//#include <direct.h>
//#include <Shlwapi.h>
//#pragma comment(lib, "shlwapi.lib")

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UTstFileNames{
	TEST_CLASS(UTstFileNames){
public:

	TEST_METHOD(TestMethod1){
		auto s = curDir();
		Assert::IsTrue(s.size() > 0);
#ifdef _DEBUG

#ifdef MYWIN32
		Assert::AreEqual(0, strcmp(s.c_str(), "C:\\Prog\\CPP\\MultiAmp\\Win32\\Debug"));
#else // WIN32
		Assert::AreEqual(0, strcmp(s.c_str(), "C:\\Prog\\CPP\\MultiAmp\\x64\\Debug"));
#endif // WIN32

#else // DEBUG

#ifdef MYWIN32
		Assert::AreEqual(0, strcmp(s.c_str(), "C:\\Prog\\CPP\\MultiAmp\\Win32\\Release"));
#else // WIN32
		Assert::AreEqual(0, strcmp(s.c_str(), "C:\\Prog\\CPP\\MultiAmp\\x64\\Release"));
#endif // WIN32

#endif // DEBUG

	}
	};
}
