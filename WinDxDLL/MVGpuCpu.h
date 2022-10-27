#pragma once
#include <amp.h>
#include <amp_short_vectors.h>
#include <vector>
#include "MLaysCPUCfg.h"

using namespace Concurrency::graphics;
template<class T>
class MVGpuCpu{
public:
	std::vector<T> vcpu;
	concurrency::array<T, 2>* vgpu = NULL;

	~MVGpuCpu(){ SAFE_DELETE(vgpu); }

	void Create(const int_2 size, const bool is_gpu){
		size_t size1 = (size_t)size.x * (size_t)size.y;
		vcpu.resize(size1);
		for(size_t j = 0; j < size1; j++)
			vcpu[j] = (T)0;
		SAFE_DELETE(vgpu);
		if(is_gpu)
			vgpu = new concurrency::array<T, 2>(size.y, size.x, vcpu.begin());
	} // ////////////////////////////////////////////////////////////////////////////
	void Create(const int_2 size, const std::vector<T>& vi_inp, const MCPUtype cpu_type){
		size_t size1 = (size_t)size.x * (size_t)size.y;
		_ASSERTE(size1 == vi_inp.size());
		vcpu.resize(size1);
		for(size_t j = 0; j < size1; j++)
			vcpu[j] = vi_inp[j];
		SAFE_DELETE(vgpu);
		if(cpu_type == MCPUtype::GPU)
			vgpu = new concurrency::array<T, 2>(size.y, size.x, vcpu.begin());
	} // //////////////////////////////////////////////////////////////////////////////

	void gpu2cpu(){ concurrency::copy(*vgpu, vcpu.begin()); }
	void cpu2gpu(){ concurrency::copy(vcpu.begin(), *vgpu); }

}; //class VGpuCpu

