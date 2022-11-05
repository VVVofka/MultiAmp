#pragma once
#include <vector>
#include <string>
#include <random>
#include "LayBase.h"
#include "Vertex.h"

class Lay0 : public LayBase{
public:
	concurrency::array<Vertex2D, 1>* vgpuScreen = NULL;		//[pointsCnt] for render [-1...+1]

	concurrency::array<Vertex2D, 1>* Create(const int_2 sz_0, const std::vector<int>& va_inp);
	~Lay0();

	int countPoint = 0;
	int SetRndScreenPoints(const int count, std::mt19937& gen);
	void SetScreenPoints(const int count, const int_2* ptr);

	bool isLoad()const;
	std::string sDumpA(const int digits)const;
	std::string DumpA(const int digits = 2)const;
	concurrency::array<Vertex2D, 1>* cpuPoint2gpuPoint(const int count_point);

	using LayBase::cpu2gpu;
	using LayBase::gpu2cpu;

private:
	static int defPointsCnt(const std::vector<int>& vi_inp);
};

