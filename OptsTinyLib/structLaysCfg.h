#pragma once
#include <vector>
#include "KoefsFlt.h"

class structLaysCfg{
public:
	static const size_t DEF_SIZE = 3;
	size_t cntlays = DEF_SIZE;
	size_t topX = 1, topY = 1;
	size_t digits = 2;
	size_t cpuSingle = 0;
	size_t cpuMultiThreaded = 0;
	KoefsFlt koefsF;

	size_t sizeX(size_t n_lay){ return topX << (cntlays - (n_lay + 1)); }
	size_t sizeY(size_t n_lay){ return topY << (cntlays - (n_lay + 1)); }
	size_t sizeX(int n_lay){ return topX << (cntlays - size_t(n_lay + 1)); }
	size_t sizeY(int n_lay){ return topY << (cntlays - size_t(n_lay + 1)); }
	size_t bottomY(){ return topY << (cntlays - 1); }
	size_t bottomX(){ return topX << (cntlays - 1); }
	size_t bottomSquare(){ return bottomX() * bottomY(); }

	bool isGPU(int n_lay){ return n_lay < (int)cntlays - int(cpuSingle + cpuMultiThreaded); }
	bool isMT(int n_lay){ return !isGPU(n_lay) && (n_lay < (int)cntlays - int(cpuSingle)); }

	void setConfig(size_t top_x, size_t top_y, size_t cpu = 0, size_t mt = 0, size_t cnt_lays=0);
	size_t setKoefsF(const vector<float>& vf_in);
	size_t setKoefsF(const char* s_in, const char delimiter = ' ');
	void resize(size_t new_size);

	std::vector<int> vikf();
private:
}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
