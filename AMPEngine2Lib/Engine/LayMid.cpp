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
	va.Create(sz, create_gpu, m_accl_view);
	vf.Create(sz, create_gpu, m_accl_view);
	
	std::vector<float_2> vkf(cfg_all->masks.vf.size());
	float koeff = float(cfg_all->lays.koefsF[n_lay - 1]);
	for(size_t j = 0; j < cfg_all->masks.vf.size(); j++)
		vkf[j] = koeff * cfg_all->masks.vf[j];
	kF.Create(sz, vkf, create_gpu, m_accl_view);
	//for(size_t j = 0; j < cfg_all->masks.vf.size(); j++)
	//	kF[j] = cfg_all->masks.vf[j];
	//@@kF = float(cfg_all->lays.koefsF[n_lay - 1]);
} // /////////////////////////////////////////////////////////////////////////////////
