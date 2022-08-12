#include "Options.h"
using namespace tinyxml2;

bool Options::create(XMLDocument* doc){
	XMLElement* ele_out = doc->NewElement(XMLName);
	XMLNode* node = doc->InsertEndChild(ele_out);
	bool bmasks = masks.create(node);
	return bmasks;
} // ///////////////////////////////////////////////////////////
bool Options::load(XMLDocument* doc){
	bool bmasks = false;
	for(XMLNode* node = doc->FirstChild(); node; node = node->NextSibling()){
		XMLElement* ele = node->ToElement();
		std::string name(ele->Name());
		if(name == XMLName){
			bmasks = masks.load(node);
			break;
		}
	}
	return bmasks;
} // ///////////////////////////////////////////////////////////
