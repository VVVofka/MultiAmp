#pragma once
#include "structDataCfg.h"
#include "structLaysCfg.h"
#include "structMiscCfg.h"
#include "structMasksCfg.h"
#include "InPort.h"

struct structAll{ 
	structDataCfg data;
	structLaysCfg lays;
	structMiscCfg misc;
	structMasksCfg masks;

	void load(const char* f_name){
		data = getDataCfg(f_name);
		lays = getLaysCfg(f_name);
		misc = getMiscCfg(f_name);
		masks = getMasksCfg(f_name);
	} // ///////////////////////////////////////////////////////////////////
};
