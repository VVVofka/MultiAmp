#include "ProcessF.h"
#include "EngineDbg.h"

ProcessF::ProcessF(Lays* p_lays, MaskF* p_Masks_f){
	lays = p_lays;
	fmasks = p_Masks_f;

} // /////////////////////////////////////////////////////////////////////////////
void ProcessF::RunAll(const int_2 shift){
	for(int nmidlay = lays->cntMidLays - 1; nmidlay > 1; nmidlay--){
		const LayMid* up = lays->vMidLays[nmidlay];
		LayMid* dn = lays->vMidLays[nmidlay - 1];
		const int tp = (int)dn->cpuType;
		(this->*arFuncRun[tp])(nmidlay);	//{&ProcessF::gpuRun1, &ProcessF::mtRun, &ProcessF::cpuRun}
		if(dn->cpuType == CPUtype::GPU && up->cpuType != CPUtype::GPU)
			dn->cpu2gpu();
	}
	gpuRun0(shift); 
} // ///////////////////////////////////////////////////////////////////////////
