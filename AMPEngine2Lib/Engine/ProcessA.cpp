#include "ProcessA.h"
#include "EngineDbg.h"

ProcessA::ProcessA(Lays* p_lays, MaskA* p_Mask_a){
	lays = p_lays;
	amask = p_Mask_a;
} // ////////////////////////////////////////////////////////////////////////////////////////////
void ProcessA::RunAllLays(const int_2 shift){
	gpuRun0(shift);

	for(int nMidUp = 1; nMidUp < lays->cntMidLays; nMidUp++){
		LayMid* up = lays->vMidLays[nMidUp];
		int tp = (int)up->cpuType;
		(this->*vFuncRunMid[tp])(nMidUp);	//{&ProcessA::gpuRunMid, &ProcessA::mtRunMid, &ProcessA::cpuRunMid}
	}
} // ///////////////////////////////////////////////////////////////////////////
		//VVVDBG_IF_DBG(lays->DumpA(nmid));

		//VVVDBG_IF_DBG(lays->DumpA(nmid + 1));
		//VVVDBG_IF_DBG(up->cpuType == CPUtype::GPU ? VVVDBG_SET_A(nmid + 1, up->va.vgpu) : VVVDBG_SET_A(nmid + 1, up->va.vcpu));
