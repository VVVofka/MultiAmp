#pragma once
#include <string>

struct ProcessParam{
	float klayf = 1.f;
	float levelTurbul = 2 * 2.7f;
	float kLaminar = 0.1f;
	float kTurbul = 0.1f;

	std::string sDump() const;
};
