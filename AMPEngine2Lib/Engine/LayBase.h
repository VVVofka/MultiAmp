#pragma once
#include <string>		// dor Dump
#include <amp.h>
#include <amp_graphics.h>

#include "VGpuCpu.h"	// for va
#include "..\..\OptsTinyLib\structAll.h"

using namespace Concurrency;

class LayBase{
public:
	LayBase(uint n_lay, structAll* cfg_all, accelerator_view* m_accl_view = NULL);
	uint nlay = 0;
	uint_2 sz;
	CPUtype cpuType = CPUtype::GPU;

	accelerator_view* m_accl_view = NULL;
	structAll* cfg_all = NULL;

	int id(const int x, const int y) const{ return y * sz.x + x; }

protected:
	static std::string sDumpV(const std::vector<int>& v, const uint_2 sz, const int digits);
	static std::string sDumpV(const std::vector<float_2>& v, const uint_2 sz, const int digits);

private:
}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

