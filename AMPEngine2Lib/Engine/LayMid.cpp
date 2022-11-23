#include <crtdbg.h>	// _ASSERTE
#include "LayMid.h"

LayMid::LayMid(int n_lay, structAll* cfg_all, accelerator_view* m_accl_view) :
	LayBase(n_lay, cfg_all, m_accl_view){

	_ASSERTE(n_lay > 0);
	const bool is_dngpu = cfg_all->lays.isGPU(n_lay - 1);
	const bool is_gpu = cfg_all->lays.isGPU(n_lay);
	if(is_gpu)
		LayBase::cpuType = CPUtype::GPU;
	else if(cfg_all->lays.isMT(n_lay))
		LayBase::cpuType = CPUtype::MT;
	else
		LayBase::cpuType = CPUtype::CPU;
	const bool create_gpu = is_dngpu || is_gpu;	
	LayBase::va.Create(sz, create_gpu, m_accl_view);
	vf.Create(sz, create_gpu, m_accl_view);
} // /////////////////////////////////////////////////////////////////////////////////
void LayMid::gpu2cpu(){
	LayBase::gpu2cpu();
	vf.gpu2cpu();
} // /////////////////////////////////////////////////////////////////////////////////
void LayMid::cpu2gpu(){
	LayBase::cpu2gpu();
	vf.cpu2gpu();
} // /////////////////////////////////////////////////////////////////////////////////
void LayMid::gpu2other(std::vector<float_2>& v_dst) const{
	vf.gpu2other(v_dst);
} // /////////////////////////////////////////////////////////////////////////////////


