#pragma once
#include "structDataCfg.h"
#include "structLaysCfg.h"
#include "structMiscCfg.h"
#include "InPort.h"
#include <vector>

struct structAll{ 
	structDataCfg data;
	structLaysCfg lays;
	structMiscCfg misc;
	void load(const char* f_name){
		data = getDataCfg(f_name);
		lays = getLaysCfg(f_name);
		misc = getMiscCfg(f_name);
	} // ///////////////////////////////////////////////////////////////////
};
