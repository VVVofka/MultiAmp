#ifdef _DEBUG
#include "EngineDbg.h"
using namespace Concurrency::graphics;	//	float_2
namespace EngineDbg{
	std::vector<std::vector<int>> va;
	std::vector<std::vector<float_2>> vf;

	void initV(size_t cnt_lays, size_t size_lay0){
		va.resize(cnt_lays);
		vf.resize(cnt_lays);
		for(size_t j = 0; j < cnt_lays; j++){
			va[j].resize(size_lay0);
			vf[j].resize(size_lay0);
			size_lay0 /= 4;
		}
	} // //////////////////////////////////////////////////////////////////////
	void setVA(size_t n_lay, const concurrency::array<int, 2>& vgpu){
		concurrency::copy(vgpu, va[n_lay].begin());
	} // //////////////////////////////////////////////////////////////////////
	void setVA(size_t n_lay, const concurrency::array<int, 2>* vgpu){
		concurrency::copy(*vgpu, va[n_lay].begin());
	} // //////////////////////////////////////////////////////////////////////
	void setVA(size_t n_lay, const std::vector<int>& v_cpu){
		va[n_lay] = v_cpu;
	} // //////////////////////////////////////////////////////////////////////
	void setVA(size_t n_lay, const std::vector<int>* v_cpu){
		va[n_lay] = *v_cpu;
	} // //////////////////////////////////////////////////////////////////////

	void setVF(size_t n_lay, const concurrency::array<float_2, 2>& vgpu){
		concurrency::copy(vgpu, vf[n_lay].begin());
	} // //////////////////////////////////////////////////////////////////////
	void setVF(size_t n_lay, const concurrency::array<float_2, 2>* vgpu){
		concurrency::copy(*vgpu, vf[n_lay].begin());
	} // //////////////////////////////////////////////////////////////////////
	void setVF(size_t n_lay, const std::vector<float_2>& v_cpu){
		vf[n_lay] = v_cpu;
	} // //////////////////////////////////////////////////////////////////////
	void setVF(size_t n_lay, const std::vector<float_2>* v_cpu){
		vf[n_lay] = *v_cpu;
	} // //////////////////////////////////////////////////////////////////////


	void EngineDbg::Dump(const std::string& s){
		_RPT0(0, s.c_str());
	} // ////////////////////////////////////////////////////////////////////////
} // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#endif
