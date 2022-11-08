#pragma once
#include <string>
#include "structLaysCfg.h"
#include "structDataCfg.h"
#include "structMiscCfg.h"
#include "structMasksCfg.h"

std::string getMaskA(const char* fname);
void setMaskA(const char* fname, const char* s);

std::string getMaskF(const char* fname);
void setMaskF(const char* fname, const char* s);

structLaysCfg getLaysCfg(const char* fname);
void setLaysCfg(const char* fname, const structLaysCfg& lays_cfg);

structDataCfg getDataCfg(const char* fname);
void setDataCfg(const char* fname, const structDataCfg& data_cfg);
void clearDataCfg(const char* fname);

structMiscCfg getMiscCfg(const char* fname);
void setMiscCfg(const char* fname, const structMiscCfg& lays_cfg);

structMasksCfg getMasksCfg(const char* f_name);
