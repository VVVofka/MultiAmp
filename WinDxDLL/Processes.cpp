#include "Processes.h"

using namespace concurrency::graphics;
Processes::Processes(structAll* p_cfg_all, Lays* p_lays){
	lays = p_lays;
	cfg_all = p_cfg_all;
} // ///////////////////////////////////////////////////////////////////////////
void Processes::Create(Lays* p_lays, MaskA* p_Mask_a, MaskF* p_Masks_f){
	processA.Create(p_lays, p_Mask_a);
	processF.Create(p_lays, p_Masks_f);
} // //////////////////////////////////////////////////////////////////////
void Processes::RunAll(const int_2 shift){
	processA.RunAll(shift);
	processF.RunAll(shift);
} // //////////////////////////////////////////////////////////////////////

