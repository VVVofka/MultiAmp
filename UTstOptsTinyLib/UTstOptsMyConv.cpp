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

		v = myconv::strToVInt("0  -3691+945+-*@&$;; _=+-0");
		Assert::AreEqual(v.size(), (size_t)4);
		Assert::AreEqual(v[0], (int)0);
		Assert::AreEqual(v[1], (int)-3691);
		Assert::AreEqual(v[2], (int)945);
		Assert::AreEqual(v[3], (int)0);

		v = myconv::strToVInt("  0  -3691+945+-*@&$;; _=+- 0  ");
		Assert::AreEqual(v.size(), (size_t)4);
		Assert::AreEqual(v[0], (int)0);
		Assert::AreEqual(v[1], (int)-3691);
		Assert::AreEqual(v[2], (int)945);
		Assert::AreEqual(v[3], (int)0);

		v = myconv::strToVInt("  0  -3691+945+-*@&$;; _=+- 0  ");
		Assert::AreEqual(v.size(), (size_t)4);
		Assert::AreEqual(v[0], (int)0);
		Assert::AreEqual(v[1], (int)-3691);
		Assert::AreEqual(v[2], (int)945);
		Assert::AreEqual(v[3], (int)0);
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

	TEST_METHOD(strToVFloat){
		std::vector<float> v;
		const float tol = 0.00001f;
		v = myconv::strToVFloat("");
		Assert::AreEqual((size_t)0, v.size(), L"0");

		v = myconv::strToVFloat(" ");
		Assert::AreEqual((size_t)0, v.size(), L"0");

		v = myconv::strToVFloat(" 0");
		Assert::AreEqual((size_t)1, v.size(), L"Check:1a");
		Assert::AreEqual(0.f, v[0], tol, L"Check:1b");

		v = myconv::strToVFloat("- 0,");
		Assert::AreEqual((size_t)1, v.size(), L"2");
		Assert::AreEqual(0.f, v[0], tol, L"2");

		v = myconv::strToVFloat("+0. ");
		Assert::AreEqual((size_t)1, v.size(), L"3");
		Assert::AreEqual(0.f, v[0], tol, L"3");

		v = myconv::strToVFloat("1.273 -034,890 +-.0 -.0910&");
		Assert::AreEqual((size_t)4, v.size(), L"4");
		Assert::AreEqual(1.273f, v[0], tol, L"4");
		Assert::AreEqual(-34.89f, v[1], tol, L"4");
		Assert::AreEqual(0.f, v[2], tol, L"4");
		Assert::AreEqual(-0.091f, v[3], tol, L"4");

		v = myconv::strToVFloat("^^-.36*91;-,%945--+---345,23f-");
		Assert::AreEqual((size_t)3, v.size(), L"5a");
		Assert::AreEqual(-0.3691f, v[0], tol, L"5b");
		Assert::AreEqual(-0.945f, v[1], tol, L"5c");
		Assert::AreEqual(-345.23f, v[2], tol, L"5d");

		v = myconv::strToVFloat("..");
		Assert::AreEqual((size_t)2, v.size(), L"6a");
		Assert::AreEqual(0.f, v[0], tol, L"6b");
		Assert::AreEqual(0.f, v[1], tol, L"6b");

		v = myconv::strToVFloat("---345,2");
		Assert::AreEqual(-345.f, v[0], tol, L"7a");

	} // ////////////////////////////////////////////////////////////////////////////};
	};
}
