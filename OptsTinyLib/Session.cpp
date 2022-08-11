#include "Session.h"
using namespace tinyxml2;

void Session::load(const char* f_name){
	fname = strlen(f_name) == 0 ? "session.xml" : f_name;
	XMLError errLoad = doc.LoadFile(fname.c_str());
	if(errLoad != XML_SUCCESS){
		create(fname.c_str());
	} else{
		XMLError errSave = doc.SaveFile(("new_" + fname).c_str());
		_RPT1(0, "errSave1 = %d\n", (int)errSave);

	}

} // //////////////////////////////////////////////////////
//		<element>
//			<!--comment-->
//			<sub attrib="0" />
//			<sub attrib="1" />
//			<sub attrib="2" >& Text!</sub>
//		<element>

void Session::tstcrt(){
	XMLElement* sub[3] = {doc.NewElement("sub"), doc.NewElement("sub"), doc.NewElement("sub")};
	for(int i = 0; i < 3; ++i)
		sub[i]->SetAttribute("attrib", i);
	XMLElement* ele_out = doc.NewElement("element");
	XMLNode* node = doc.InsertEndChild(ele_out);
	node->InsertEndChild(sub[2]);

	XMLError errSave = doc.SaveFile("crt.xml");
	_RPT1(0, "errSave3 = %d\n", (int)errSave);
} // //////////////////////////////////////////////////////////
void Session::create(const char* fname){
	opts.create(&doc);
	//doc.NewComment("mycomment");
	XMLError errSave = doc.SaveFile(("new_" + std::string(fname)).c_str());
	_RPT1(0, "errSave_create = %d\n", (int)errSave);
} // //////////////////////////////////////////////////////////////
