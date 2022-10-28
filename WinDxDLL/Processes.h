#pragma once
#include "ProcessA.h"
#include "ProcessF.h"

namespace executor{
	class Processes{
	public:
		ProcessA processA;
		ProcessF processF;

		void Create(Lays* p_lays, Masks_a* p_Mask_a, Masks_f* p_Masks_f);
		void RunAll(const int_2 shift);
	}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

}