#pragma once
#include "tinyxml2.h" 
using namespace tinyxml2;

class MyTiny2Utils{
protected:
	MyTiny2Utils(const char* XML_Name, const char* f_name);

	char XMLName[8] = "";
	XMLDocument doc;
	XMLNode* node = NULL;
	XMLNode* parrentNode = NULL;

private:
	XMLNode* getNode(XMLDocument* doc);
	XMLNode* getNode(XMLNode* doc);
};

