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
		data = getxml::getDataCfg(f_name);
		lays = getxml::getLaysCfg(f_name);
		misc = getxml::getMiscCfg(f_name);
		masks = getxml::getMasksCfg(f_name);
	} // ///////////////////////////////////////////////////////////////////
};
