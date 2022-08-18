#pragma once
#include "MaskBase.h"
#include <string>

using namespace tinyxml2;
class MaskF : public MaskBase{
public:
	MaskF();
	XMLNode* create(XMLNode* parent_node);
	XMLNode* load(XMLNode* parent_node);
	XMLNode* set(XMLNode* parent_node, const char* s = NULL);

	const char* get_s() const;
	std::string v;
	static const size_t size = 16 * 16;

private:
	std::string defval;
	const char XMLName[6] = "MaskF";	// "MaskA"

};

