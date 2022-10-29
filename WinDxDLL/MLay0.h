#pragma once
#include <vector>
#include <string>
#include <random>
#include "MLayBase.h"
#include "Vertex.h"

class MLay0 : public MLayBase{
public:
	concurrency::array<Vertex2D, 1>* vgpuScreen = NULL;		//[pointsCnt] for render [-1...+1]

	void Create(
		const int_2 sz_0,
		const std::vector<int>& va_inp,			// sz_0.x * sz_0.y
		const std::vector<float_2>& vf_inp		// sz_0.x * sz_0.y
	);
	~MLay0();

	int countPoint = 0;
	int SetRndScreenPoints(const int count, std::mt19937& gen);
	void SetScreenPoints(const int count, const int_2* ptr);

	bool isLoad()const;
	std::string sDumpA(const int digits)const;
	std::string sDumpF(const int digits)const;
	std::string DumpA(const int digits = 2)const;
	std::string DumpF(const int digits = 2)const;
	void cpuPoint2gpuPoint(const int count_point);

private:
	static int defPointsCnt(const std::vector<int>& vi_inp);
};

