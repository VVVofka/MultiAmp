#pragma once
#include <string>
#include "tinyxml2.h" 
using namespace tinyxml2;

class MaskBase{
public:
	bool isChange = true;
	XMLNode* node = NULL;
protected:
	char v[16 + 1];
private:
};
