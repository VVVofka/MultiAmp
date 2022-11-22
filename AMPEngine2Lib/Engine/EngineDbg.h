#pragma once
#include <vector>
#include <amp.h>

class EngineDbg{
public:
	static std::vector<std::vector<int>> va;
	static void initVA(size_t cnt_lays){
		va.resize(cnt_lays); 
	}
	static void setVA(size_t n_lay, const concurrency::array<int, 2>& vgpu){
		concurrency::copy(vgpu, va[n_lay].begin()); 
	}

private:
	//void gpu2cpu(concurrency::array<int, 2>* gpu, ){ concurrency::copy(*vgpu, vcpu.begin()); }
}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#ifdef _DEBUG
#define VVVDBG_INIT_A(CNT_LAY) {EngineDbg::initVA(CNT_LAY);}
#define VVVDBG_SET_A(N_LAY, VGPU) {EngineDbg::setVA(N_LAY, VGPU);}
#else
#define VVVDBG_INIT_A(CNT_LAY) {}
#define VVVDBG_SET_A(N_LAY, VGPU) {}
#endif // DEBUG

