#include "pch.h"
#include "CppUnitTest.h"
#include "..\OptsTinyLib\structAll.h"
#include "..\AMPEngine2Lib\AMPEngine2Lib.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UTstEng2Lib{
	TEST_CLASS(UTstEng2Lib){
public:
	TEST_METHOD(TestMethod1){
		structAll cfgall;
		string sscr = "88 61 51 121 32 49 70 63 42 33 21 34 47 12 38 24 113 65 20 8 111 11 97 90 75 114 74 115 44 103 79 52 58 96 41 36 98";
		cfgall.data.fill_v(sscr);
	} // ////////////////////////////////////////////////////////////

private:

	}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
} // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
