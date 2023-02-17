#include "LayBase.h"

LayBase::LayBase(uint n_lay, structAll* cfg_all, accelerator_view* m_accl_view){
	nlay = n_lay;
	this->cfg_all = cfg_all;
	this->m_accl_view = m_accl_view;
	sz = cfg_all->lays.sizeLay(n_lay);

//#ifdef _DEBUG
//	{size_t szx = cfg_all->lays.bottomX();
//	size_t szy = cfg_all->lays.bottomY();
//	std::vector<float_2> vtmp(szx * szy);
	//SAFE_DELETE(vgpuDbg);
	//vgpuDbg = new concurrency::array<float_2, 2>(szy, szx, vtmp.begin(), *m_accl_view); }
//#endif	//  _DEBUG
} // ///////////////////////////////////////////////////////////////////////////////
LayBase::~LayBase(){
//#ifdef _DEBUG
//	SAFE_DELETE(vgpuDbg);
//#endif	//  _DEBUG
} // ///////////////////////////////////////////////////////////////////////////////

