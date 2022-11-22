#pragma once
#ifdef _DEBUG
#include <vector>
#include <amp.h>

namespace EngineDbg{
	extern std::vector<std::vector<int>> va;
	void initVA(size_t cnt_lays, size_t size_lay0);
	void setVA(size_t n_lay, const concurrency::array<int, 2>& vgpu);
}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#define VVVDBG_INIT_A(CNT_LAY, SIZE_LAY0) {EngineDbg::initVA(CNT_LAY, SIZE_LAY0);}
#define VVVDBG_SET_A(N_LAY, VGPU) {EngineDbg::setVA(size_t(N_LAY), VGPU);}
#else
#define VVVDBG_INIT_A(CNT_LAY) {}
#define VVVDBG_SET_A(N_LAY, VGPU) {}
#endif // DEBUG

