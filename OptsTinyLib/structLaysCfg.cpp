#include "structLaysCfg.h"
#include "myconv.h"
void structLaysCfg::setConfig(size_t top_x, size_t top_y, size_t cpu, size_t mt, size_t cnt_lays){
	if(cnt_lays > 0)
		cntlays = cnt_lays;
	topX = top_x, topY = top_y, cpuSingle = cpu, cpuMultiThreaded = mt;
	vector<float> v(cntlays - 1, 1.f);
	koefsF.create(v);
} // /////////////////////////////////////////////////////////////////////////
size_t structLaysCfg::setKoefsF(const vector<float>& vf_in){
	cntlays = vf_in.size() + 1;
	return koefsF.create(vf_in);
} // ////////////////////////////////////////////////////////////////////////////////
size_t structLaysCfg::setKoefsF(const char* s_in, const char delimiter){
	vector<float> v_parse = myconv::strToVFloat(s_in, delimiter);
	return setKoefsF(v_parse);
} // ////////////////////////////////////////////////////////////////////////////////
void structLaysCfg::resize(size_t new_cnt_lays){
	cntlays = new_cnt_lays;
	koefsF.resize(cntlays - 1);
} // ////////////////////////////////////////////////////////////////////////////////
