#pragma once
#include <amp.h>
#include <amp_graphics.h>
#include <amp_short_vectors.h>
#include <vector>
#include "..\myUtil.h"	// SAFE_DELETE

using namespace Concurrency;				// accelerator_view
using namespace Concurrency::graphics;		// int_2

template<class T> class VGpuCpu2{	// double dimension gpu
public:
	std::vector<T> vcpu;
	concurrency::array<T, 2>* vgpu = NULL;

	~VGpuCpu2(){ SAFE_DELETE(vgpu); }

	void Create(const uint_2 size, const bool is_gpu, accelerator_view* m_accl_view){
		size_t size1 = (size_t)size.x * (size_t)size.y;
		vcpu.resize(size1, 1);
		SAFE_DELETE(vgpu);
		if(is_gpu)
			vgpu = new concurrency::array<T, 2>(size.y, size.x, vcpu.begin(), *m_accl_view);
	} // ////////////////////////////////////////////////////////////////////////////
	void Create(const uint_2 size, const std::vector<T>& vi_inp, const bool is_gpu, accelerator_view* m_accl_view){
		size_t size1 = (size_t)size.x * (size_t)size.y;
		_ASSERTE(size1 == vi_inp.size());
		vcpu.resize(size1);
		for(size_t j = 0; j < size1; j++)
			vcpu[j] = vi_inp[j];
		SAFE_DELETE(vgpu);
		if(is_gpu)
			vgpu = new concurrency::array<T, 2>(size.y, size.x, vcpu.begin(), *m_accl_view);
	} // //////////////////////////////////////////////////////////////////////////////
	void gpu2cpu(){ concurrency::copy(*vgpu, vcpu.begin()); }
	void cpu2gpu(){ concurrency::copy(vcpu.begin(), *vgpu); }
	void gpu2other(std::vector<T>& v_dst) const{
		if(vgpu) 
			concurrency::copy(*vgpu, v_dst.begin()); 
	} // ///////////////////////////////////////////////////////////////////////////////
}; //class VGpuCpu ##################################################################################
template<class T> class VGpuCpu1{	// single dimension gpu
public:
	std::vector<T> vcpu;
	concurrency::array<T, 1>* vgpu = NULL;

	~VGpuCpu1(){ SAFE_DELETE(vgpu); }

	void Create(const std::vector<T>& vi_inp, const bool is_gpu, accelerator_view* m_accl_view){
		size_t size1 = vi_inp.size();
		vcpu.resize(size1);
		for(size_t j = 0; j < size1; j++)
			vcpu[j] = vi_inp[j];
		SAFE_DELETE(vgpu);
		if(is_gpu)
			vgpu = new concurrency::array<T, 1>(size1, vcpu.begin(), *m_accl_view);
	} // //////////////////////////////////////////////////////////////////////////////
	void gpu2cpu(){ concurrency::copy(*vgpu, vcpu.begin()); }
	void cpu2gpu(){ concurrency::copy(vcpu.begin(), *vgpu); }
	void gpu2other(std::vector<T>& v_dst) const{
		if(vgpu)
			concurrency::copy(*vgpu, v_dst.begin());
	} // ///////////////////////////////////////////////////////////////////////////////
}; // ##################################################################################