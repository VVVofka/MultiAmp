#include "MaskF.h"
using namespace tinyxml2;

MaskF::MaskF(){
	v.resize(size, '0');
	defval.resize(size, '0');
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
XMLNode* MaskF::set(XMLNode* parent_node, const char* s_in){
	if(s_in == NULL)
		s_in = defval.c_str();
	v = defval;
	isChange = false;
	size_t j_in = 0, j_v = 0;
	const char* s = s_in;
	while(s_in[j_in] != '/0'){
		if(s[j_in] >= '0' && s[j_in] < '9'){
			v[j_v] = s[j_in];
			if(++j_v >= size)
				break;
		}
		if((j_in++) / 2 > size)
			break;;
	}

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

	std::string z(16, '\0');
	char sbin[5]; sbin[4] = 0;
	for(int j = 0; j < 16; j++){
		XMLElement* element = doc->NewElement(("i" + std::to_string(j)).c_str());

		for(int n = 0; n < 4; n++){
			unsigned i = (j >> n) & 1;
			sbin[3 - n] = std::to_string(i)[0];
		}
		element->SetAttribute("bin", sbin);

		for(size_t cell = 0; cell < 4; cell++){
			z = v.substr(j * 16 + cell * 4, 4);
			element->SetAttribute(("cell" + std::to_string(cell)).c_str(), z.c_str());
		}
		node->InsertEndChild(element);
	}	//	for(int j = 0; j < 16; j++)
	return node;
} // ////////////////////////////////////////////////////////////////////
