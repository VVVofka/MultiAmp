#pragma once
#include <string>		// dor Dump
#include "VGpuCpu.h"	// for va

class LayBase{
public:
	int_2 sz;
	VGpuCpu<int> va;

	void Create(const int_2 xy, const bool is_gpu);
	void Create(const int_2 xy, const std::vector<int>& va_inp, const bool is_gpu);
	int id(const int x, const int y) const{ return y * sz.x + x; }
	bool isLoad()const;

protected:
	void gpu2cpu(){ va.gpu2cpu(); }
	void cpu2gpu(){ va.cpu2gpu(); }

	std::string sDumpA(const int digits)const;
};

