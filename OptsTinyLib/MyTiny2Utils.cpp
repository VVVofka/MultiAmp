#include "MyTiny2Utils.h"
#include <string>
using namespace tinyxml2;

MyTiny2Utils::MyTiny2Utils(const char* XML_Name){
	strncpy_s(XMLName, XML_Name, sizeof(XMLName));
} // ////////////////////////////////////////////////////////////////

//XMLDocument* MyTiny2Utils::getDoc(const char* f_name){
//	if(f_name == NULL) return NULL;
//	auto slen = strlen(f_name);
//	if(slen == 0 || slen > 255) return NULL;
//	XMLError errLoad = doc.LoadFile(f_name);
//	if(errLoad != XML_SUCCESS)
//		doc.Clear();
//	return &doc;
//} // //////////////////////////////////////////////////////////////
//XMLDocument* MyTiny2Utils::setDoc(const char* f_name){
//
//} // //////////////////////////////////////////////////////////////
//MyTiny2Utils::MyTiny2Utils(const char* XML_Name, XMLDocument* doc){
//	strncpy_s(XMLName, XML_Name, sizeof(XMLName));
//	node = setNode(doc);
//} // ////////////////////////////////////////////////////////////////
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
