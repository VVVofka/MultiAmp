#include "pch.h"
#include "DataCfg.h"
#include <string>
XMLNode* DataCfg::create(XMLNode* parent_node){
	structDataCfg new_cfg;
	new_cfg.v.resize(1);
	new_cfg.v[0] = 0;
	return set(parent_node, new_cfg);
} // ///////////////////////////////////////////////////////////////////////////////////
XMLNode* DataCfg::load(XMLNode* parent_node){
	node = NULL;
	for(XMLNode* curnode = parent_node->FirstChild(); curnode; curnode = curnode->NextSibling()){
		XMLElement* ele = curnode->ToElement();
		std::string name(ele->Name());
		if(name == XMLName){
			size_t size = ele->IntAttribute("size", 1);
			cfg.seed = ele->UnsignedAttribute("seed", 1234567);

			const char* pchar = ele->Attribute("sigma");
			cfg.sigma = (pchar == NULL) ? 0 : sbin2float(pchar);
			
			std::string sin = ele->GetText();

			cfg.fill_v(sin);
			if(cfg.v.size() != size){
				printf("bad attribute size dataCfg");
				_RPT2(0, "bad attribute size dataCfg cfg.v.size=%u attribute=%u\n", cfg.v.size(), size);
			}
			parent_node->DeleteChild(curnode);
			node = set(parent_node, cfg);
			return node;
		}
	}
	node = set(parent_node, cfg);
	return node;
} // ///////////////////////////////////////////////////////////////////////////////////
XMLNode* DataCfg::set(XMLNode* parent_node, const structDataCfg& new_cfg){
	cfg = new_cfg;
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
	ele_out->SetAttribute("size", new_cfg.v.size());
	ele_out->SetAttribute("seed", new_cfg.seed);
	ele_out->SetAttribute("sigma", new_cfg.sigma);
	ele_out->SetText(new_cfg.get_s().c_str());
	node = parent_node->InsertEndChild(ele_out);
	return node;
} // ///////////////////////////////////////////////////////////////////////////////////
std::string DataCfg::float2sbin(float f){
	char buf[33];
	sprintf_s(buf, "%X", *(__int32*)&f);
	return std::string(buf);
} // //////////////////////////////////////////////////////////////////////////////
float DataCfg::sbin2float(const char* s){
	__int32 i;
	sscanf_s(s, "%X", &i);
	return *((float*)&i);
} // //////////////////////////////////////////////////////////////////////////////
