#include "pch.h"
#include <string>
#include "CppUnitTest.h"
#include "..\MultiAmp\MaskA4.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace maska;
using namespace std;
namespace UTstOptions{
	TEST_CLASS(UTstOptions){
public:

	TEST_METHOD(TestMethod1){
		MaskA4 maska;
		auto r = maska.check();
		//Assert::IsFalse(maska.check());
		//maska.setdef();
		//string s = maska.gets();
		//Assert::AreEqual(s, maska.s_def);
		//unsigned u = maska.getu();
		//Assert::AreEqual(u, (unsigned)0b1111111011101000);
	}
	};
}
