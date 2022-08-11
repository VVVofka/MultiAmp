#pragma once
#include "MaskA.h"
#include "MaskF.h"
using namespace tinyxml2;

class Masks{
public:
	MaskA maskA;
	//MaskF maskF;
	void create(XMLDocument& doc);
	void load(XMLDocument& doc);

};

