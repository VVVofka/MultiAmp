//#include "pch.h"
#include "CppUnitTest.h"
#include "..\AMPEngine2Exe\ParseCmdLine.h"
#include <string>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UTstAMPEngine2Exe{
	TEST_CLASS(UTstAMPEngine2ExeParse){
public:
	TEST_METHOD(TestMethod1){
		ParseCmdLine prs;
		prs.parse((LPWSTR)L"");
		Assert::AreEqual((int)prs.tick_cnt, -1);
		Assert::AreEqual(prs.fname, string(prs.def_fname));

		prs.parse((LPWSTR)L" ");
		Assert::AreEqual((int)prs.tick_cnt, -1);
		Assert::AreEqual(prs.fname, string(prs.def_fname));

		prs.parse((LPWSTR)L"  ");
		Assert::AreEqual((int)prs.tick_cnt, -1);
		Assert::AreEqual(prs.fname, string(prs.def_fname));

		prs.parse((LPWSTR)L"myfile.xml");
		Assert::AreEqual((int)prs.tick_cnt, -1);
		Assert::AreEqual(prs.fname, string("myfile.xml"));

		prs.parse((LPWSTR)L"my file.xml");
		Assert::AreEqual((int)prs.tick_cnt, -1);
		Assert::AreEqual(prs.fname, string("my"));

		prs.parse((LPWSTR)L"myfile.xml 5");
		Assert::AreEqual((int)prs.tick_cnt, 5);
		Assert::AreEqual(prs.fname, string("myfile.xml"));

		prs.parse((LPWSTR)L"my file.xml 6");
		Assert::AreEqual((int)prs.tick_cnt, 6);
		Assert::AreEqual(prs.fname, string("my"));

		prs.parse((LPWSTR)L"7");
		Assert::AreEqual((int)prs.tick_cnt, -1);
		Assert::AreEqual(prs.fname, string("7"));

		prs.parse((LPWSTR)L"myfile.xml asd0 7  2");
		Assert::AreEqual((int)prs.tick_cnt, 72);
		Assert::AreEqual(prs.fname, string("myfile.xml"));

		prs.parse((LPWSTR)L"`myfile.xml` asd1 73");
		Assert::AreEqual((int)prs.tick_cnt, 173);
		Assert::AreEqual(prs.fname, string("myfile.xml"));

		prs.parse((LPWSTR)L" \"myfile.xml` a sd1 73 ");
		Assert::AreEqual((int)prs.tick_cnt, -1);
		Assert::AreEqual(prs.fname, string("myfile.xml` a sd1 73"));

		prs.parse((LPWSTR)L" ` myfile.xml ` asd1 75 ");
		Assert::AreEqual((int)prs.tick_cnt, 175);
		Assert::AreEqual(prs.fname, string("myfile.xml"));
	} // /////////////////////////////////////////////////////////////////////////////
	};
}
