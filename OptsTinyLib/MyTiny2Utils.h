#pragma once
#include "tinyxml2.h" 
using namespace tinyxml2;

class MyTiny2Utils{
protected:
	MyTiny2Utils(const char* XML_Name);

	char XMLName[8] = "";
	XMLNode* node = NULL;
	XMLNode* parrentNode = NULL;

	//XMLDocument* getDoc(const char* f_name);

private:
	XMLDocument doc;
	XMLNode* getNode(XMLDocument* doc);
	XMLNode* getNode(XMLNode* doc);
};

