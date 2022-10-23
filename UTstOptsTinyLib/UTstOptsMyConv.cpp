#include "pch.h"
#include "CppUnitTest.h"
#include "..\OptsTinyLib\myconv.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UTstOptsTinyLib{
	TEST_CLASS(UTstOptsMyConv){
public:
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

		v = myconv::strToVInt("3691 945");
		Assert::AreEqual((size_t)2, v.size());
		Assert::AreEqual(v[0], (int)3691);
		Assert::AreEqual(v[1], (int)945);

		v = myconv::strToVInt("-3691 -945");
		Assert::AreEqual(v.size(), (size_t)2);
		Assert::AreEqual(v[0], (int)-3691);
		Assert::AreEqual(v[1], (int)-945);

		v = myconv::strToVInt("-36-945");
		Assert::AreEqual(v.size(), (size_t)2);
		Assert::AreEqual(v[0], (int)-36);
		Assert::AreEqual(v[1], (int)-945);

		v = myconv::strToVInt(" -3691+9452638");
		Assert::AreEqual(v.size(), (size_t)2);
		Assert::AreEqual(v[0], (int)-3691);
		Assert::AreEqual(v[1], (int)9452638);

		v = myconv::strToVInt(" -3691+945+-*@&$;; _=+-");
		Assert::AreEqual(v.size(), (size_t)2);
		Assert::AreEqual(v[0], (int)-3691);
		Assert::AreEqual(v[1], (int)945);
	} // ////////////////////////////////////////////////////////////////////////////
	TEST_METHOD(strToVSizet){
		std::vector<size_t> v;
		v = myconv::strToVSizet(" ");
		Assert::AreEqual(v.size(), (size_t)0);

		v = myconv::strToVSizet(" 0");
		Assert::AreEqual(v.size(), (size_t)1);
		Assert::AreEqual(v[0], (size_t)0);

		v = myconv::strToVSizet("- 0");
		Assert::AreEqual(v.size(), (size_t)1);
		Assert::AreEqual(v[0], (size_t)0);

		v = myconv::strToVSizet("+0 ");
		Assert::AreEqual(v.size(), (size_t)1);
		Assert::AreEqual(v[0], (size_t)0);

		v = myconv::strToVSizet("369.1;94,5+");
		Assert::AreEqual(v.size(), (size_t)4);
		Assert::AreEqual(v[0], (size_t)369);
		Assert::AreEqual(v[1], (size_t)1);
		Assert::AreEqual(v[2], (size_t)94);
		Assert::AreEqual(v[3], (size_t)5);

		v = myconv::strToVSizet("-.3691;-,945");
		Assert::AreEqual(v.size(), (size_t)2);
		Assert::AreEqual(v[0], (size_t)3691);
		Assert::AreEqual(v[1], (size_t)945);

		v = myconv::strToVSizet("-36-945");
		Assert::AreEqual(v.size(), (size_t)2);
		Assert::AreEqual(v[0], (size_t)36);
		Assert::AreEqual(v[1], (size_t)945);

		v = myconv::strToVSizet(" -3691+9452638");
		Assert::AreEqual(v.size(), (size_t)2);
		Assert::AreEqual(v[0], (size_t)3691);
		Assert::AreEqual(v[1], (size_t)9452638);

		v = myconv::strToVSizet(" -3691+945+-*@&$;; _=+-");
		Assert::AreEqual(v.size(), (size_t)2);
		Assert::AreEqual(v[0], (size_t)3691);
		Assert::AreEqual(v[1], (size_t)945);
	} // ////////////////////////////////////////////////////////////////////////////
	};
}
