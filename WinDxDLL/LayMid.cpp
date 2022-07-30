#include "pch.h"
#include "LayMid.h"

void LayMid::Create(const int_2 xy, const CPUtype cpu_type, const bool gpu_in){
	const bool is_gpu = gpu_in || cpu_type == CPUtype::GPU;
	LayBase::Create(xy, is_gpu);
	cpuType = cpu_type;
	gpuIn = gpu_in;
} // /////////////////////////////////////////////////////////////////////////////////
