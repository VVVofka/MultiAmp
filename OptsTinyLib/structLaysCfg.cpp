#include "structLaysCfg.h"

void structLaysCfg::setConfig(size_t top_x, size_t top_y, size_t cnt_lays, size_t cpu = 0, size_t mt = 0){
	cntlays = cnt_lays, topX = top_x, topY = top_y, cpuSingle = cpu, cpuMultiThreaded = mt;
	vkf.clear(), vkf.resize(cntlays - 1);
	for(size_t j = 0; j < cntlays; j++)
		vkf[j] = 1;
} // /////////////////////////////////////////////////////////////////////////
void structLaysCfg::resize(size_t new_size){
	cntlays = new_size;
	vkf.clear(), vkf.resize(cntlays - 1);
	for(size_t j = 0; j < cntlays; j++)
		vkf[j] = 1;

} // ////////////////////////////////////////////////////////////////////////////////