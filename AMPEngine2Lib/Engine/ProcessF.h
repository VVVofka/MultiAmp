#pragma once
#include <amp_graphics.h>
#include "Lays.h"
#include "MaskF.h"

using namespace Concurrency::graphics;	// int_2

class ProcessF{
	typedef void (ProcessF::* pFunc)(const int n_lay);

	Lays* lays = NULL;
	MaskF* fmasks = NULL;

public:
	ProcessF(Lays* p_lays, MaskF* p_Masks_f);
	void RunAll(const uint_2 shift);

private:
	void gpuRun0(const uint_2 shift);
	void gpuRun1(const int ncurlay);
	void mtRun(const int ncurlay);
	void cpuRun(const int ncurlay);

	const pFunc arFuncRun[3] = {&ProcessF::gpuRun1, &ProcessF::mtRun, &ProcessF::cpuRun};
}; // #### ProcessF #########################################################################
