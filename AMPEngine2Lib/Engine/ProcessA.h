#pragma once
#include <vector>
#include <amp.h>
#include <amp_math.h>
#include <amp_graphics.h>

#include "LayMid.h"
#include "Lays.h"
#include "MaskA.h"

class ProcessA{
	typedef void (ProcessA::* pFunc)(const int n_lay);

	Lays* lays;	// = NULL;
	MaskA* amask;	// = NULL;

public:
	ProcessA(Lays* p_lays, MaskA* p_Mask_a);
	void RunAll(const uint_2 shift);	// return sum vabs from last lay

private:
	void gpuRun0(const uint_2 shift);
	void gpuRun1(const int n_lay);
	void mtRun(const int n_lay);
	void cpuRun(const int n_lay);

	const pFunc arFuncRun[3] = {&ProcessA::gpuRun1, &ProcessA::mtRun, &ProcessA::cpuRun};

	//float_2 getNormKoef();
	//void defNormKoefAvg();
	//void defNormKoefAbs();
	//void defNormKoefLay0Avg();
	//void defNormKoefLay0Abs();
	//void defNormKoefFinishAvg(unsigned sz);
	//void defNormKoefFinishAbs(unsigned sz);
	//void defNormKoefReduct(unsigned sz);

	//void ApplyKNormAvg();
	//void ApplyKNormAbs();
};
