#include "Processes.h"

Processes::Processes(structAll* p_cfg_all, Lays* p_lays, accelerator_view* m_accl_view) :
	masks(p_cfg_all, m_accl_view),
	processA(p_lays, &masks.a),
	processF(p_lays, &masks.f),
	rnd(p_cfg_all->misc.curRndSeed){

	cfg_all = p_cfg_all;
	curIteration = p_cfg_all->misc.curIteration;
	rnd.setUpper((int)p_cfg_all->lays.bottomSquare());
} // ///////////////////////////////////////////////////////////////////////////
Processes::~Processes(){
	cfg_all->misc.curRndSeed = rnd.getSeed();
	cfg_all->misc.curIteration = curIteration;
} // ///////////////////////////////////////////////////////////////////////////
void Processes::RunAllLays(){
	int pos = (int)rnd.randk();	// max ~ 65500*65500
	int szx = (int)cfg_all->lays.sizeBottom();
	int x = pos % szx;
	int y = pos / szx;
	int_2 shift = int_2(x, y);
	processA.RunAllLays(shift);

	uint iter = 1 & uint(cfg_all->misc.curIteration++);
	processF.RunAllLays(shift, iter);
} // ///////////////////////////////////////////////////////////////////////////

