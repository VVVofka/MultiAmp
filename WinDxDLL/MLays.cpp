#include "MLays.h"
bool MLays::Create(
	const int_2 sz_lay0,				// size x lay0
	const MLaysCPUCfg cfg,				// count gpu mt cpu
	const std::vector<int>& va_inp,			// szx_0 * szy_0
	const std::vector<float_2>& vf_inp,		// szx_0 * szy_0
	const float k_decAfterMove){
	lay0.Create(sz_lay0, va_inp, vf_inp, k_decAfterMove);
	if(lay0.isLoad() == false) return false;
	int_2 sz_lay1 = sz_lay0 / 2;
	cntMidMLays = (int)fillvMidLays(sz_lay1, cfg);
	return isLoad();
} // //////////////////////////////////////////////////////////////////////////
bool MLays::isLoad(){
	if(lay0.isLoad() == false) return false;
	if(vMidLays.size() < 1) return false;
	_ASSERTE(vMidLays.size() == cntMidMLays);
	for(int j = 0; j < cntMidMLays; j++)
		if(vMidLays[j].isLoad() == false)
			return false;
	return true;
} // //////////////////////////////////////////////////////////////////////////
int MLays::fillvMidLays(const int_2 sz_1, const MLaysCPUCfg cfgcpu){
	const int cnt_lays = cfgcpu.cnt();
	_ASSERTE(cnt_lays > 1);
	const int cnt_mid_lays = cfgcpu.cntmid();
	if(cnt_mid_lays < 1)
		return -1;
	vMidLays.resize(cnt_mid_lays);

	int_2 sz_cur = sz_1;
	MCPUtype prevtype = MCPUtype::GPU;
	for(int j = 0; j < cnt_mid_lays; j++){
		const MCPUtype curtype = cfgcpu.getType(j + 1);
		const bool gpu_in = prevtype == MCPUtype::GPU && curtype != MCPUtype::GPU;
		vMidLays[j].Create(sz_cur, curtype, gpu_in);
		sz_cur /= 2;
		prevtype = curtype;
	}
	return cnt_mid_lays;
} // /////////////////////////////////////////////////////////////////////////////
std::string MLays::sDumpA(const int idx, const int digits)const{
	if(idx > cntMidMLays)
		return "";
	if(idx == 0)
		return "a:Lay0: " + lay0.sDumpA(digits);
	if(idx > 0)
		return "a:Lay" + std::to_string(idx) + ": " + vMidLays[idx - 1].sDumpA(digits);

	// if(idx < 0)
	std::string ret = "a:Lay0: " + lay0.sDumpA(digits);
	for(int jmid = 0; jmid < cntMidMLays; jmid++)
		ret += "a:Lay" + std::to_string(jmid + 1) + ": " + vMidLays[jmid].sDumpA(digits);
	return ret;
} // /////////////////////////////////////////////////////////////////////////////
std::string MLays::sDumpF(const int idx, const int digits)const{
	if(idx > cntMidMLays)
		return "";
	if(idx == 0)
		return "f:Lay0: " + lay0.sDumpF(digits);
	if(idx > 0)
		return "f:Lay" + std::to_string(idx) + ": " + vMidLays[idx - 1].sDumpF(digits);

	// if(idx < 0)
	std::string ret = "f:Lay0: " + lay0.sDumpF(digits);
	for(int jmid = 0; jmid < cntMidMLays; jmid++)
		ret += "f:Lay" + std::to_string(jmid + 1) + ": " + vMidLays[jmid].sDumpF(digits);
	return ret;
} // /////////////////////////////////////////////////////////////////////////////

std::string MLays::DumpA(const int idx, const int digits)const{
	std::string s(sDumpA(idx, digits));
	_RPT0(0, s.c_str());
	return s;
} // /////////////////////////////////////////////////////////////////////////////
std::string MLays::DumpF(const int idx, const int digits)const{
	std::string s(sDumpF(idx, digits));
	_RPT0(0, s.c_str());
	return s;
} // /////////////////////////////////////////////////////////////////////////////
