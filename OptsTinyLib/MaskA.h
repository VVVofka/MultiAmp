#pragma once
#include <string>
#include "tinyxml2.h" 
using namespace tinyxml2;

class MaskA{
public:
	bool create(XMLNode* parent_node);
	bool load(XMLNode* parent_node);
	unsigned get_uns() const;
	bool isChange = true;

private:
	const char defval[16 + 1] = "0001011101111111";
	char v[16 + 1];
	const char XMLName[6] = "MaskA";	// "MaskA"
	bool set(XMLNode* parent_node, const char* s = NULL);
};

