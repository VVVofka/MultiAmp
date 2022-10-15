#include "pch.h"
#include "CppUnitTest.h"
#include "..\OptsTinyLib\myXML.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace tinyxml2;

namespace UTstOptsTinyLib{
	TEST_CLASS(UTstOptsTinyLib){
public:
	TEST_METHOD(getNode_NULL){
		const char* tstFileNull = "tst.xml";
		XMLNode* node = myxml::getNode(tstFileNull, "");
		Assert::IsNull(node);
		node = myxml::getNode(tstFileNull, ";");
		Assert::IsNull(node);
		node = myxml::getNode(tstFileNull, ";;");
		Assert::IsNull(node);
		node = myxml::getNode(tstFileNull, "One");
		Assert::IsNull(node);
		node = myxml::getNode(tstFileNull, ";One");
		Assert::IsNull(node);
		node = myxml::getNode(tstFileNull, "One;");
		Assert::IsNull(node);
		node = myxml::getNode(tstFileNull, ";One;");
		Assert::IsNull(node);
		node = myxml::getNode(tstFileNull, ";One;");
		Assert::IsNull(node);
		node = myxml::getNode(tstFileNull, ";One;Two");
		Assert::IsNull(node);
		node = myxml::getNode(tstFileNull, ";One;Two;");
		Assert::IsNull(node);
	} // ////////////////////////////////////////////////////////////////////////////
	TEST_METHOD(Create){
		const char* tstFile = "tstCreate.xml";
		XMLDocument doc;
		doc.SaveFile(tstFile); // clear
		XMLNode* node = myxml::getNode(tstFile, "One1");
		Assert::IsNull(node);
		node = myxml::getOrCreateNode(tstFile, "One1");
		Assert::IsNotNull(node);
		myxml::setText(node, "tst1");
		std::string s = myxml::getText(node, "defval1");
		Assert::IsTrue(s == "One1");
	} // ////////////////////////////////////////////////////////////////////////////
	//TEST_METHOD(CreateDefault){
	//	Session session;
	//	session.create();
	//	std::string smaska = session.get_maskA();
	//	Assert::IsTrue(smaska == DEFMASKA);
	//}
	//TEST_METHOD(ChangeMaskA){
	//	const char tstmask[] = "0101010101010101";
	//	Session session1, session2;
	//	session1.create("ChangeMaskA1.xml");
	//	session1.set_maskA(tstmask);
	//	session1.save("ChangeMaskA2.xml");
	//	session2.load("ChangeMaskA2.xml");
	//	std::string smaska2 = session2.get_maskA();
	//	Assert::IsTrue(smaska2 == tstmask);

	//	std::string smaska1 = session1.get_maskA();
	//	Assert::IsTrue(smaska1 == tstmask);
	//	session1.load("ChangeMaskA1.xml");
	//	std::string smaska1reload = session1.get_maskA();
	//	Assert::IsTrue(smaska1reload == DEFMASKA);
	//}
	};
}
