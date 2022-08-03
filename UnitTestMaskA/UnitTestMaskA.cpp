#include "pch.h"
#include "CppUnitTest.h"
#include "..\MultiAmp\MaskA4.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestMaskA{
	TEST_CLASS(UnitTestMaskA){
public:
	TEST_METHOD(TestMethod1){
		MaskA4 m;
		bool res = m.check();
	}
	};
}
