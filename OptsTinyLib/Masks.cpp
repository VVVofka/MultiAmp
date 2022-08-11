#include "pch.h"
#include "Masks.h"

void Masks::create(XMLNode* parent_node){
	XMLDocument* doc = parent_node->GetDocument();
	XMLElement* ele_out = doc->NewElement(XMLName);
	XMLNode* node = parent_node->InsertEndChild(ele_out);
	maskA.create(node);
	//maskF.create();
} // ///////////////////////////////////////////////////////
void Masks::load(XMLDocument& doc){
	maskA.load(doc);
} // ///////////////////////////////////////////////////////
