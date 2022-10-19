#pragma once
#include "structDataCfg.h"
#include "structLaysCfg.h"
#include "structMiscCfg.h"
struct structAll{
	structDataCfg data;
	structLaysCfg lays;
	structMiscCfg misc;
};
struct structPtrAll{
	structDataCfg* data;
	structLaysCfg* lays;
	structMiscCfg* misc;
};