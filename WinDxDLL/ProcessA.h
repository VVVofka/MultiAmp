#pragma once
#include <vector>
#include <amp.h>
#include <amp_math.h>
#include <amp_graphics.h>

#include "LayMid.h"
#include "Lays.h"
#include "Masks_a.h"

namespace executor{
	class ProcessA{
		typedef void (ProcessA::* pFunc)(const int n_lay);

		Lays* lays = NULL;
		Masks_a* amask = NULL;

	public:
		void Create(Lays* p_lays, Masks_a* p_Mask_a);
		void RunAll(const int_2 shift);	// return sum vabs from last lay
		void NormalizeV();
		float_2 getNormKoef();

	private:
		void gpuRun0(const int_2 shift);
		void gpuRun1(const int n_lay);
		void mtRun(const int n_lay);
		void cpuRun(const int n_lay);

		const pFunc arFuncRun[3] = {&ProcessA::gpuRun1, &ProcessA::mtRun, &ProcessA::cpuRun};

		void defNormKoefAvg();
		void defNormKoefAbs();
		void defNormKoefLay0Avg();
		void defNormKoefLay0Abs();
		void defNormKoefFinishAvg(unsigned sz);
		void defNormKoefFinishAbs(unsigned sz);
		void defNormKoefReduct(unsigned sz);

		void ApplyKNormAvg();
		void ApplyKNormAbs();
	};
};
