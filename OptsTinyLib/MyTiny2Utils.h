#pragma once
#include "tinyxml2.h" 
using namespace tinyxml2;

class MyTiny2Utils{
protected:
	MyTiny2Utils(const char* XML_Name, XMLNode* parent_node);
	MyTiny2Utils(const char* XML_Name, XMLDocument* doc);
	char XMLName[8];
	XMLNode* node;

private:
	XMLNode* getNode(XMLDocument* doc);
	XMLNode* getNode(XMLNode* doc);
};

