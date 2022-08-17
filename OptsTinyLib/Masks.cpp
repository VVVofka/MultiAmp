#include "pch.h"
#include "Masks.h"
#include <string>

XMLNode* Masks::create(XMLNode* parent_node){
	XMLDocument* doc = parent_node->GetDocument();
	XMLElement* ele_out = doc->NewElement(XMLName);
	node = parent_node->InsertEndChild(ele_out);
	XMLNode* maskA_node = maskA.create(node);
	XMLNode* maskF_node = maskF.create(node);
	if(maskA_node == NULL || maskF_node == NULL)
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
			XMLNode* maskF_node = maskF.load(curnode);
			if(maskA_node != NULL || maskF_node == NULL)
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
const char* Masks::get_maskF() const{
	return maskF.get_s();
} // //////////////////////////////////////////////////////////
XMLNode* Masks::set_maskF(const char* s){
	return maskF.set(node, s);
} // ///////////////////////////////////////////////////////////
