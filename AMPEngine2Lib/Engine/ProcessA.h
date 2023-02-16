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
	void RunAllLays(const int_2 shift);	// return sum vabs from last lay

private:
	void gpuRun0(const int_2 shift);
	void gpuRunMid(const int n_lay);
	void mtRunMid(const int n_lay);
	void cpuRunMid(const int n_lay);

	const pFunc vFuncRunMid[3] = {&ProcessA::gpuRunMid, &ProcessA::mtRunMid, &ProcessA::cpuRunMid};

};
