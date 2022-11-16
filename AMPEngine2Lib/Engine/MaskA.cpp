#include "MaskA.h"
#include "..\myUtil.h"

MaskA::MaskA(structAll* cfg_all){
	vcpu = {0};
	vgpu = NULL;	// amp maskA
} // ///////////////////////////////////////////////////////////////////////
MaskA::~MaskA(){
	SAFE_DELETE(vgpu);
} // //////////////////////////////////////////////////////////////////////////
bool MaskA::load(const std::vector<int>& mask_A){	//	16
	if(mask_A.size() != 16) return false;
	for(size_t j = 0; j < vcpu.size(); j++)
		vcpu[j] = mask_A[j];

	SAFE_DELETE(vgpu);
	vgpu = new concurrency::array<int, 1>((int)vcpu.size(), vcpu.data());
	return vgpu != NULL;
} // ///////////////////////////////////////////////////////////////////////////
