#include <ppl.h>				//	parallel_for
#include "ProcessA.h"

void ProcessA::cpuRunMid(LayMid* up_lay){
	LayMid* dn_lay = up_lay - 1;
	if(dn_lay->cpuType == CPUtype::GPU)
		dn_lay->va.gpu2cpu();

	for(size_t id_up = 0; id_up < up_lay->sz; id_up++){
		mtcpuRunMid1(up_lay, id_up);
	}
} // ///////////////////////////////////////////////////////////////////////////
void ProcessA::mtRunMid(LayMid* up_lay){
	LayMid* dn_lay = up_lay - 1;
	if(dn_lay->cpuType == CPUtype::GPU)
		dn_lay->va.gpu2cpu();

	parallel_for(size_t(0), up_lay->sz, [=](size_t id_up) {
		mtcpuRunMid1(up_lay, id_up);
		});
} // ///////////////////////////////////////////////////////////////////////////
void ProcessA::mtcpuRunMid1(LayMid* up_lay, const size_t id_up){
	LayMid* dn_lay = up_lay - 1;
	const size_t x = id_up % up_lay->sz;
	const size_t y = id_up / up_lay->sz + 1;	// begin from top & right to left !
	const size_t id_dn = 2 * (y * dn_lay->sz + x);
	int* va_dn = &dn_lay->va.vcpu[id_dn];
	
	register int sum = amask->vcpu[va_dn[1]]; 
	sum = (sum << 1) | amask->vcpu[va_dn[0]];
	va_dn -= dn_lay->sz;						// begin from top & right to left !
	sum = (sum << 1) | amask->vcpu[va_dn[1]];
	up_lay->va.vcpu[id_up] = (sum << 1) | amask->vcpu[va_dn[0]];
} // //////////////////////////////////////////////////////////////////////////////////