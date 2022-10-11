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
	TEST_METHOD(tstFloat){
		float f = 0.5f;
		char buf[255];
		std::string s = float2sbin(f);
		float fout = sbin2float(s.c_str());
		sprintf(buf, "%f %s %f", f, s.c_str(), fout);
		Logger::WriteMessage(buf);
	} // //////////////////////////////////////////////////////////////////////////////
	std::string float2sbin(float f){
		char buf[33];
		sprintf(buf, "%X", *(__int32*)&f);
		return std::string(buf);
	} // //////////////////////////////////////////////////////////////////////////////
	float sbin2float(const char* s){
		__int32 i;
		sscanf_s(s, "%X", &i);
		return *((float*)&i);
	} // //////////////////////////////////////////////////////////////////////////////

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
	} // //////////////////////////////////////////////////////////////////////////////
	};
}
