#pragma once
#include <amp_graphics.h>

#include "Lays.h"
#include "MaskF.h"

using namespace Concurrency::graphics;
class ProcessF{
	typedef void (ProcessF::* pFunc)(const int n_lay);

	Lays* lays = NULL;
	MaskF* fmasks = NULL;

public:
	void Create(Lays* p_lays, MaskF* p_Masks_f);
	void RunAll(const int_2 shift);

private:
	void gpuRun0(const int_2 shift);
	void gpuRun1(const int ncurlay);
	void mtRun(const int ncurlay);
	void cpuRun(const int ncurlay);

	//float_2 rSizeDn0; // 1/size lay0

	const pFunc arFuncRun[3] = {&ProcessF::gpuRun1, &ProcessF::mtRun, &ProcessF::cpuRun};
}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
