#include "pch.h"
#include "Lays.h"
#include <string>

Lays::Lays(){
	cfg.vkf.resize(cfg.laysCnt, 1.0f);
} // ///////////////////////////////////////////////////////////////////////////////////
XMLNode* Lays::create(XMLNode* parent_node){
	structLaysCfg new_cfg;
	new_cfg.topX = new_cfg.topY = 1;
	new_cfg.laysCnt = 5;
	new_cfg.vkf.resize(new_cfg.laysCnt, 1.0f);
	return set(parent_node, new_cfg);
} // ///////////////////////////////////////////////////////////////////////////////////
XMLNode* Lays::load(XMLNode* parent_node){
	node = NULL;
	for(XMLNode* curnode = parent_node->FirstChild(); curnode; curnode = curnode->NextSibling()){
		XMLElement* ele = curnode->ToElement();
		std::string name(ele->Name());
		if(name == XMLName){
			structLaysCfg cfg;
			cfg.topX = ele->IntAttribute("topX", 1);
			cfg.topY = ele->IntAttribute("topY", 1);
			cfg.laysCnt = ele->IntAttribute("cnt", 5);
			cfg.vkf.resize(cfg.laysCnt);
			for(size_t j = 0; j < cfg.vkf.size(); j++){
				std::string atrname = "klayf" + std::to_string(j);
				cfg.vkf[j] = ele->FloatAttribute(atrname.c_str(), 1.0f);
			}
			parent_node->DeleteChild(curnode);
			node = set(parent_node, cfg);
			break;
		}
	}
	return node;
} // ///////////////////////////////////////////////////////////////////////////////////
XMLNode* Lays::set(XMLNode* parent_node, const structLaysCfg& new_cfg){
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

	ele_out->SetAttribute("topX", new_cfg.topX);	// 1
	ele_out->SetAttribute("topY", new_cfg.topY);	// 1
	ele_out->SetAttribute("cnt", new_cfg.laysCnt);	// 5
	for(size_t j = 0; j < new_cfg.vkf.size(); j++){
		std::string atrname = "klayf" + std::to_string(j);
		ele_out->SetAttribute(atrname.c_str(), new_cfg.vkf[j]);	// 1.0f
	}
	node = parent_node->InsertEndChild(ele_out);
	return node;
} // ///////////////////////////////////////////////////////////////////////////////////
