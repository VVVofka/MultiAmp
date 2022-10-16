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
		std::remove("tst1.xml"); // delete file
		MyXML xml("tst1.xml", "One;Two");
		std::string s;
		s = xml.getText("defstr");
		Assert::IsTrue(s == "defstr");
		
		xml.setText("hiHi");
		s = xml.getText("defstr");
		Assert::IsTrue(s == "hiHi");

		s = xml.getAttribute("", "defstr");
		Assert::IsTrue(s == "defstr");

		xml.setAttribute("attrib1", "val_atr1");
		s = xml.getAttribute("attrib1", "defstr");
		Assert::IsTrue(s == "val_atr1");

		xml.setOrCreateNode(xml.node, "four;five");
		xml.Save();
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
