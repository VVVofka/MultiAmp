#include "LayBase.h"

LayBase::LayBase(int n_lay, structAll* cfg_all, accelerator_view* m_accl_view){
	nlay = n_lay;
	this->cfg_all = cfg_all;
	this->m_accl_view = m_accl_view;
	sz.x = cfg_all->lays.sizeX(n_lay);
	sz.y = cfg_all->lays.sizeY(n_lay);
	//va.Create(sz, is_gpu, m_accl_view);
} // ///////////////////////////////////////////////////////////////////////////////
bool LayBase::isLoad() const{
	if(sz.x <= 0 || sz.y <= 0) return false;
	return va.vcpu.size() > 0;
} // ///////////////////////////////////////////////////////////////////////////////
