#pragma once
#include <cstdint>
class LehmerRng{
public:
	uint32_t seed;
	uint32_t rand(){
		return seed = (uint64_t)seed * 279470273u % 0xfffffffb;
	}
};

