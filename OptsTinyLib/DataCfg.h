#pragma once
#include "tinyxml2.h" 
#include "structDataCfg.h"
using namespace tinyxml2;

class DataCfg{
public:
	structDataCfg cfg;
	XMLNode* node = NULL;

	XMLNode* create(XMLNode* parent_node);
	XMLNode* load(XMLNode* parent_node);
	XMLNode* set(XMLNode* parent_node, const structDataCfg& cfg);
	void clear(XMLNode* parent_node);

private:
	const char XMLName[8] = "DataCfg";	// "LaysCfg"

};

