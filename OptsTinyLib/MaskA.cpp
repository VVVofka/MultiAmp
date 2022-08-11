#include "MaskA.h"
using namespace tinyxml2;

void MaskA::create(XMLNode* parent_node){
	v.clear();
	v.reserve(16);
	for(int j = 0; j < 16; j++)
		v.push_back(defval[j]);

	XMLDocument* doc = parent_node->GetDocument();
	XMLElement* ele_out = doc->NewElement(XMLName);
	ele_out->SetAttribute("val", v.c_str());
	XMLNode* node = parent_node->InsertEndChild(ele_out);

	//char z[2];
	//z[1] = 0;
	//for(int j = 0; j < 16; j++){
	//	z[0] = v[j];
	//	XMLElement* element = doc->NewElement(z);
	//	element->SetAttribute("index", j);
	//	node->InsertEndChild(element);
	//}
} // //////////////////////////////////////////////////////////////
void MaskA::load(XMLDocument& doc){
	// TODO: ---
	XMLError err = XML_SUCCESS;

	if(err != XML_SUCCESS){
		v.clear();
		v.reserve(16);
		for(int j = 0; j < 16; j++)
			v.push_back(defval[j]);
		XMLElement* element1 = doc.NewElement("MaskA");
		element1->SetText(v.c_str());
		doc.InsertEndChild(element1);
		doc.SaveFile("session.xml");
	}
} // //////////////////////////////////////////////////////////////
