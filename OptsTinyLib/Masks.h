#pragma once
#include "MaskA.h"
#include "MaskF.h"
using namespace tinyxml2;

class Masks{
public:
	MaskA maskA;
	//MaskF maskF;
	XMLNode* create(XMLNode* parent_node);
	XMLNode* load(XMLNode* parent_node);
	XMLNode* node = NULL;

	const char* get_maskA() const;
	XMLNode* set_maskA(const char* s);

private:
	const char XMLName[6] = "Masks";
	//XMLElement* element = NULL;

};

