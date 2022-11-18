#include "MaskF.h"

MaskF::MaskF(const structAll* cfg_all, accelerator_view* m_accl_view){
	vcpu = cfg_all->masks.vf;	// copy
	vgpu = new concurrency::array<float_2, 1>(256, vcpu.begin(), *m_accl_view);
} // //////////////////////////////////////////////////////////////////////
MaskF::~MaskF(){
	if(vgpu) delete vgpu;
} // //////////////////////////////////////////////////////////////////////
void MaskF::dump(){
	std::array<float_2, 16 * 4> vdump;
	concurrency::copy(*vgpu, vdump.begin());
	for(size_t j = 0; j < vcpu.size() / 4; j++){
		printf("%d\n", (int)j);
		for(size_t i = 0; i < 4; i++){
			auto n = (i + 2) % 4;
			float_2 f2 = vcpu[j * 4 + n];
			printf("%+.2f%+.2f ", f2.x, f2.y);
			if(n & 1)
				printf("\n");
		}
		printf("\n");
	}
} // /////////////////////////////////////////////////////////////////////
