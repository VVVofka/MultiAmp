#pragma once
#include "MyTiny2Utils.h"
#include "structLaysCfg.h"
#include "structDataCfg.h"
#include "Lays.h"
#include "Masks.h"

using namespace tinyxml2;

class Options : protected MyTiny2Utils{
public:
	Lays lays;
	Masks masks;

	XMLNode* create(XMLDocument* doc);
	XMLNode* load(XMLDocument* doc);
	XMLNode* loadMasks(XMLDocument* doc);
	XMLNode* loadLaysCfg(XMLDocument* doc);
	XMLNode* loadDataCfg(XMLDocument* doc);
	XMLNode* node;

	const char* get_maskA() const;
	XMLNode* set_maskA(XMLDocument* doc, const char* s);
	
	const char* get_maskF() const;
	XMLNode* set_maskF(XMLDocument* doc, const char* s);

	structLaysCfg get_laysCfg() const;
	XMLNode* set_laysCfg(XMLDocument* doc, const structLaysCfg& lays_cfg);

	structDataCfg get_dataCfg() const;
	XMLNode* set_dataCfg(XMLDocument* doc, const structDataCfg& data_cfg);
	void clear_dataCfg(XMLDocument* doc);

private:
	const char XMLName[8] = "Options";	//	Options
};

