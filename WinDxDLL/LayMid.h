#pragma once
#include <string>
#include "LayBase.h"
class LayMid : public LayBase{
public:
	LayMid(int n_lay, structAll* cfg_all, accelerator_view* m_accl_view = NULL);
	VGpuCpu<float_2> vf;

	CPUtype cpuType = CPUtype::GPU;
	bool gpuIn = false; // underlying lay is GPU and cur isn't GPU

	void gpu2cpu();
	void cpu2gpu();

	std::string sDumpA(const int digits)const;
	std::string sDumpF(const int digits)const;

	std::string sInfo()const;


private:
	std::string sDumpvf(const VGpuCpu<float_2>& v, const int digits)const;
};

