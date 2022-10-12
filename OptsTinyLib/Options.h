#pragma once
#include "Lays.h"
#include "Masks.h"
#include "DataCfg.h"
#include "structLaysCfg.h"
#include "structDataCfg.h"

using namespace tinyxml2;

class Options{
public:
	Lays lays;
	Masks masks;
	DataCfg datacfg;

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
	XMLNode* getNode(XMLDocument* doc);
};

