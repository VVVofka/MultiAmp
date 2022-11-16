#pragma once
#include <string>		// dor Dump
#include <amp.h>
#include <amp_graphics.h>

#include "VGpuCpu.h"	// for va
#include "..\..\OptsTinyLib\structAll.h"
#include "..\EngineOld\ProcessParams.h"

using namespace Concurrency;

class LayBase{
public:
	LayBase(int n_lay, structAll* cfg_all, accelerator_view* m_accl_view = NULL);
	int nlay = 0;
	int_2 sz;
	CPUtype cpuType = CPUtype::GPU;
	bool gpuIn = false; // underlying lay is GPU and cur isn't GPU

	VGpuCpu<int> va;
	
	accelerator_view* m_accl_view = NULL;
	structAll* cfg_all = NULL;

	int id(const int x, const int y) const{ return y * sz.x + x; }
	bool isLoad()const;

	ProcessParam param;

protected:
	void gpu2cpu(){ va.gpu2cpu(); }
	void cpu2gpu(){ va.cpu2gpu(); }

	std::string sDumpA(const int digits)const;

private:
}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

