#pragma once
#include <vector>
#include "structCfgBase.h"

class structLaysCfg : public structCfgBase{
public:
	size_t topX = 1, topY = 1;
	size_t digits = 2;
	std::vector<int> vkf;
	size_t cpuSingle = 0;
	size_t cpuMultiThreaded = 0;

	size_t laysCnt(){ return vkf.size(); }
	size_t sizeX(size_t n_lay){ return topX << (vkf.size() - (n_lay + 1)); }
	size_t sizeY(size_t n_lay){ return topY << (vkf.size() - (n_lay + 1)); }
	size_t sizeX(int n_lay){ return topX << (vkf.size() - size_t(n_lay + 1)); }
	size_t sizeY(int n_lay){ return topY << (vkf.size() - size_t(n_lay + 1)); }
	size_t bottomY(){ return topY << (vkf.size() - 1); }
	size_t bottomX(){ return topX << (vkf.size() - 1); }

	bool isGPU(int n_lay){ return n_lay < (int)laysCnt() - int(cpuSingle + cpuMultiThreaded); }
	bool isMT(int n_lay){ return !isGPU(n_lay) && (n_lay < (int)laysCnt() - int(cpuSingle)); }

	static const size_t DEF_SIZE = 5;

	bool isEqual(const structCfgBase* other){
		structLaysCfg* p = (structLaysCfg*)other;
		return topX == p->topX
			&& topY == p->topY
			&& digits == p->digits
			&& vkf == p->vkf
			&& cpuSingle == p->cpuSingle
			&& cpuMultiThreaded == p->cpuMultiThreaded
			;
	} // ///////////////////////////////////////////////////////////////////////////////////

private:
};
