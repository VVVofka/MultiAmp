#include "pch.h"
#include "CppUnitTest.h"
#include "..\OptsTinyLib\myconv.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UTstOptsTinyLib{
	TEST_CLASS(UTstOptsMyConv){
public:
	TEST_METHOD(sizet_str){
		std::string s;
		s = myconv::size_tToStr(0);
		Assert::AreEqual(s.c_str(), "0");
		s = myconv::size_tToStr(234745624);
		Assert::AreEqual(s.c_str(), "234745624");
	} // ////////////////////////////////////////////////////////////////////////////
	TEST_METHOD(str_sizet){
		size_t s;
		s = myconv::strToSize_t("0");
		Assert::AreEqual(s, (size_t)0);

		s = myconv::strToSize_t("+0");
		Assert::AreEqual(s, (size_t)0);

		s = myconv::strToSize_t("-0");
		Assert::AreEqual(s, (size_t)0);

		s = myconv::strToSize_t("234745624");
		Assert::AreEqual(s, (size_t)234745624);
	} // ////////////////////////////////////////////////////////////////////////////
	TEST_METHOD(strToVInt){
		std::vector<int> v;
		v = myconv::strToVInt("");
		Assert::AreEqual(v.size(), (size_t)0);

		v = myconv::strToVInt("0");
		Assert::AreEqual(v.size(), (size_t)1);
		Assert::AreEqual(v[0], (int)0);

		v = myconv::strToVInt("-0");
		Assert::AreEqual(v.size(), (size_t)1);
		Assert::AreEqual(v[0], (int)0);

		v = myconv::strToVInt("+0");
		Assert::AreEqual(v.size(), (size_t)1);
		Assert::AreEqual(v[0], (int)0);

		v = myconv::strToVInt("3691;945");
		Assert::AreEqual(v.size(), (size_t)2);
		Assert::AreEqual(v[0], (int)3691);
		Assert::AreEqual(v[1], (int)945);

		v = myconv::strToVInt("-3691;-945");
		Assert::AreEqual(v.size(), (size_t)2);
		Assert::AreEqual(v[0], (int)-3691);
		Assert::AreEqual(v[1], (int)-945);

		v = myconv::strToVInt("-3691-945");
		Assert::AreEqual(v.size(), (size_t)2);
		Assert::AreEqual(v[0], (int)-3691);
		Assert::AreEqual(v[1], (int)-945);

		v = myconv::strToVInt(" -3691+945");
		Assert::AreEqual(v.size(), (size_t)2);
		Assert::AreEqual(v[0], (int)-3691);
		Assert::AreEqual(v[1], (int)945);
	} // ////////////////////////////////////////////////////////////////////////////
	};
}
