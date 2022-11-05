#pragma once
#include <amp.h>
#include <amp_short_vectors.h>
#include <vector>
#include "LaysCPUCfg.h"
#include "Utils.h"

using namespace Concurrency::graphics;
template<class T>
class VGpuCpu{
public:
	std::vector<T> vcpu;
	concurrency::array<T, 2>* vgpu = NULL;

	~VGpuCpu(){ SAFE_DELETE(vgpu); }

	void Create(const int_2 size, const bool is_gpu, accelerator_view& m_accl_view){
		size_t size1 = (size_t)size.x * (size_t)size.y;
		vcpu.resize(size1);
		for(size_t j = 0; j < size1; j++)
			vcpu[j] = (T)0;
		SAFE_DELETE(vgpu);
		if(is_gpu)
			vgpu = new concurrency::array<T, 2>(size.y, size.x, vcpu.begin(), m_accl_view);
	} // ////////////////////////////////////////////////////////////////////////////
	void Create(const int_2 size, const std::vector<T>& vi_inp, const bool is_gpu, accelerator_view& m_accl_view){
		size_t size1 = (size_t)size.x * (size_t)size.y;
		_ASSERTE(size1 == vi_inp.size());
		vcpu.resize(size1);
		for(size_t j = 0; j < size1; j++)
			vcpu[j] = vi_inp[j];
		SAFE_DELETE(vgpu);
		if(is_gpu)
			vgpu = new concurrency::array<T, 2>(size.y, size.x, vcpu.begin(), m_accl_view);
	} // //////////////////////////////////////////////////////////////////////////////

	void gpu2cpu(){ concurrency::copy(*vgpu, vcpu.begin()); }
	void cpu2gpu(){ concurrency::copy(vcpu.begin(), *vgpu); }

}; //class VGpuCpu

