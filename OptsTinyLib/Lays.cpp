#include "pch.h"
#include "Lays.h"
#include <string>

Lays::Lays(){
	cfg.topX = cfg.topY = 1;
	cfg.laysCnt = 5;
} // ///////////////////////////////////////////////////////////////////////////////////
XMLNode* Lays::create(XMLNode* parent_node){
	structLaysCfg cfg;
	return set(parent_node, cfg);;
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
			parent_node->DeleteChild(curnode);
			node = set(parent_node, cfg);
			break;
		}
	}
	return node;
} // ///////////////////////////////////////////////////////////////////////////////////
XMLNode* Lays::set(XMLNode* parent_node, const structLaysCfg& cfg){
	isChange = false;

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

	ele_out->SetAttribute("topX", cfg.topX);	// 1
	ele_out->SetAttribute("topY", cfg.topY);	// 1
	ele_out->SetAttribute("cnt", cfg.laysCnt);	// 5

	node = parent_node->InsertEndChild(ele_out);
	return node;
} // ///////////////////////////////////////////////////////////////////////////////////
