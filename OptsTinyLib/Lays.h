#pragma once
#include "tinyxml2.h" 
#include "structLaysCfg.h"
using namespace tinyxml2;

class Lays{
public:
	structLaysCfg cfg;
	bool isChange = true;
	XMLNode* node = NULL;

	Lays();
	XMLNode* create(XMLNode* parent_node);
	XMLNode* load(XMLNode* parent_node);
	XMLNode* set(XMLNode* parent_node, const structLaysCfg& cfg);


private:
	const char XMLName[8] = "LaysCfg";	// "LaysCfg"

};

