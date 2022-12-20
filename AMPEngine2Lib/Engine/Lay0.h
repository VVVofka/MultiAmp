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
	VGpuCpu2<int> va;	// -1 - empty point
	VGpuCpu2<float_2> vf;	
	
	concurrency::array<uint, 1>* vgpuMaskMove = NULL;

	std::vector<Vertex2D> vcpuScreen;
	concurrency::array<Vertex2D, 1>* vgpuScreen = NULL;		//[pointsCnt] for render [-1...+1]

	int countPoint = 0;

	bool isLoad()const;

	static const int defdig = 3;
	std::string sDumpAcpu(const int digits = defdig)const;
	std::string sDumpAgpu(const int digits = defdig)const;
	std::string sDumpFgpu(const int digits = defdig)const;
	std::string DumpAcpu(const int digits = defdig)const;
	std::string DumpAgpu(const int digits = defdig)const;
	std::string sDumpScreen(const int digits = defdig)const;
	concurrency::array<Vertex2D, 1>* cpuPoint2gpuPoint(const uint count_point);

	void cpu2gpu(){ va.cpu2gpu(); vf.cpu2gpu();}
	void gpu2cpu(){ va.gpu2cpu(); vf.gpu2cpu();}

private:
	void fill_vScreen();
	void fill_va();
	void fill_vf();
	void fill_vmaskmove();
}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

