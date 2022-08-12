#pragma once
#include "Lays.h"
#include "Masks.h"
using namespace tinyxml2;

class Options{
public:
	Lays lays;
	Masks masks;
	bool create(XMLDocument* doc);
	bool load(XMLDocument* doc);

private:
	const char XMLName[8] = "Options";
	//XMLElement* element = NULL;

};

