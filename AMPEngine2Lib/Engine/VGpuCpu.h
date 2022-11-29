#pragma once
#include <amp.h>
#include <amp_graphics.h>
#include <amp_short_vectors.h>
#include <vector>

#include "LaysCPUCfg.h"
#include "..\myUtil.h"

using namespace Concurrency;
using namespace Concurrency::graphics;	// int_2

template<class T, int SZ>
class VGpuCpu{
public:
	std::vector<T> vcpu;
	concurrency::array<T, SZ>* vgpu = NULL;

	~VGpuCpu(){ SAFE_DELETE(vgpu); }

	void Create(const uint_2 size, const bool is_gpu, accelerator_view* m_accl_view){
		_ASSERTE(SZ == 2);
		//size_t size1 = 0;	for(size_t j = 0; j < SZ; j++) size1 += size[j];
		size_t size1 = (size_t)size.x * (size_t)size.y;
		vcpu.resize(size1, 0);
		//for(size_t j = 0; j < size1; j++) vcpu[j] = (T)0;
		SAFE_DELETE(vgpu);
		if(is_gpu)
			vgpu = new concurrency::array<T, SZ>(size.y, size.x, vcpu.begin(), *m_accl_view);
	} // ////////////////////////////////////////////////////////////////////////////
	void Create(const uint_2 size, const std::vector<T>& vi_inp, const bool is_gpu, accelerator_view* m_accl_view){
		_ASSERTE(SZ == 2);
		size_t size1 = (size_t)size.x * (size_t)size.y;
		_ASSERTE(size1 == vi_inp.size());
		vcpu.resize(size1);
		for(size_t j = 0; j < size1; j++)
			vcpu[j] = vi_inp[j];
		SAFE_DELETE(vgpu);
		if(is_gpu)
			vgpu = new concurrency::array<T, SZ>(size.y, size.x, vcpu.begin(), *m_accl_view);
	} // //////////////////////////////////////////////////////////////////////////////
	void Create(const std::vector<T>& vi_inp, const bool is_gpu, accelerator_view* m_accl_view){
		_ASSERTE(SZ == 1);
		size_t size1 = vi_inp.size();
		vcpu.resize(size1);
		for(size_t j = 0; j < size1; j++)
			vcpu[j] = vi_inp[j];
		SAFE_DELETE(vgpu);
		if(is_gpu)
			vgpu = new concurrency::array<T, SZ>(size1, vcpu.begin(), *m_accl_view);
	} // //////////////////////////////////////////////////////////////////////////////

	void gpu2cpu(){ concurrency::copy(*vgpu, vcpu.begin()); }
	void cpu2gpu(){ concurrency::copy(vcpu.begin(), *vgpu); }
	void gpu2other(std::vector<T>& v_dst) const{
		if(vgpu) 
			concurrency::copy(*vgpu, v_dst.begin()); 
	} // ///////////////////////////////////////////////////////////////////////////////

}; //class VGpuCpu

