#include "EngineDbg.h"
#ifdef _DEBUG
namespace EngineDbg{
	std::vector<std::vector<int>> va;
	void initVA(size_t cnt_lays, size_t size_lay0){
		va.resize(cnt_lays);
		for(size_t j = 0; j < cnt_lays; j++){
			va[j].resize(size_lay0);
			size_lay0 /= 4;
		}
	} // //////////////////////////////////////////////////////////////////////
	void setVA(size_t n_lay, const concurrency::array<int, 2>& vgpu){
		concurrency::copy(vgpu, va[n_lay].begin());
	} // //////////////////////////////////////////////////////////////////////
	void setVA(size_t n_lay, const std::vector<int>& v_cpu){
		va[n_lay] = v_cpu;
	} // //////////////////////////////////////////////////////////////////////
} // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#endif
