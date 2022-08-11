#pragma once
#include "Data.h"
#include "Options.h"
#include "tinyxml2.h"
using namespace tinyxml2;

class Session{
public:
	Data data;
	Options opts;
	void load(const char* fname = "");

protected:
	XMLDocument doc;
};

