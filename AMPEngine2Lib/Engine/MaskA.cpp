#include "MaskA.h"

MaskA::MaskA(const structAll* cfg_all, accelerator_view* m_accl_view){
	vcpu = cfg_all->masks.va;	// copy
	vgpu = new concurrency::array<int, 1>(16, vcpu.begin(), *m_accl_view);
} // ///////////////////////////////////////////////////////////////////////
MaskA::~MaskA(){
	if(vgpu) delete vgpu;
} // //////////////////////////////////////////////////////////////////////////
