#include "MaskA.h"
using namespace tinyxml2;

bool MaskA::create(XMLNode* parent_node){
	return set(parent_node, defval);
} // /////////////////////////////////////////////////////////////////////////////

bool MaskA::load(XMLNode* parent_node){
	// TODO: ---
	XMLError err = XML_SUCCESS;

	if(err != XML_SUCCESS){
	}
	return true;
} // //////////////////////////////////////////////////////////////
unsigned MaskA::get_uns() const {
	unsigned sum = 0;
	for(int j = 0; j < 16; j++)
		if(v[j] == '1')
			sum += (1 << j);
	return sum;
} // //////////////////////////////////////////////////////////////////
bool MaskA::set(XMLNode* parent_node, const char* s){
	if(s == NULL)
		s = defval;
	isChange = false;
	for(int j = 0; j < 16; j++){
		isChange = isChange || (v[j] != s[j]);
		v[j] = s[j];
		if(s[j] != '0' && s[j] != '1'){
			v[j + 1] = '\0';
			return false;
		}
	}
	v[16] = '\0';

	XMLDocument* doc = parent_node->GetDocument();
	
	if(isChange){
		//doc->Get()
	}

	XMLElement* ele_out = doc->NewElement(XMLName);

	ele_out->SetAttribute("val", v);
	unsigned uns = get_uns();
	ele_out->SetAttribute("uns", uns);

	XMLNode* node = parent_node->InsertEndChild(ele_out);

	char z[2];	z[1] = 0;
	char sbin[5]; sbin[4] = 0;
	for(int j = 0; j < 16; j++){
		XMLElement* element = doc->NewElement(std::to_string(j).c_str());

		unsigned cnt = 0;
		for(int n = 0; n < 4; n++){
			unsigned i = (j >> n) & 1;
			cnt += i;
			sbin[3 - n] = std::to_string(i)[0];
		}
		element->SetAttribute("bin", sbin);
		element->SetAttribute("cnt", cnt);

		z[0] = v[j];
		element->SetAttribute("val", z);

		node->InsertEndChild(element);
	}	//	for(int j = 0; j < 16; j++)
	return true;
} // ////////////////////////////////////////////////////////////////////
