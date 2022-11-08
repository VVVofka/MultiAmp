#include "ProcessA.h"
using namespace concurrency;
using namespace concurrency::graphics;

void ProcessA::Create(Lays* p_lays, MaskA* p_Mask_a){
	lays = p_lays;
	amask = p_Mask_a;
} // ///////////////////////////////////////////////////////////////////////////
void ProcessA::RunAll(const int_2 shift){		// return sum vabs from last lay
	gpuRun0(shift);
	if(lays->vMidLays[0].gpuIn)
		lays->vMidLays[0].gpu2cpu();
	for(int j = 1; j < lays->cntMidLays; j++){
		LayMid* up = &lays->vMidLays[j];
		LayMid* dn = &lays->vMidLays[j - 1];
		int tp = (int)dn->cpuType;
		(this->*arFuncRun[tp])(j);	//{&ProcessA::gpuRun1, &ProcessA::mtRun, &ProcessA::cpuRun}
		if(up->gpuIn)
			up->gpu2cpu();
	}
} // ///////////////////////////////////////////////////////////////////////////
