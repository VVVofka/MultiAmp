// Processes.cpp : Определяет функции для статической библиотеки.
#include "Processes.h"

namespace executor{
	using namespace concurrency::graphics;
	void Processes::Create(Lays* p_lays, Masks_a* p_Mask_a, Masks_f* p_Masks_f){
		processA.Create(p_lays, p_Mask_a);
		processF.Create(p_lays, p_Masks_f);
	} // //////////////////////////////////////////////////////////////////////
	void Processes::RunAll(const int_2 shift){
		processA.NormalizeV();
		processA.RunAll(shift);
		processF.RunAll(shift);
	} // //////////////////////////////////////////////////////////////////////

}
