#pragma once
#include <string>		// dor Dump
#include "VGpuCpu.h"	// for va
#include "..\OptsTinyLib\structAll.h"

class LayBase{
public:
	LayBase(int n_lay, structAll* cfg_all, accelerator_view* m_accl_view = NULL);
	int_2 sz;
	VGpuCpu<int> va;
	
	accelerator_view* m_accl_view = NULL;
	structAll* cfg_all = NULL;

	int id(const int x, const int y) const{ return y * sz.x + x; }
	bool isLoad()const;

protected:
	void gpu2cpu(){ va.gpu2cpu(); }
	void cpu2gpu(){ va.cpu2gpu(); }

	std::string sDumpA(const int digits)const;
};

