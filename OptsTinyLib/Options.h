#pragma once
#include "Lays.h"
#include "Masks.h"
using namespace tinyxml2;

class Options{
public:
	Lays lays;
	Masks masks;
	void create(XMLDocument& doc);
	void load(XMLDocument& doc);

};

