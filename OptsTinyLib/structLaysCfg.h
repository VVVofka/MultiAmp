#pragma once
#include <vector>
#include "KoefsFlt.h"

class structLaysCfg{
public:
	static const size_t DEF_SIZE = 3;
	size_t cntlays = DEF_SIZE;
	size_t topSize = 1;
	size_t digits = 2;
	size_t cpuSingle = 0;
	size_t cpuMultiThreaded = 0;
	KoefsFlt koefsF;

	size_t sizeLay(size_t n_lay){ return topSize << (cntlays - (n_lay + 1)); }
	size_t sizeLay(int n_lay){ return topSize << (cntlays - (n_lay + 1)); }
	size_t sizeBottom(){ return topSize << (cntlays - 1); }
	size_t bottomSquare(){ return sizeBottom() * sizeBottom(); }

	bool isGPU(int n_lay){ 
		if(n_lay <= 1)
			return true;
		return n_lay < (int)cntlays - int(cpuSingle + cpuMultiThreaded); 
	}
	bool isMT(int n_lay){ 
		if(n_lay <= 1)
			return false;
		return !isGPU(n_lay) && (n_lay < (int)cntlays - int(cpuSingle)); 
	}
	size_t setConfig(size_t top_size, size_t one_core, size_t mt, const char* s_koefs, const char delimiter = ' ');
	size_t setConfig(size_t top_size, size_t one_core, size_t mt, const vector<float>* vkoef_in);
	void resize(size_t new_cnt_lays);
	int intKF(size_t idx)const{ return int(lrint(pow(10, (int)digits) * koefsF[idx])); }
	void setIntKF(size_t idx, int val){ koefsF[idx] = val / pow(10, (int)digits); }
private:
}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
