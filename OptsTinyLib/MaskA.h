#pragma once
#include <string>
#include "tinyxml2.h"
using namespace tinyxml2;

class MaskA{
public:
	const char defval[16 + 1] = "0001011101111111";
	void create(XMLNode* parent_node);
	bool set(const std::string& s);
	void load(XMLDocument& doc);
	unsigned get_uns() const;
private:
	std::string v = defval;
	const char XMLName[6] = "MaskA";
public:
	const char* pchar() const { return v.c_str(); }
	const std::string& str() const {return v;}
};

