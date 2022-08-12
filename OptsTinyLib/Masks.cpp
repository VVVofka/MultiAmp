#include "pch.h"
#include "Masks.h"
#include <string>

XMLNode* Masks::create(XMLNode* parent_node){
	XMLDocument* doc = parent_node->GetDocument();
	XMLElement* ele_out = doc->NewElement(XMLName);
	node = parent_node->InsertEndChild(ele_out);
	XMLNode* maskA_node = maskA.create(node);
	if(maskA_node == NULL)
		node = NULL;
	return node;
} // ///////////////////////////////////////////////////////
XMLNode* Masks::load(XMLNode* parent_node){
	node = NULL;
	for(XMLNode* curnode = parent_node->FirstChild(); curnode; curnode = curnode->NextSibling()){
		XMLElement* ele = curnode->ToElement();
		std::string name(ele->Name());
		if(name == XMLName){
			XMLNode* maskA_node = maskA.load(curnode);
			// TODO: maskf
			if(maskA_node != NULL)
				node = curnode;
			break;
		}
	}
	return node;
} // ///////////////////////////////////////////////////////
const char* Masks::get_maskA() const{
	return maskA.get_s();
} // //////////////////////////////////////////////////////////
XMLNode* Masks::set_maskA(const char* s){
	return maskA.set(node, s);
} // ///////////////////////////////////////////////////////////
