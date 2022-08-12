#include "Session.h"
using namespace tinyxml2;

void Session::create(const char* f_name){
	fname = strlen(f_name) == 0 ? "session.xml" : f_name;
	doc.DeleteChildren();
	XMLNode* options_node = options.create(&doc);
	if(options_node != NULL){
		//doc.NewComment("mycomment");
		XMLError errSave = doc.SaveFile(fname.c_str());
		if(errSave != XML_SUCCESS){ _RPT1(0, "errSave_create = %d\n", (int)errSave); }
	}
} // //////////////////////////////////////////////////////////////
void Session::load(const char* f_name){
	fname = strlen(f_name) == 0 ? "session.xml" : f_name;
	XMLError errLoad = doc.LoadFile(fname.c_str());
	if(errLoad == XML_SUCCESS){
		XMLNode* options_node = options.load(&doc);
	} else{
		create(fname.c_str());
	}
} // //////////////////////////////////////////////////////
void Session::save(const char* f_name){
	if(strlen(f_name) > 0)  
		fname = f_name;
	XMLError errSave = doc.SaveFile(fname.c_str());
} // ////////////////////////////////////////////////////////////////

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
const char* Session::get_maskA() const{
	return options.get_maskA();
} // //////////////////////////////////////////////////////////////
XMLNode* Session::set_maskA(const char* s){
	return options.set_maskA(s);
} // //////////////////////////////////////////////////////////////
