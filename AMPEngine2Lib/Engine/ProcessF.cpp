#include "ProcessF.h"
#include "EngineDbg.h"

ProcessF::ProcessF(Lays* p_lays, MaskF* p_Masks_f){
	lays = p_lays;
	fmasks = p_Masks_f;

} // /////////////////////////////////////////////////////////////////////////////
void ProcessF::RunAll(const uint_2 shift, const uint iter){
#define DIGITS 3
	for(int nmidlay = lays->cntMidLays - 1; nmidlay > 1; nmidlay--){
		
		const LayMid* up = lays->vMidLays[nmidlay];
		VVVDBG_IF_DBG(up->cpuType == CPUtype::GPU ? \
			VVVDBG_SET_F(nmidlay + 1, up->vf.vgpu) : \
			VVVDBG_SET_F(nmidlay + 1, up->vf.vcpu));
		VVVDBG_DUMP(up->sDumpF(DIGITS));

		LayMid* dn = lays->vMidLays[nmidlay - 1];
		VVVDBG_IF_DBG(dn->cpuType == CPUtype::GPU ? \
			VVVDBG_SET_F(nmidlay, dn->vf.vgpu) : \
			VVVDBG_SET_F(nmidlay, dn->vf.vcpu));
		VVVDBG_DUMP(dn->sDumpF(DIGITS));

		const int tp = (int)dn->cpuType;
		(this->*arFuncRun[tp])(nmidlay);	//{&ProcessF::gpuRun1, &ProcessF::mtRun, &ProcessF::cpuRun}
		if(dn->cpuType == CPUtype::GPU && up->cpuType != CPUtype::GPU)
			dn->cpu2gpu();
		VVVDBG_IF_DBG(dn->cpuType == CPUtype::GPU ? \
			VVVDBG_SET_F(nmidlay, dn->vf.vgpu) : \
			VVVDBG_SET_F(nmidlay, dn->vf.vcpu));
		VVVDBG_DUMP(dn->sDumpF(DIGITS));
	}
	gpuRun0(shift, iter); 
	VVVDBG_IF_DBG(lays->lay0.DumpAgpu(DIGITS));
#undef DIGITS
} // ///////////////////////////////////////////////////////////////////////////
