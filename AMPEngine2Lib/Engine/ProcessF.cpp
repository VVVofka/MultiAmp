#include "ProcessF.h"
#include "EngineDbg.h"

ProcessF::ProcessF(Lays* p_lays, MaskF* p_Masks_f){
	lays = p_lays;
	fmasks = p_Masks_f;

} // /////////////////////////////////////////////////////////////////////////////
void ProcessF::RunAllLays(const int_2 shift, const uint iter){
	for(int nMidUp = lays->cntMidLays - 1; nMidUp > 0; nMidUp--){
		const LayMid* up = lays->vMidLays[nMidUp];
		LayMid* dn = lays->vMidLays[nMidUp - 1];
		const int tp = (int)dn->cpuType;
		(this->*vFuncRunMid[tp])(nMidUp);	//{&ProcessF::gpuRunMid, &ProcessF::mtRunMid, &ProcessF::cpuRunMid}
		if(dn->cpuType == CPUtype::GPU && up->cpuType != CPUtype::GPU)
			dn->cpu2gpu();
	}
	gpuRun0(shift, iter); 
} // ///////////////////////////////////////////////////////////////////////////
//VVVDBG_IF_DBG(up->cpuType == CPUtype::GPU ? \
//	VVVDBG_SET_F(nmidlay + 1, up->vf.vgpu) : \
//	VVVDBG_SET_F(nmidlay + 1, up->vf.vcpu));
//VVVDBG_DUMP(up->sDumpF());
