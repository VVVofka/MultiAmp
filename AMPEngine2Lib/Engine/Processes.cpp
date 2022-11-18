#include "Processes.h"

//using namespace concurrency::graphics;
Processes::Processes(structAll* p_cfg_all, Lays* p_lays, accelerator_view* m_accl_view) :
	masks(p_cfg_all, m_accl_view),
	processA(p_lays, &masks.a),
	processF(p_lays, &masks.f),
	rnd(p_cfg_all->misc.curRndSeed){

	cfg_all = p_cfg_all;
	curIteration = p_cfg_all->misc.curIteration;
	rnd.setUpper(p_cfg_all->lays.bottomSquare());
} // ///////////////////////////////////////////////////////////////////////////
Processes::~Processes(){
	cfg_all->misc.curRndSeed = rnd.getSeed();
	cfg_all->misc.curIteration = curIteration;
} // ///////////////////////////////////////////////////////////////////////////
void Processes::RunAll(){
	auto pos = rnd.randk();	// max ~ 65500*65500
	size_t szx = cfg_all->lays.bottomX();
	int x = pos % szx;
	int y = pos / szx;
	int_2 shift = int_2(x, y);
	processA.RunAll(shift);
	processF.RunAll(shift);
	curIteration++;
} // ///////////////////////////////////////////////////////////////////////////

