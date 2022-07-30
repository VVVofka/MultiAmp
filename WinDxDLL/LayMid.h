#pragma once
#include <string>
#include "LayBase.h"
class LayMid : public LayBase{
public:
	CPUtype cpuType = CPUtype::GPU;
	bool gpuIn = false;

	void Create(
		const int_2 xy,
		const CPUtype cpu_type,
		const bool gpu_in
	);

	std::string sDumpA(const int digits)const;
	std::string sDumpF(const int digits)const;

	std::string sInfo()const;
};

