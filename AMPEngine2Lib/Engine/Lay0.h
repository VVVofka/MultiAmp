#pragma once
#include <vector>
#include <string>
#include <random>
#include "LayBase.h"
#include "..\MDX\Vertex.h"
#include <amp.h>
#include <amp_graphics.h>

using namespace Concurrency;

class Lay0 : public LayBase{
public:
	Lay0(structAll* cfg_all, accelerator_view* m_accl_view);
	~Lay0();
	VGpuCpu<int, 2> va;	// -1 - empty point

	std::vector<Vertex2D> vcpuScreen;
	concurrency::array<Vertex2D, 1>* vgpuScreen = NULL;		//[pointsCnt] for render [-1...+1]

	int countPoint = 0;

	bool isLoad()const;
	std::string sDumpAcpu(const int digits)const;
	std::string sDumpAgpu(const int digits)const;
	std::string DumpAcpu(const int digits)const;
	std::string DumpAgpu(const int digits)const;
	concurrency::array<Vertex2D, 1>* cpuPoint2gpuPoint(const uint count_point);

	void cpu2gpu(){ va.cpu2gpu(); }
	void gpu2cpu(){ va.gpu2cpu(); }

private:
	void fill_vScreen();
	void fill_va();
}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

