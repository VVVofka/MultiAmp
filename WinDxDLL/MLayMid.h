#pragma once
#include <string>
#include "MLayBase.h"
class MLayMid : public MLayBase{
public:
	MCPUtype cpuType = MCPUtype::GPU;
	bool gpuIn = false;

	void Create(
		const int_2 xy,
		const MCPUtype cpu_type,
		const bool gpu_in
	);

	std::string sDumpA(const int digits)const;
	std::string sDumpF(const int digits)const;

	std::string sInfo()const;
};

