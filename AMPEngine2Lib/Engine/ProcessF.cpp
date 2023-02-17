#include "ProcessF.h"
#include "EngineDbg.h"

ProcessF::ProcessF(Lays* p_lays, MaskF* p_Masks_f){
	lays = p_lays;
	fmasks = p_Masks_f;
} // /////////////////////////////////////////////////////////////////////////////

void ProcessF::RunAllLays(const int_2 shift, const uint iter){
	for(int nMidUp = lays->cntMidLays - 1; nMidUp > 0; nMidUp--){
		LayMid* up_lay = lays->vMidLays[nMidUp];
		LayMid* dn_lay = up_lay - 1;
		const int tp = (int)dn_lay->cpuType;
		(this->*vFuncRunMid[tp])(up_lay);	//{&ProcessF::gpuRunMid, &ProcessF::mtRunMid, &ProcessF::cpuRunMid}
		if(dn_lay->cpuType == CPUtype::GPU && up_lay->cpuType != CPUtype::GPU)
			dn_lay->cpu2gpu();
	}
	gpuRun0(shift, iter); 
} // ///////////////////////////////////////////////////////////////////////////

//VVVDBG_IF_DBG(up_lay->cpuType == CPUtype::GPU ? \
//	VVVDBG_SET_F(nmidlay + 1, up_lay->vf.vgpu) : \
//	VVVDBG_SET_F(nmidlay + 1, up_lay->vf.vcpu));
//VVVDBG_DUMP(up_lay->sDumpF());
