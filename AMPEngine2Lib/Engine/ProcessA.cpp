#include "ProcessA.h"
#include "EngineDbg.h"

ProcessA::ProcessA(Lays* p_lays, MaskA* p_Mask_a){
	lays = p_lays;
	amask = p_Mask_a;
} // ////////////////////////////////////////////////////////////////////////////////////////////
void ProcessA::RunAll(const int_2 shift){		
	VVVDBG_IF_DBG(lays->DumpA(0));
	gpuRun0(shift);
	VVVDBG_IF_DBG(lays->DumpAgpu(1));

	LayMid* dn, * up = lays->vMidLays[0];
	for(int nmid = 1; nmid < lays->cntMidLays; nmid++){
		dn = up;
		up = lays->vMidLays[nmid];

		if(dn->cpuType == CPUtype::GPU && up->cpuType != CPUtype::GPU)
			dn->gpu2cpu();
		
		VVVDBG_IF_DBG(lays->DumpA(nmid));
		int tp = (int)up->cpuType;
		(this->*arFuncRun[tp])(nmid);	//{&ProcessA::gpuRun1, &ProcessA::mtRun, &ProcessA::cpuRun}
		VVVDBG_IF_DBG(lays->DumpA(nmid + 1));
	}
} // ///////////////////////////////////////////////////////////////////////////
