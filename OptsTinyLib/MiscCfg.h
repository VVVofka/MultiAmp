#pragma once
#include "MyTiny2Utils.h"
#include "structMiscCfg.h"

using namespace tinyxml2;

class MiscCfg : protected MyTiny2Utils{
public:
	MiscCfg(XMLDocument* doc) : MyTiny2Utils("MiscCfg"){}

	//XMLNode* create(XMLDocument* doc);
	//XMLNode* load(XMLDocument* doc);
	XMLNode* set(const char* f_name, const structMiscCfg* in_cfg);
	//structMiscCfg* get();

private:
	structMiscCfg cfg;
};

