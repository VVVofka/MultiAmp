#include "MyTiny2Utils.h"
#include <string>
using namespace tinyxml2;

MyTiny2Utils::MyTiny2Utils(const char* XML_Name, XMLNode* parent_node){
	strncpy_s(XMLName, XML_Name, sizeof(XMLName));
	node = getNode(parent_node);
} // ////////////////////////////////////////////////////////////////
MyTiny2Utils::MyTiny2Utils(const char* XML_Name, XMLDocument* doc){
	strncpy_s(XMLName, XML_Name, sizeof(XMLName));
	node = getNode(doc);
} // ////////////////////////////////////////////////////////////////
XMLNode* MyTiny2Utils::getNode(XMLDocument* doc){
	for(XMLNode* curnode = doc->FirstChild(); curnode; curnode = curnode->NextSibling()){
		XMLElement* ele = curnode->ToElement();
		std::string name(ele->Name());
		if(name == XMLName)
			return curnode;
	}
	return nullptr;
} // ////////////////////////////////////////////////////////////////
XMLNode* MyTiny2Utils::getNode(XMLNode* parrent_node){
	for(XMLNode* curnode = parrent_node->FirstChild(); curnode; curnode = curnode->NextSibling()){
		XMLElement* ele = curnode->ToElement();
		std::string name(ele->Name());
		if(name == XMLName)
			return curnode;
	}
	return nullptr;
} // ////////////////////////////////////////////////////////////////
