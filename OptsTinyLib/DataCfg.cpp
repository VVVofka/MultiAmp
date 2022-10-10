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
			cfg.topX = ele->IntAttribute("topX", 1);
			cfg.topY = ele->IntAttribute("topY", 1);
			cfg.digits = ele->IntAttribute("digits", 2);
			size_t size = ele->IntAttribute("cnt", 5);
			cfg.vkf.resize(size);
			for(size_t j = 0; j < cfg.vkf.size(); j++){
				std::string atrname = "k" + std::to_string(j);
				cfg.vkf[j] = ele->IntAttribute(atrname.c_str(), 1);
			}
			parent_node->DeleteChild(curnode);
			node = set(parent_node, cfg);
			return node;
		}
	}
	cfg.topX = cfg.topY = 1;
	//cfg.laysCnt = 5;
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
	ele_out->SetText(new_cfg.get_s().c_str());
	node = parent_node->InsertEndChild(ele_out);
	return node;
} // ///////////////////////////////////////////////////////////////////////////////////
