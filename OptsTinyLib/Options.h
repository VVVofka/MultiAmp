#pragma once
#include "Lays.h"
#include "Masks.h"
using namespace tinyxml2;

class Options{
public:
	Lays lays;
	Masks masks;
	void create(XMLDocument* doc);
	void load(XMLDocument* doc);

private:
	const char XMLName[8] = "Options";
	//XMLElement* element = NULL;

};

