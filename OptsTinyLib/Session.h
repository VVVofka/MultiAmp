#pragma once
#include "Data.h"
#include "Options.h"
#include "tinyxml2.h"
using namespace tinyxml2;

class Session{
public:
	Data data;
	Options options;
	void load(const char* fname = "");
	std::string fname;
	void tstcrt();

	const char* get_maskA() const;
	XMLNode* set_maskA(const char* s);

protected:
	XMLDocument doc;
	void create(const char* fname);
};

