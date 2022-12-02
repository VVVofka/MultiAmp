#pragma once
#ifdef _DEBUG
#include <vector>
#include <amp.h>
#include <amp_short_vectors.h>
#include <string>

namespace EngineDbg{
	using namespace Concurrency::graphics;	//	float_2

	extern std::vector<std::vector<int>> va;
	extern std::vector<std::vector<float_2>> vf;
	void initV(size_t cnt_lays, size_t size_lay0);
	
	void setVA(size_t n_lay, const concurrency::array<int, 2>& vgpu);
	void setVA(size_t n_lay, const concurrency::array<int, 2>* vgpu);
	void setVA(size_t n_lay, const std::vector<int>& v_cpu);
	void setVA(size_t n_lay, const std::vector<int>* v_cpu);

	void setVF(size_t n_lay, const concurrency::array<float_2, 2>& vgpu);
	void setVF(size_t n_lay, const concurrency::array<float_2, 2>* vgpu);
	void setVF(size_t n_lay, const std::vector<float_2>& v_cpu);
	void setVF(size_t n_lay, const std::vector<float_2>* v_cpu);

	void Dump(const std::string& s);

}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#define VVVDBG_IF_DBG(ANY_OPER) (ANY_OPER);
#define VVVDBG_INIT_V(CNT_LAY, SIZE_LAY0) {EngineDbg::initV(size_t(CNT_LAY), size_t(SIZE_LAY0));}
#define VVVDBG_SET_A(N_LAY, V_SOURCE) (EngineDbg::setVA(size_t(N_LAY), (V_SOURCE) ))
#define VVVDBG_SET_F(N_LAY, V_SOURCE) (EngineDbg::setVF(size_t(N_LAY), (V_SOURCE) ))
#define VVVDBG_DUMP(STRING_DUMP) {EngineDbg::Dump(STRING_DUMP);}
#else
#define VVVDBG_IF_DBG(ANY_OPER) {}
#define VVVDBG_INIT_V(CNT_LAY) {}
#define VVVDBG_SET_A(N_LAY, VGPU) 
#define VVVDBG_SET_F(N_LAY, VGPU) 
#define VVVDBG_DUMP(STRING_DUMP) {}
#endif // DEBUG

