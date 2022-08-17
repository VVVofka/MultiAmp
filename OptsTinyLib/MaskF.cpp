#include "MaskF.h"
using namespace tinyxml2;

MaskF::MaskF(){
	v.resize(16 * 16, '0');
	defval.resize(16 * 16, '0');
} // //////////////////////////////////////////////////////////////////////////////
XMLNode* MaskF::create(XMLNode* parent_node){
	return set(parent_node, defval.c_str());
} // /////////////////////////////////////////////////////////////////////////////
XMLNode* MaskF::load(XMLNode* parent_node){
	node = NULL;
	for(XMLNode* curnode = parent_node->FirstChild(); curnode; curnode = curnode->NextSibling()){
		XMLElement* ele = curnode->ToElement();
		std::string name(ele->Name());
		if(name == XMLName){
			const char* val = ele->Attribute("val");	//	, defval
			parent_node->DeleteChild(curnode);
			node = set(parent_node, val);
			break;
		}
	}
	return node;
} // //////////////////////////////////////////////////////////////
const char* MaskF::get_s() const{
	return v.c_str();
} // /////////////////////////////////////////////////////////////////////
XMLNode* MaskF::set(XMLNode* parent_node, const char* s){
	if(s == NULL)
		s = defval.c_str();
	isChange = false;
	for(int j = 0; j < 16; j++){
		isChange = isChange || (v[j] != s[j]);
		v[j] = s[j];
		if(s[j] != '0' && s[j] != '1' && s[j] != '2' && s[j] != '3' && s[j] != '4' && s[j] != '5' && s[j] != '6' && s[j] != '7' && s[j] != '8'){
			v[j + 1] = '\0';
			return NULL;
		}
	}
	v[16] = '\0';

	// If exist, delete node *****************
	for(XMLNode* curnode = parent_node->FirstChild(); curnode; curnode = curnode->NextSibling()){
		XMLElement* ele = curnode->ToElement();
		std::string name(ele->Name());
		if(name == XMLName){
			parent_node->DeleteChild(curnode);
			break;
		}
	}
	//****************

	XMLDocument* doc = parent_node->GetDocument();
	XMLElement* ele_out = doc->NewElement(XMLName);

	ele_out->SetAttribute("val", v.c_str());	// "012345678"
	node = parent_node->InsertEndChild(ele_out);

	//char z[2];	z[1] = 0;
	//char sbin[5]; sbin[4] = 0;
	//for(int j = 0; j < 16; j++){
	//	XMLElement* element = doc->NewElement(("id" + std::to_string(j)).c_str());

	//	unsigned cnt = 0;
	//	for(int n = 0; n < 4; n++){
	//		unsigned i = (j >> n) & 1;
	//		cnt += i;
	//		sbin[3 - n] = std::to_string(i)[0];
	//	}
	//	element->SetAttribute("bin", sbin);
	//	element->SetAttribute("cnt", cnt);

	//	z[0] = v[j];
	//	element->SetAttribute("val", z);

	//	node->InsertEndChild(element);
	//}	//	for(int j = 0; j < 16; j++)
	return node;
} // ////////////////////////////////////////////////////////////////////
