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
		Assert::AreEqual(0, strcmp(s.c_str(), "C:\\Prog\\CPP\\MultiAmp\\Win32\\Debug"));
	}
	};
}
