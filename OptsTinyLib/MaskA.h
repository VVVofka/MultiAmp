#pragma once
#include <string>
#include "tinyxml2.h" 
using namespace tinyxml2;

class MaskA{
public:
	XMLNode* create(XMLNode* parent_node);
	XMLNode* load(XMLNode* parent_node);
	XMLNode* set(XMLNode* parent_node, const char* s = NULL);

	unsigned get_uns() const;
	const char* get_s() const;
	
	bool isChange = true;
	XMLNode* node = NULL;

private:
	const char defval[16 + 1] = "0001011101111111";
	char v[16 + 1];
	const char XMLName[6] = "MaskA";	// "MaskA"
};

