#pragma once
#include "MaskA.h"
#include "MaskF.h"
using namespace tinyxml2;

class Masks{
public:
	MaskA maskA;
	//MaskF maskF;
	void create(XMLNode* parent_node);
	void load(XMLDocument& doc);

private:
	const char XMLName[6] = "Masks";
	//XMLElement* element = NULL;

};

