#pragma once
#include <time.h>
#include <cstdint>
#include <string>
struct structMiscCfg{
	uint32_t curRndSeed;
	uint64_t curIteration;
	time_t dtCreate;
	time_t dtLastStop;
	std::string sComments;
};

