#include "ProcessA.h"
#include "EngineDbg.h"

ProcessA::ProcessA(Lays* p_lays, MaskA* p_Mask_a){
	lays = p_lays;
	amask = p_Mask_a;
} // ////////////////////////////////////////////////////////////////////////////////////////////
void ProcessA::RunAllLays(const int_2 shift){
	gpuRun0(shift);

	for(int n_mid_up = 1; n_mid_up < lays->cntMidLays; n_mid_up++){
		LayMid* up_lay = lays->vMidLays[n_mid_up];
		int tp = (int)up_lay->cpuType;
		(this->*vFuncRunMid[tp])(up_lay);	//{&ProcessA::gpuRunMid, &ProcessA::mtRunMid, &ProcessA::cpuRunMid}
	}
} // ///////////////////////////////////////////////////////////////////////////
		//VVVDBG_IF_DBG(lays->DumpA(nmid));

		//VVVDBG_IF_DBG(lays->DumpA(nmid + 1));
		//VVVDBG_IF_DBG(up->cpuType == CPUtype::GPU ? VVVDBG_SET_A(nmid + 1, up->va.vgpu) : VVVDBG_SET_A(nmid + 1, up->va.vcpu));
