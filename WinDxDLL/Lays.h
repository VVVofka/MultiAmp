#pragma once
#include "Lay0.h"
#include "LayMid.h"

class Lays : public Lay0{
public:
	Lay0 lay0;
	std::vector<LayMid> vMidLays;
	int cntMidLays;

	Lays();

	bool Create(
		const int_2 sz_0,					// size x lay0
		const LaysCPUCfg cfg,				// count gpu mt cpu
		const std::vector<int>& vi_inp,			// szx_0 * szy_0
		const std::vector<float_2>& vf_inp,		// (szx_0 * szy_0)
		const float k_decAfterMove
	);
	bool isLoad();

	std::string sDumpA(int idx = -1, const int digits = 2)const;
	std::string sDumpF(int idx = -1, const int digits = 2)const;
	std::string sDumpV(int idx = -1, const int digits = 3)const;

	std::string DumpA(int idx = -1, const int digits = 2)const;
	std::string DumpF(int idx = -1, const int digits = 2)const;
	std::string DumpV(int idx = -1, const int digits = 3)const;

private:
	int fillvMidLays(
		const int_2 sz_1,
		const LaysCPUCfg cfg			// count gpu mt cpu
	);
};

