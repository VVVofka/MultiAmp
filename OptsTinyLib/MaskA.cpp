#include "MaskA.h"
using namespace tinyxml2;

void MaskA::create(XMLElement* parent_element){
	v.clear();
	v.reserve(16);
	for(int j = 0; j < 16; j++)
		v.push_back(defval[j]);
	element = parent_element->InsertNewChildElement(XMLName);
	element->SetText(v.c_str());
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
