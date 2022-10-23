#include "pch.h"
#include "CppUnitTest.h"
#include "..\OptsTinyLib\myXML.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace tinyxml2;

namespace UTstOptsTinyLib{
	TEST_CLASS(UTstOptsTinyLib){
public:
	TEST_METHOD(Create){
		std::remove("tst1.xml"); // delete file
		MyXML xml("tst1.xml", "One;Two");
		std::string s;
		s = xml.getText("defstr");
		Assert::IsTrue(s == "defstr");
		
		xml.setText("hiHi");
		s = xml.getText("defstr");
		Assert::IsTrue(s == "hiHi");

		s = xml.getAttributeS("", "defstr");
		Assert::IsTrue(s == "defstr");

		xml.setAttributeS("attrib1", "val_atr1");
		s = xml.getAttributeS("attrib1", "defstr");
		Assert::IsTrue(s == "val_atr1");

		xml.setAttributeT<int>("attrib2", 77);
		int iret = xml.getAttributeT<int>("attrib2", 0);
		Assert::IsTrue(iret == 77);

		xml.setOrCreateNode(xml.node, "One;Two;four;five");
		xml.Save();
	} // ////////////////////////////////////////////////////////////////////////////

	};
}
