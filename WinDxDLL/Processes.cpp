#include "Processes.h"

using namespace concurrency::graphics;
Processes::Processes(structAll* p_cfg_all, Lays* p_lays) :
	masks(p_cfg_all),
	processA(p_lays, &masks.a),
	processF(p_lays, &masks.f){
	lays = p_lays;
	cfg_all = p_cfg_all;
} // ///////////////////////////////////////////////////////////////////////////
void Processes::RunAll(const int_2 shift){
	processA.RunAll(shift);
	processF.RunAll(shift);
} // //////////////////////////////////////////////////////////////////////

