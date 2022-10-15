#pragma once
#include "MyTiny2Utils.h"
#include "structDataCfg.h"
using namespace tinyxml2;
class DataCfg : protected MyTiny2Utils{
public:
	DataCfg(XMLDocument* doc) : MyTiny2Utils("DataCfg"){ }
	structDataCfg cfg;

	XMLNode* create(XMLNode* parent_node);
	XMLNode* load(XMLNode* parent_node);
	XMLNode* set(XMLNode* parent_node, const structDataCfg& cfg);
	void clear(XMLNode* parent_node);

private:
	//const char XMLName[8] = "DataCfg";	

};

