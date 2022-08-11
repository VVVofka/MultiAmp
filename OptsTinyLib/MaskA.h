#pragma once
#include <string>
#include "tinyxml2.h"
using namespace tinyxml2;

class MaskA{
public:
	const char defval[16 + 1] = "0001011101111111";
	void create(XMLDocument& doc);
	void load(XMLDocument& doc);
private:
	std::string v = defval;
public:
	const char* pchar() const { return v.c_str(); }
	const std::string& str() const {return v;}
};

