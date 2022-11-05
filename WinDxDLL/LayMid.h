#pragma once
#include <string>
#include "LayBase.h"
class LayMid : public LayBase{
public:
	VGpuCpu<float_2> vf;

	CPUtype cpuType = CPUtype::GPU;
	bool gpuIn = false;

	void Create(const int_2 xy, const CPUtype cpu_type, const bool gpu_in);
	void gpu2cpu();
	void cpu2gpu();

	std::string sDumpA(const int digits)const;
	std::string sDumpF(const int digits)const;

	std::string sInfo()const;


private:
	std::string sDumpvf(const VGpuCpu<float_2>& v, const int digits)const;
};

