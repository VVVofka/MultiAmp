#include "pch.h"
#include "CppUnitTest.h"
#include "..\adat\adat.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UTstAdat{
	TEST_CLASS(UTstAdat){
public:

	TEST_METHOD(maska){
		adat::CfgMaskA maska, maska2;
		int v[16] = {0,0,0,0,0,1,1,1,0,1,0,0,1,1,1,1};
		maska.set("0000011103001111");
		for(size_t j = 0; j < 16; j++)
			Assert::AreEqual(maska.v[j], v[j]);

		maska2.set("0000011103001111");
		Assert::IsTrue(maska == maska2);
		maska2.set("9000011103001111");
		Assert::IsTrue(maska != maska2);
	} // //////////////////////////////////////////////////////////////////////////////////////////
	TEST_METHOD(adat2){
		adat::CfgAll all;
		Assert::IsFalse(adat::load(all, ""));
		Assert::IsFalse(adat::save(all, ""));
	} // //////////////////////////////////////////////////////////////////////////////////
	};
}
