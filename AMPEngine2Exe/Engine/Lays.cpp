#include "Lays.h"
#include "..\myUtil.h"

Lays::Lays(structAll* cfg_all, accelerator_view* m_accl_view) : 
	lay0(cfg_all, m_accl_view){

	_ASSERTE(lay0.isLoad());

	cntMidLays = cfg_all->lays.laysCnt() - 1;	// w/o lay0
	vMidLays.resize(cntMidLays);
	for(int j = 0; j < cntMidLays; j++)
		vMidLays[j] = new LayMid(j + 1, cfg_all, m_accl_view);
} // ////////////////////////////////////////////////////////////////////////////////
Lays::~Lays(){
	for(size_t nlay = 0; nlay < vMidLays.size(); nlay++)
		SAFE_DELETE(vMidLays[nlay]);
} // ////////////////////////////////////////////////////////////////////////////////
bool Lays::isLoad(){
	if(lay0.isLoad() == false) return false;
	if(vMidLays.size() < 1) return false;
	_ASSERTE(vMidLays.size() == cntMidLays);
	for(int j = 0; j < cntMidLays; j++)
		if(vMidLays[j]->isLoad() == false)
			return false;
	return true;
} // //////////////////////////////////////////////////////////////////////////
