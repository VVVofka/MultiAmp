#pragma once
#include "structDataCfg.h"
#include "structLaysCfg.h"
#include "structMiscCfg.h"
#include "InPort.h"
#include <vector>

class structAll{
public:
	structDataCfg data;
	structLaysCfg lays;
	structMiscCfg misc;

	structDataCfg olddata;
	structLaysCfg oldlays;
	structMiscCfg oldmisc;

	std::vector<structCfgBase*> v = {&data, &lays, &misc};
	bool isEqual(const structAll* other) const;
	void load(const char* f_name){
		//data.
		data = getDataCfg(f_name);
		lays = getLaysCfg(f_name);
		misc = getMiscCfg(f_name);
	}
};

class structAlls{
	structAll cur;
	structAll old;
	bool isEqual() const;
};
//struct structPtrAll{
//	structDataCfg* data;
//	structLaysCfg* lays;
//	structMiscCfg* misc;
//};