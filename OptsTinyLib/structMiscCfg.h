#pragma once
#include <time.h>
#include <cstdint>
#include <string>

#pragma warning(disable : 26495)
class structMiscCfg{
public:
	uint32_t curRndSeed;
	uint64_t curIteration;
	time_t dtCreate;
	time_t dtLastStop;
	std::string sComments;
	int cntForStop = -1;
	int cntEnginePerRender = 1;
}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

