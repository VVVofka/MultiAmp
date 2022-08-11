#pragma once
#include <string>
#include "tinyxml2.h"
using namespace tinyxml2;

class MaskA{
public:
	const char defval[16 + 1] = "0001011101111111";
	void create(XMLElement* parent_element);
	void load(XMLDocument& doc);
private:
	std::string v = defval;
	const char XMLName[6] = "MaskA";
	XMLElement* element = NULL;
public:
	const char* pchar() const { return v.c_str(); }
	const std::string& str() const {return v;}
};

