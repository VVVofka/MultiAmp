#pragma once
#include "MaskBase.h"
using namespace tinyxml2;
class MaskF : public MaskBase{
public:
	XMLNode* create(XMLNode* parent_node);
	XMLNode* load(XMLNode* parent_node);
	XMLNode* set(XMLNode* parent_node, const char* s = NULL);

	unsigned get_uns() const;
	const char* get_s() const;

private:
	const char defval[16 + 1] = "0000000000000000";
	const char XMLName[6] = "MaskF";	// "MaskA"

};

