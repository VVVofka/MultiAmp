#pragma once
#include "structDataCfg.h"
#include "structLaysCfg.h"
#include "structMiscCfg.h"
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