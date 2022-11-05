#pragma once
#include "Lay0.h"
#include "LayMid.h"
#include "LaysCPUCfg.h"

class Lays{	//  : public Lay0
public:
	Lay0 lay0;
	std::vector<LayMid> vMidLays;
	int cntMidLays = 0;

	concurrency::array<Vertex2D, 1>* Create(
		const int_2 sz_0,			// size x lay0
		const LaysCPUCfg& cfg,		// count gpu mt cpu
		const std::vector<int>& vi		// szx_0 * szy_0
	);
	bool isLoad();

	std::string sDumpA(int idx = -1, const int digits = 2)const;
	std::string sDumpF(int idx = -1, const int digits = 2)const;

	std::string DumpA(int idx = -1, const int digits = 2)const;
	std::string DumpF(int idx = -1, const int digits = 2)const;

private:
	int fillvMidLays(
		const int_2 sz_1,
		const LaysCPUCfg cfg			// count gpu mt cpu
	);
};

