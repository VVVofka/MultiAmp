#include "ProcessA.h"

ProcessA::ProcessA(Lays* p_lays, MaskA* p_Mask_a){
	lays = p_lays;
	amask = p_Mask_a;
} // ////////////////////////////////////////////////////////////////////////////////////////////
void ProcessA::RunAll(const int_2 shift){		// return sum vabs from last lay
	gpuRun0(shift);

	LayMid  *dn, *up = lays->vMidLays[0];
	if(up->cpuType != CPUtype::GPU)
		up->gpu2cpu();

	for(int j = 1; j < lays->cntMidLays; j++){
		dn = up;
		up = lays->vMidLays[j];
		int tp = (int)dn->cpuType;
		(this->*arFuncRun[tp])(j);	//{&ProcessA::gpuRun1, &ProcessA::mtRun, &ProcessA::cpuRun}
		if(dn->cpuType == CPUtype::GPU && up->cpuType != CPUtype::GPU)
			up->gpu2cpu();
	}
} // ///////////////////////////////////////////////////////////////////////////
