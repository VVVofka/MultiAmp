#pragma once
#include <string>
#include "LayBase.h"
#include <amp_graphics.h>

using namespace Concurrency;

class LayMid : public LayBase{
public:
	LayMid(int n_lay, structAll* cfg_all, accelerator_view* m_accl_view);
	VGpuCpu2<int> va;	// -1 - empty point
	VGpuCpu2<float_2> vf;
	VGpuCpu1<float_2> kF;	// size=256

	void gpu2cpu(){ va.gpu2cpu(), vf.gpu2cpu(); }
	void cpu2gpu(){ va.cpu2gpu(), vf.cpu2gpu();	}

	static const int defdig = 3;
	std::string sDumpAcpu(const int digits = defdig)const;
	std::string sDumpAgpu(const int digits = defdig)const;
	std::string sDumpFcpu(const int digits = defdig)const;
	std::string sDumpFgpu(const int digits = defdig)const;
	std::string sDumpF(const int digits = defdig)const;

	std::string sInfo()const;

private:
}; // #########################################################################################

