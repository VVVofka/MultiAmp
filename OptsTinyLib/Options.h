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
	XMLNode* set_maskA(const char* s);
	
	const char* get_maskF() const;
	XMLNode* set_maskF(const char* s);

	structLaysCfg get_laysCfg() const;
	XMLNode* set_laysCfg(const structLaysCfg& lays_cfg);

	structDataCfg get_dataCfg() const;
	XMLNode* set_dataCfg(XMLDocument* doc, const structDataCfg& data_cfg);

private:
	const char XMLName[8] = "Options";	//	Options
	XMLNode* getNode(XMLDocument* doc);
};

