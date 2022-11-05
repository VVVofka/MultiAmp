#include "Lays.h"
Lays::Lays(accelerator_view& m_accl_view){
	this->m_accl_view = &m_accl_view;
} // ////////////////////////////////////////////////////////////////////////////////
concurrency::array<Vertex2D, 1>* Lays::Create(
	const int_2 sz_lay0,				// size lay0
	const LaysCPUCfg& cfg,				// count gpu mt cpu
	const std::vector<int>& va_inp		// szx_0 * szy_0
	){
	auto ret = lay0.Create(sz_lay0, va_inp, *m_accl_view);
	if(lay0.isLoad() == false) return NULL;
	int_2 sz_lay1 = sz_lay0 / 2;
	cntMidLays = (int)fillvMidLays(sz_lay1, cfg);
	if(isLoad() == false) return NULL;
	return ret;
} // //////////////////////////////////////////////////////////////////////////
bool Lays::isLoad(){
	if(lay0.isLoad() == false) return false;
	if(vMidLays.size() < 1) return false;
	_ASSERTE(vMidLays.size() == cntMidLays);
	for(int j = 0; j < cntMidLays; j++)
		if(vMidLays[j].isLoad() == false)
			return false;
	return true;
} // //////////////////////////////////////////////////////////////////////////
int Lays::fillvMidLays(const int_2 sz_1, const LaysCPUCfg cfgcpu){
	const int cnt_lays = cfgcpu.cnt();
	_ASSERTE(cnt_lays > 1);
	const int cnt_mid_lays = cfgcpu.cntmid();
	if(cnt_mid_lays < 1)
		return -1;
	vMidLays.resize(cnt_mid_lays);

	int_2 sz_cur = sz_1;
	CPUtype prevtype = CPUtype::GPU;
	for(int j = 0; j < cnt_mid_lays; j++){
		const CPUtype curtype = cfgcpu.getType(j + 1);
		const bool gpu_in = prevtype == CPUtype::GPU && curtype != CPUtype::GPU;
		vMidLays[j].Create(sz_cur, curtype, gpu_in, *m_accl_view);
		sz_cur /= 2;
		prevtype = curtype;
	}
	return cnt_mid_lays;
} // /////////////////////////////////////////////////////////////////////////////
std::string Lays::sDumpA(int idx, const int digits)const{
	if(idx > cntMidLays)
		return "";
	if(idx == 0)
		return "a:Lay0: " + lay0.sDumpA(digits);
	if(idx > 0)
		return "a:Lay" + std::to_string(idx) + ": " + vMidLays[idx - 1].sDumpA(digits);

	// if(idx < 0)
	std::string ret = "a:Lay0: " + lay0.sDumpA(digits);
	for(int jmid = 0; jmid < cntMidLays; jmid++)
		ret += "a:Lay" + std::to_string(jmid + 1) + ": " + vMidLays[jmid].sDumpA(digits);
	return ret;
} // /////////////////////////////////////////////////////////////////////////////
std::string Lays::sDumpF(int idx, const int digits)const{
	if(idx > cntMidLays || idx == 0)
		return "";
	if(idx > 0)
		return "f:Lay" + std::to_string(idx) + ": " + vMidLays[idx - 1].sDumpF(digits);

	// if(idx < 0)
	std::string ret;
	for(int jmid = 0; jmid < cntMidLays; jmid++)
		ret += "f:Lay" + std::to_string(jmid + 1) + ": " + vMidLays[jmid].sDumpF(digits);
	return ret;
} // /////////////////////////////////////////////////////////////////////////////

std::string Lays::DumpA(int idx, const int digits)const{
	std::string s(sDumpA(idx, digits));
	_RPT0(0, s.c_str());
	return s;
} // /////////////////////////////////////////////////////////////////////////////
std::string Lays::DumpF(int idx, const int digits)const{
	std::string s(sDumpF(idx, digits));
	_RPT0(0, s.c_str());
	return s;
} // /////////////////////////////////////////////////////////////////////////////
