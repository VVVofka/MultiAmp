#pragma once
#include "Lays.h"
#include "Masks.h"
#include "structLaysCfg.h"

using namespace tinyxml2;

class Options{
public:
	Lays lays;
	Masks masks;
	XMLNode* create(XMLDocument* doc);
	XMLNode* load(XMLDocument* doc);
	XMLNode* node;

	const char* get_maskA() const;
	XMLNode* set_maskA(const char* s);
	const char* get_maskF() const;
	XMLNode* set_maskF(const char* s);
	structLaysCfg get_laysCfg() const;
	XMLNode* set_laysCfg(const structLaysCfg& lays_cfg);


private:
	const char XMLName[8] = "Options";	//	Options

};

