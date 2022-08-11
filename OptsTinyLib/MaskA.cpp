#include "MaskA.h"
using namespace tinyxml2;

void MaskA::create(XMLNode* parent_node){
	v = defval;
	XMLDocument* doc = parent_node->GetDocument();
	XMLElement* ele_out = doc->NewElement(XMLName);

	ele_out->SetAttribute("val", v.c_str());
	ele_out->SetAttribute("uns", get_uns());
	
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
unsigned MaskA::get_uns() const {
	unsigned sum = 0;
	for(int j = 0; j < 16; j++)
		if(v[j] == '1')
			sum += (1 << j);
	return sum;
} // //////////////////////////////////////////////////////////////////
bool MaskA::set(const std::string& s){
	if(s.size() != 16)
		return false;
	if(v.size() != 16)
		v.resize(16);
	for(int j = 0; j < 16; j++){
		if(s[j] != '0' && s[j] != '1')
			return false;
		v[j] = s[j];
	}
	return true;
} // ////////////////////////////////////////////////////////////////////
