#pragma once
#include <string>
#include "structLaysCfg.h"
#include "structDataCfg.h"

std::string getMaskA(const char* fname);
void setMaskA(const char* fname, const char* s);

std::string getMaskF(const char* fname);
void setMaskF(const char* fname, const char* s);

structLaysCfg getLaysCfg(const char* fname);
void setLaysCfg(const char* fname, const structLaysCfg& lays_cfg);

structDataCfg getDataCfg(const char* fname);
void setDataCfg(const char* fname, const structDataCfg& data_cfg);