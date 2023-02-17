#pragma once
#include <amp_graphics.h>	// int_2

#include "LayMid.h"
#include "Lays.h"
#include "MaskA.h"

class ProcessA{
	typedef void (ProcessA::* pFunc)(LayMid* up_lay);

	Lays* lays;	// = NULL;
	MaskA* amask;	// = NULL;

public:
	ProcessA(Lays* p_lays, MaskA* p_Mask_a);
	void RunAllLays(const int_2 shift);	// return sum vabs from last lay

private:
	void gpuRun0(const int_2 shift);
	void gpuRunMid(LayMid* up_lay);
	void mtRunMid(LayMid* up_lay);
	void cpuRunMid(LayMid* up_lay);
	void mtcpuRunMid1(LayMid* up_lay, const size_t id_up);

	const pFunc vFuncRunMid[3] = {&ProcessA::gpuRunMid, &ProcessA::mtRunMid, &ProcessA::cpuRunMid};
}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
