#pragma once
#include "Data.h"
#include "Options.h"
#include "tinyxml2.h"
using namespace tinyxml2;

class Session{
public:
	Data data;
	Options options;

	void create(const char* f_name = "");
	void load(const char* f_name = "");
	void save(const char* f_name = "");
	std::string fname;
	void tstcrt();

	const char* get_maskA() const;
	XMLNode* set_maskA(const char* s);
	const char* get_maskF() const;
	XMLNode* set_maskF(const char* s);

protected:
	XMLDocument doc;
};

