#pragma once
#include <string>
#include "structLaysCfg.h"
std::string getMaskA(const char* fname);
void setMaskA(const char* fname, const char* s);

std::string getMaskF(const char* fname);
void setMaskF(const char* fname, const char* s);

structLaysCfg getLaysCgf(const char* fname);
void setMaskF(const char* fname, const structLaysCfg& lays_cfg);
