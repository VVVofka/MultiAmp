#pragma once
#include "Lays.h"
#include "Masks.h"
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


private:
	const char XMLName[8] = "Options";
	//XMLElement* element = NULL;

};

