#include "Lays.h"
#include "..\myUtil.h"

Lays::Lays(structAll* cfg_all, accelerator_view* m_accl_view) :
	lay0(cfg_all, m_accl_view){

	_ASSERTE(lay0.isLoad());
	if(!correctMtCpu(cfg_all))
		return;
	cntMidLays = (int)cfg_all->lays.cntlays - 1;	// w/o lay0
	vMidLays.resize(cntMidLays);
	//	cfg_all->lays.cpuSingle == 0 && cfg_all->lays.cpuMultiThreaded == 2
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
bool Lays::correctMtCpu(structAll* cfg){
	const int layscnt = int(cfg->lays.cntlays);
	const int processcnt = layscnt - 1;
	_ASSERTE(processcnt > 0);
	int mt = int(cfg->lays.cpuMultiThreaded);
	int cp = int(cfg->lays.cpuSingle);
	const int min_gp = 1;
	while(mt + cp + min_gp > processcnt){
		if(mt > 0)
			--mt;
		else if(cp > 0)
			--cp;
		else
			return false;
	}
	cfg->lays.cpuMultiThreaded = size_t(mt);
	cfg->lays.cpuSingle = size_t(cp);
	return true;
} // /////////////////////////////////////////////////////////////////////////////////////
