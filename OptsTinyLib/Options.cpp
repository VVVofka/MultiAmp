#include "Options.h"
using namespace tinyxml2;

XMLNode* Options::create(XMLDocument* doc){
	XMLElement* ele_out = doc->NewElement(XMLName);
	node = doc->InsertEndChild(ele_out);
	XMLNode* masks_node = masks.create(node);
	if(masks_node == NULL)
		node = NULL;
	return node;
} // ///////////////////////////////////////////////////////////
XMLNode* Options::load(XMLDocument* doc){
	node = NULL;
	for(XMLNode* curnode = doc->FirstChild(); curnode; curnode = curnode->NextSibling()){
		XMLElement* ele = curnode->ToElement();
		std::string name(ele->Name());
		if(name == XMLName){
			XMLNode* masks_node = masks.load(curnode);
			if(masks_node != NULL)
				node = curnode;
			break;
		}
	}
	return node;
} // ///////////////////////////////////////////////////////////
const char* Options::get_maskA() const{
	return masks.get_maskA();
} // ////////////////////////////////////////////////////////////////
XMLNode* Options::set_maskA(const char* s){
	return masks.set_maskA(s);
} // ////////////////////////////////////////////////////////////////////
