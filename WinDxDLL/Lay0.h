#pragma once
#include <vector>
#include <string>
#include <random>
#include "LayBase.h"
#include "Vertex.h"

class Lay0 : public LayBase{
public:
	Lay0(structAll* cfg_all, accelerator_view* m_accl_view = NULL);
	~Lay0();

	std::vector<Vertex2D> vcpuScreen;
	concurrency::array<Vertex2D, 1>* vgpuScreen = NULL;		//[pointsCnt] for render [-1...+1]

	int countPoint = 0;

	bool isLoad()const;
	std::string sDumpA(const int digits)const;
	std::string DumpA(const int digits = 2)const;
	concurrency::array<Vertex2D, 1>* cpuPoint2gpuPoint(const int count_point);

	using LayBase::cpu2gpu;
	using LayBase::gpu2cpu;

private:
	void fill_vScreen();
	void fill_va();
}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

