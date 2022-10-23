#pragma once
#include <time.h>
#include <cstdint>
#include <string>
#include "structCfgBase.h"

#pragma warning(disable : 26495)
class structMiscCfg : public structCfgBase{
public:
	uint32_t curRndSeed;
	uint64_t curIteration;
	time_t dtCreate;
	time_t dtLastStop;
	std::string sComments;

	bool isEqual(const structCfgBase* other){
		structMiscCfg* p = (structMiscCfg*)other;
		return curRndSeed == p->curRndSeed
			&& curIteration == p->curIteration
			&& dtCreate == p->dtCreate
			&& dtLastStop == p->dtLastStop;
	}

};

