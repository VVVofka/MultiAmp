#include "pch.h"
#include "CppUnitTest.h"
#include "..\OptsTinyLib\structDataCfg.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UTstOptsTinyLib{
	TEST_CLASS(UTststructDataCfg){
		structDataCfg data;
		std::vector<size_t>& v = data.v;
public:
	TEST_METHOD(tst0){
		data.fill_v("");
		Assert::AreEqual(v.size(), (size_t)0);

		data.fill_v(" ");
		Assert::AreEqual(v.size(), (size_t)0);

		data.fill_v("-");
		Assert::AreEqual(v.size(), (size_t)0);

		data.fill_v("0");
		Assert::AreEqual(v.size(), (size_t)1);
		Assert::AreEqual(v[0], (size_t)0);

		data.fill_v(" 0 ");
		Assert::AreEqual(v.size(), (size_t)1);
		Assert::AreEqual(v[0], (size_t)0);

		data.fill_v(" 0 0 ");
		Assert::AreEqual(v.size(), (size_t)1);
		Assert::AreEqual(v[0], (size_t)0);

	} // ////////////////////////////////////////////////////////////////
	TEST_METHOD(tst1){
		data.fill_v("0");
		Assert::AreEqual(v.size(), (size_t)1);
		Assert::AreEqual(v[0], (size_t)0);

		data.fill_v("001");
		Assert::AreEqual(v.size(), (size_t)1);
		Assert::AreEqual(v[0], (size_t)1);

		data.fill_v(" 0 ");
		Assert::AreEqual(v.size(), (size_t)1);
		Assert::AreEqual(v[0], (size_t)0);

		data.fill_v("0 0");
		Assert::AreEqual(v.size(), (size_t)1);
		Assert::AreEqual(v[0], (size_t)0);

		data.fill_v(" 7 7 ");
		Assert::AreEqual(v.size(), (size_t)1);
		Assert::AreEqual(v[0], (size_t)7);
	} // ////////////////////////////////////////////////////////////////
	TEST_METHOD(tst2){
		data.fill_v("010 3 10");
		Assert::AreEqual(v.size(), (size_t)2);
		Assert::AreEqual(v[0], (size_t)10);
		Assert::AreEqual(v[1], (size_t)3);

		data.fill_v("0 0 3 -0 0 -3");
		Assert::AreEqual(v.size(), (size_t)2);
		Assert::AreEqual(v[0], (size_t)0);
		Assert::AreEqual(v[1], (size_t)3);
	} // ////////////////////////////////////////////////////////////////
	TEST_METHOD(tst4){
		data.fill_v("  471  010  3  10 00471  4710   ");
		Assert::AreEqual(v.size(), (size_t)4);
		Assert::AreEqual(v[0], (size_t)471);
		Assert::AreEqual(v[1], (size_t)10);
		Assert::AreEqual(v[2], (size_t)3);
		Assert::AreEqual(v[3], (size_t)4710);
	} // ////////////////////////////////////////////////////////////////
	}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
} // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
