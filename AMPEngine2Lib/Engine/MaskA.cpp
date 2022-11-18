#include "MaskA.h"
#include "..\myUtil.h"	// SAFE_DELETE

MaskA::MaskA(structAll* cfg_all, accelerator_view* m_accl_view){
	vcpu = cfg_all->masks.va;	// copy
	vgpu = new concurrency::array<int, 1>(16, vcpu.begin(), *m_accl_view);
} // ///////////////////////////////////////////////////////////////////////
MaskA::~MaskA(){
	SAFE_DELETE(vgpu);
} // //////////////////////////////////////////////////////////////////////////
//bool MaskA::load(const std::array<int, 16>& mask_A){	//	16
//	if(mask_A.size() != 16) return false;
//	for(size_t j = 0; j < vcpu.size(); j++)
//		vcpu[j] = mask_A[j];
//
//	SAFE_DELETE(vgpu);
//	vgpu = new concurrency::array<int, 1>((int)vcpu.size(), vcpu.data());
//	return vgpu != NULL;
//} // ///////////////////////////////////////////////////////////////////////////
