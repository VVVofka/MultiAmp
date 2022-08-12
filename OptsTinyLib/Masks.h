#pragma once
#include "MaskA.h"
#include "MaskF.h"
using namespace tinyxml2;

class Masks{
public:
	MaskA maskA;
	//MaskF maskF;
	bool create(XMLNode* parent_node);
	bool load(XMLNode* parent_node);

private:
	const char XMLName[6] = "Masks";
	//XMLElement* element = NULL;

};

