#pragma once
#include <string>
#include "LayBase.h"
#include <amp_graphics.h>

using namespace Concurrency;

class LayMid : public LayBase{
public:
	LayMid(int n_lay, structAll* cfg_all, accelerator_view* m_accl_view);
	VGpuCpu<float_2> vf;
	//VGpuCpu<float_2> kF;// = {1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f};
	float kF;// = {1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f};

	void gpu2cpu();
	void cpu2gpu();
	void gpu2other(std::vector<float_2>& v_dst)const;

	std::string sDumpAcpu(const int digits)const;
	std::string sDumpAgpu(const int digits)const;
	std::string sDumpFcpu(const int digits)const;
	std::string sDumpFgpu(const int digits)const;

	std::string sInfo()const;

private:
}; // #########################################################################################

