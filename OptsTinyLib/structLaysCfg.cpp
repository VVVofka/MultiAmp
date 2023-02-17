#include "structLaysCfg.h"
#include "myconv.h"
size_t structLaysCfg::setConfig(size_t top_size, size_t one, size_t mt, const vector<float>* vkoef_in){
	topSize = top_size, cpuSingle = one, cpuMultiThreaded = mt;
	cntlays = vkoef_in->size() + 1u;
	koefsF.create(*vkoef_in);
	return cntlays;
} // /////////////////////////////////////////////////////////////////////////
size_t structLaysCfg::setConfig(size_t top_size, size_t one, size_t mt, const char* s_koefs, const char delimiter){
	topSize = top_size, cpuSingle = one, cpuMultiThreaded = mt;
	vector<float> v_parse = myconv::strToVFloat(s_koefs, delimiter);
	cntlays = v_parse.size() + 1u;
	koefsF.create(v_parse);
	return cntlays;
} // /////////////////////////////////////////////////////////////////////////
void structLaysCfg::resize(size_t new_cnt_lays){
	cntlays = new_cnt_lays;
	koefsF.resize(cntlays - 1);
} // ////////////////////////////////////////////////////////////////////////////////
