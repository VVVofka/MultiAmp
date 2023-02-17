#include<ppl.h>	//	parallel_for
#include "ProcessF.h"

void ProcessF::cpuRunMid(LayMid* up_lay){
	for(size_t id_up = 0; id_up < up_lay->sz; id_up++){
		mtcpuRunMid1(up_lay, id_up);
	}

	LayMid* dn_lay = up_lay - 1;
	if(dn_lay->cpuType == CPUtype::GPU)
		dn_lay->vf.cpu2gpu();
} // ///////////////////////////////////////////////////////////////////////////
void ProcessF::mtRunMid(LayMid* up_lay){
	parallel_for(size_t(0), up_lay->sz, [=](size_t id_up){
		mtcpuRunMid1(up_lay, id_up);
		});	

	LayMid* dn_lay = up_lay - 1;
	if(dn_lay->cpuType == CPUtype::GPU)
		dn_lay->vf.cpu2gpu();
} // ///////////////////////////////////////////////////////////////////////////
void ProcessF::mtcpuRunMid1(LayMid* up_lay, const size_t id_up){
	LayMid* dn_lay = up_lay - 1;

	const size_t x = id_up % up_lay->sz;
	const size_t y = id_up / up_lay->sz;
	const size_t id_dn = 2 * (y * dn_lay->sz + x);

	const int id_maskf = up_lay->va.vcpu[id_up] * 4;
	const float_2* val_maskf = &up_lay->kF.vcpu[id_maskf];

	const float_2 up_f = up_lay->vf.vcpu[id_up];

	float_2* vf_dn = &dn_lay->vf.vcpu[id_dn];
	vf_dn[0] = up_f + val_maskf[0] * up_lay->kf;
	vf_dn[1] = up_f + val_maskf[1] * up_lay->kf;
	vf_dn += dn_lay->sz;
	vf_dn[0] = up_f + val_maskf[2] * up_lay->kf;
	vf_dn[1] = up_f + val_maskf[3] * up_lay->kf;
} // ///////////////////////////////////////////////////////////////////////////
