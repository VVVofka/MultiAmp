#pragma once
#include "MLay0.h"
#include "MLayMid.h"
#include "MLaysCPUCfg.h"

class MLays{	//  : public MLay0
public:
	MLay0 lay0;
	std::vector<MLayMid> vMidLays;
	int cntMidMLays = 0;

	bool Create(
		const int_2 sz_0,					// size x lay0
		const MLaysCPUCfg cfg,				// count gpu mt cpu
		const std::vector<int>& vi_inp,		// szx_0 * szy_0
		const std::vector<float_2>& vf_inp	// (szx_0 * szy_0)
		//const float k_decAfterMove
	);
	bool isLoad();

	std::string sDumpA(const int idx = -1, const int digits = 2)const;
	std::string sDumpF(const int idx = -1, const int digits = 2)const;

	std::string DumpA(const int idx = -1, const int digits = 2)const;
	std::string DumpF(const int idx = -1, const int digits = 2)const;

private:
	int fillvMidLays(
		const int_2 sz_1,
		const MLaysCPUCfg cfg			// count gpu mt cpu
	);
};

