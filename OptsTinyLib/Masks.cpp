#include "pch.h"
#include "Masks.h"
#include <string>

bool Masks::create(XMLNode* parent_node){
	XMLDocument* doc = parent_node->GetDocument();
	XMLElement* ele_out = doc->NewElement(XMLName);
	XMLNode* node = parent_node->InsertEndChild(ele_out);
	bool bmaskA = maskA.create(node);
	return bmaskA;
} // ///////////////////////////////////////////////////////
bool Masks::load(XMLNode* parent_node){
	bool bmaskA = false;
	for(XMLNode* node = parent_node->FirstChild(); node; node = node->NextSibling()){
		XMLElement* ele = node->ToElement();
		std::string name(ele->Name());
		if(name == XMLName){
			bmaskA = maskA.load(node);
			break;
		}
	}
	return bmaskA;
} // ///////////////////////////////////////////////////////
