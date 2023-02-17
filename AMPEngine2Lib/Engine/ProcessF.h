#pragma once
#include <amp_graphics.h>
#include "Lays.h"
#include "MaskF.h"

using namespace Concurrency::graphics;	// int_2

class ProcessF{
	typedef void (ProcessF::* pFunc)(LayMid* up_lay);

	Lays* lays = NULL;
	MaskF* fmasks = NULL;	// TODO: del

public:
	ProcessF(Lays* p_lays, MaskF* p_Masks_f);
	void RunAllLays(const int_2 shift, const uint iter);

private:
	//	Lay0
	void gpuRun0(const int_2 shift, const uint iter);
	void gpuRun0Split1(const int_2 shift);
	void gpuRun0Split2x(const int_2 shift, const uint signFor0);
	void gpuRun0Split2y(const int_2 shift, const uint signFor0);

	// Other Lays
	void gpuRunMid(LayMid* up_lay);
	void mtRunMid(LayMid* up_lay);
	void cpuRunMid(LayMid* up_lay);
	void mtcpuRunMid1(LayMid* up_lay, const size_t id_up);

	const pFunc vFuncRunMid[3] = {&ProcessF::gpuRunMid, &ProcessF::mtRunMid, &ProcessF::cpuRunMid};
}; // #### ProcessF #########################################################################
