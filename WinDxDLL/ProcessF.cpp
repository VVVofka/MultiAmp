#include "ProcessF.h"
namespace executor{
	void ProcessF::Create(Lays* p_lays, Masks_f* p_Masks_f){
		lays = p_lays;
		fmasks = p_Masks_f;
		//rSizeDn0 = float_2(1.f / lays->lay0.sz.x, 1.f / lays->lay0.sz.y); // TODO: use in amp?
	} // /////////////////////////////////////////////////////////////////////////////
	void ProcessF::RunAll(const int_2 shift){
		for(int nmidlay = lays->cntMidLays - 1; nmidlay > 0; nmidlay--){
			LayMid& up = lays->vMidLays[nmidlay];
			LayMid& dn = lays->vMidLays[nmidlay - 1];
			int tp = (int)dn.cpuType;
			(this->*arFuncRun[tp])(nmidlay);	//{&ProcessF::gpuRun1, &ProcessF::mtRun, &ProcessF::cpuRun}
			if(dn.gpuIn)
				dn.cpu2gpu();
		}
		gpuRun0(shift);
	} // ///////////////////////////////////////////////////////////////////////////
}