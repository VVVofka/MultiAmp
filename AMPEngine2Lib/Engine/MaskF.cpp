#include "MaskF.h"
#include "..\myUtil.h"

MaskF::MaskF(structAll* cfg_all, accelerator_view* m_accl_view){
	//cfg_all->lays.
} // //////////////////////////////////////////////////////////////////////
MaskF::~MaskF(){
	SAFE_DELETE(vgpu);
} // //////////////////////////////////////////////////////////////////////
void MaskF::create(const std::vector<float_2>& v_inp){
	_ASSERTE(v_inp.size() == vcpu.size());
	for(size_t j = 0; j < vcpu.size(); j++)
		vcpu[j] = v_inp[j];
	SAFE_DELETE(vgpu);
	vgpu = new concurrency::array<float_2, 2>(16, 4, vcpu.begin());
} // //////////////////////////////////////////////////////////////////////
void MaskF::create(const std::vector<float>& v_inp){
	_ASSERTE(v_inp.size() == vcpu.size() * 2);
	for(size_t j = 0; j < vcpu.size(); j++){
		vcpu[j].x = v_inp[j * 2];
		vcpu[j].y = v_inp[j * 2 + 1];
	}
	SAFE_DELETE(vgpu);
	vgpu = new concurrency::array<float_2, 2>(16, 4, vcpu.begin());
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
