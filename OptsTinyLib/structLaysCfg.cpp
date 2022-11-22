#include "structLaysCfg.h"
#include "myconv.h"
size_t structLaysCfg::setConfig(size_t top_x, size_t top_y, size_t one, size_t mt, const vector<float>* vkoef_in){
	topX = top_x, topY = top_y, cpuSingle = one, cpuMultiThreaded = mt;
	cntlays = vkoef_in->size() + 1u;
	koefsF.create(*vkoef_in);
	return cntlays;
} // /////////////////////////////////////////////////////////////////////////
size_t structLaysCfg::setConfig(size_t top_x, size_t top_y, size_t one, size_t mt, const char* s_koefs, const char delimiter){
	topX = top_x, topY = top_y, cpuSingle = one, cpuMultiThreaded = mt;
	vector<float> v_parse = myconv::strToVFloat(s_koefs, delimiter);
	cntlays = v_parse.size() + 1u;
	koefsF.create(v_parse);
	return cntlays;
} // /////////////////////////////////////////////////////////////////////////
//size_t structLaysCfg::setKoefsF(const vector<float>& vf_in){
//	cntlays = vf_in.size() + 1;
//	return koefsF.create(vf_in);
//} // ////////////////////////////////////////////////////////////////////////////////
//size_t structLaysCfg::setKoefsF(const char* s_in, const char delimiter){
//	vector<float> v_parse = myconv::strToVFloat(s_in, delimiter);
//	return setKoefsF(v_parse);
//} // ////////////////////////////////////////////////////////////////////////////////
void structLaysCfg::resize(size_t new_cnt_lays){
	cntlays = new_cnt_lays;
	koefsF.resize(cntlays - 1);
} // ////////////////////////////////////////////////////////////////////////////////
