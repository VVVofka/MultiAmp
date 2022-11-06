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
	size_t bottomX(){ return topX << (vkf.size() - 1); }
	size_t bottomY(){ return topY << (vkf.size() - 1); }

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
