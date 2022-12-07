#include "LayBase.h"
#include "Lay0.h"
#include "LayMid.h"
#include "Lays.h"

// static
std::string LayBase::sDumpV(const std::vector<int>& v, const uint_2 sz, const int digits){
	std::string ret, sformat("%-" + std::to_string(digits) + "d");

	std::string s0 = ".";
	for(int d = 0; d < digits - 1; d++)
		s0 += ' ';

	for(size_t yr = 0; yr < sz.y; yr++){
		_ASSERTE(sz.y >= yr + 1);
		size_t y = sz.y - yr - 1;
		for(size_t x = 0; x < sz.x; x++){
			size_t idx = y * sz.x + x;
			int q = v[idx];
			if(q < 0){
				ret += s0;
			} else{
				char buf[64];
				sprintf_s(buf, sformat.c_str(), q);
				ret += buf;
			}
		}
		ret += '\n';
	}
	return ret;
} // ////////////////////////////////////////////////////////////////////////////
// static
std::string LayBase::sDumpV(const std::vector<float_2>& v, const uint_2 sz, const int digits){
	std::string sdigit = std::to_string(digits);
	std::string ret, sformat("%+." + sdigit + "f*%+." + sdigit + "f ");
	for(size_t yr = 0; yr < sz.y; yr++){
		_ASSERTE(sz.y >= yr + 1);
		size_t y = sz.y - yr - 1;
		for(size_t x = 0; x < sz.x; x++){
			char buf[64];
			size_t idx = y * sz.x + x;
			float_2 cur = v[idx];
			sprintf_s(buf, sformat.c_str(), cur.x, cur.y);
			ret += buf;
		}
		ret += "\n";
	}
	return ret;
} // ////////////////////////////////////////////////////////////////////////////
std::string LayBase::sDumpV(const std::vector<float_2>& v, const int digits){
	std::string sdigit = std::to_string(digits);
	std::string ret, sformat("%+." + sdigit + "f*%+." + sdigit + "f ");
	for(size_t x = 0; x < v.size(); x++){
		char buf[64];
		float_2 cur = v[x];
		sprintf_s(buf, sformat.c_str(), cur.x, cur.y);
		ret += buf;
		if((x+1) % 10 == 0)
			ret += "\n";
	}
	ret += "\n";
	return ret;
} // ////////////////////////////////////////////////////////////////////////////
std::string LayBase::sDumpDbg(const int digits) const{
	std::vector<float_2> vtmp(sz.x * sz.y);
	concurrency::copy(*vgpuDbg, vtmp.begin());
	std::string ret = "dbg:\n" + sDumpV(vtmp, sz, digits);
	return ret;
} // /////////////////////////////////////////////////////////////////////////////

std::string Lay0::sDumpAcpu(const int digits)const{
	std::string sa = sDumpV(va.vcpu, sz, digits);
	return "a cpu: Lay0: x*y= " + std::to_string(sz.x) + '*' + std::to_string(sz.y) + '\n' + sa;
} // ////////////////////////////////////////////////////////////////
std::string Lay0::sDumpAgpu(const int digits)const{
	std::vector<int> vtmp(va.vcpu.size());
	va.gpu2other(vtmp);
	std::string sa = sDumpV(vtmp, sz, digits);
	return "a gpu: Lay0: x*y= " + std::to_string(sz.x) + '*' + std::to_string(sz.y) + '\n' + sa;
} // ////////////////////////////////////////////////////////////////
std::string Lay0::DumpAcpu(const int digits) const{
	std::string s(sDumpAcpu(digits));
	_RPT0(0, s.c_str());
	return s;
} // ////////////////////////////////////////////////////////////////
std::string Lay0::DumpAgpu(const int digits) const{
	std::string s(sDumpAgpu(digits));
	_RPT0(0, s.c_str());
	return s;
} // ////////////////////////////////////////////////////////////////
std::string Lay0::sDumpScreen(const int digits) const{
	std::vector<Vertex2D> vvert(countPoint);
	concurrency::copy(*vgpuScreen, vvert.begin());
	std::vector<float_2> vtmp(countPoint);
	for(int j = 0; j < countPoint; j++){
		vtmp[j].x = vvert[j].Pos.x;
		vtmp[j].y = vvert[j].Pos.y;
	}
	std::string ret = "screen[" + std::to_string(countPoint) + "]:\n" + LayBase::sDumpV(vtmp, digits);
	return ret;
} // ////////////////////////////////////////////////////////////////////
std::string LayMid::sDumpAcpu(const int digits)const{
	std::string sa = sDumpV(va.vcpu, sz, digits);
	return "a cpu: " + sInfo() + '\n' + sa;
} // ///////////////////////////////////////////////////////////////////////////////
std::string LayMid::sDumpAgpu(const int digits)const{
	std::vector<int> vtmp(va.vcpu.size());
	va.gpu2other(vtmp);
	std::string sa = sDumpV(vtmp, sz, digits);
	return "a gpu: " + sInfo() + '\n' + sa;
} // ///////////////////////////////////////////////////////////////////////////////
std::string LayMid::sDumpFcpu(const int digits) const{
	return "f cpu: " + sInfo() + '\n' + LayBase::sDumpV(vf.vcpu, sz, digits);
} // ///////////////////////////////////////////////////////////////////////////////////////////
std::string LayMid::sDumpFgpu(const int digits) const{
	std::vector<float_2> vtmp(vf.vcpu.size());
	vf.gpu2other(vtmp);
	return "f gpu: " + sInfo() + '\n' + LayBase::sDumpV(vtmp, sz, digits);
} // ///////////////////////////////////////////////////////////////////////////////////////////
std::string LayMid::sDumpF(const int digits) const{
	return sDumpFgpu(digits) + sDumpFcpu(digits);
} // ///////////////////////////////////////////////////////////////////////////////////////////
std::string LayMid::sInfo() const{
	return "size x*y=" + std::to_string(sz.x) + '*' + std::to_string(sz.y) + ' ';
} // ///////////////////////////////////////////////////////////////////////////////

std::string Lays::sDumpAcpu(int idx, const int digits)const{
	if(idx > cntMidLays)
		return "";
	if(idx == 0)
		return "a cpu:Lay0: " + lay0.sDumpAcpu(digits);
	if(idx > 0)
		return "a cpu:Lay" + std::to_string(idx) + ": " + vMidLays[idx - 1]->sDumpAcpu(digits);
	// idx < 0
	std::string ret = "a cpu:Lay0: " + lay0.sDumpAcpu(digits);
	for(int jmid = 0; jmid < cntMidLays; jmid++)
		ret += "a cpu:Lay" + std::to_string(jmid + 1) + ": " + vMidLays[jmid]->sDumpAcpu(digits);
	return ret;
} // /////////////////////////////////////////////////////////////////////////////
std::string Lays::sDumpAgpu(int idx, const int digits)const{
	if(idx > cntMidLays)
		return "";
	if(idx == 0)
		return "a gpu:Lay0: " + lay0.sDumpAgpu(digits);
	if(idx > 0)
		return "a gpu:Lay" + std::to_string(idx) + ": " + vMidLays[idx - 1]->sDumpAgpu(digits);
	// idx < 0
	std::string ret = "a gpu:Lay0: " + lay0.sDumpAgpu(digits);
	for(int jmid = 0; jmid < cntMidLays; jmid++)
		ret += "a gpu:Lay" + std::to_string(jmid + 1) + ": " + vMidLays[jmid]->sDumpAgpu(digits);
	return ret;
} // /////////////////////////////////////////////////////////////////////////////
std::string Lays::sDumpA(int idx, const int digits)const{
	if(idx > cntMidLays)
		return "";
	if(idx == 0){
		std::string sgpu = lay0.sDumpAgpu(digits);
		std::string scpu = lay0.sDumpAcpu(digits);
		return " Lay0 a gpu: " + sgpu + " Lay0 a cpu: " + scpu;
	}
	if(idx > 0){
		std::string sgpu = vMidLays[idx - 1]->sDumpAgpu(digits);
		std::string scpu = vMidLays[idx - 1]->sDumpAcpu(digits);
		return " Lay" + std::to_string(idx) + " a gpu: " + sgpu + " a cpu: " + scpu;
	}
	// idx < 0
	std::string ret = "a gpu:Lay0: " + lay0.sDumpAgpu(digits);
	ret += "a cpu:Lay0: " + lay0.sDumpAcpu(digits);
	for(int jmid = 0; jmid < cntMidLays; jmid++){
		ret += "a gpu:Lay" + std::to_string(jmid + 1) + ": " + vMidLays[jmid]->sDumpAgpu(digits);
		ret += "a cpu:Lay" + std::to_string(jmid + 1) + ": " + vMidLays[jmid]->sDumpAcpu(digits);
	}
	return ret;
} // /////////////////////////////////////////////////////////////////////////////

std::string Lays::sDumpFcpu(int idx, const int digits)const{
	if(idx > cntMidLays || idx == 0)
		return "";
	if(idx > 0)
		return "f cpu: Lay" + std::to_string(idx) + ": " + vMidLays[idx - 1]->sDumpFcpu(digits);

	// if(idx < 0)
	std::string ret;
	for(int jmid = 0; jmid < cntMidLays; jmid++)
		ret += "f cpu: Lay" + std::to_string(jmid + 1) + ": " + vMidLays[jmid]->sDumpFcpu(digits);
	return ret;
} // /////////////////////////////////////////////////////////////////////////////
std::string Lays::sDumpFgpu(int idx, const int digits)const{
	if(idx > cntMidLays || idx == 0)
		return "";
	if(idx > 0)
		return "f gpu: Lay" + std::to_string(idx) + ": " + vMidLays[idx - 1]->sDumpFgpu(digits);

	// if(idx < 0)
	std::string ret;
	for(int jmid = 0; jmid < cntMidLays; jmid++)
		ret += "f gpu: Lay" + std::to_string(jmid + 1) + ": " + vMidLays[jmid]->sDumpFgpu(digits);
	return ret;
} // /////////////////////////////////////////////////////////////////////////////
std::string Lays::sDumpF(int idx, const int digits)const{
	if(idx > cntMidLays || idx == 0)
		return "";

	if(idx > 0)
		return "Lay" + std::to_string(idx) +
		" f gpu: " + vMidLays[idx - 1]->sDumpFgpu(digits) +
		" f cpu: " + vMidLays[idx - 1]->sDumpFcpu(digits);

	// idx < 0
	std::string ret;
	for(int jmid = 0; jmid < cntMidLays; jmid++){
		ret += " f gpu Lay" + std::to_string(jmid + 1) + ": " + vMidLays[jmid]->sDumpFgpu(digits);
		ret += " f cpu Lay" + std::to_string(jmid + 1) + ": " + vMidLays[jmid]->sDumpFcpu(digits);
	}
	return ret;
} // /////////////////////////////////////////////////////////////////////////////

std::string Lays::DumpAcpu(int idx, const int digits)const{
	std::string s(sDumpAcpu(idx, digits));
	_RPT0(0, s.c_str());
	return s;
} // /////////////////////////////////////////////////////////////////////////////
std::string Lays::DumpAgpu(int idx, const int digits)const{
	std::string s(sDumpAgpu(idx, digits));
	_RPT0(0, s.c_str());
	return s;
} // /////////////////////////////////////////////////////////////////////////////
std::string Lays::DumpA(int idx, const int digits)const{
	std::string s(sDumpA(idx, digits));
	_RPT0(0, s.c_str());
	return s;
} // /////////////////////////////////////////////////////////////////////////////
std::string Lays::DumpFcpu(int idx, const int digits)const{
	std::string s(sDumpFcpu(idx, digits));
	_RPT0(0, s.c_str());
	return s;
} // /////////////////////////////////////////////////////////////////////////////
std::string Lays::DumpFgpu(int idx, const int digits)const{
	std::string s(sDumpFgpu(idx, digits));
	_RPT0(0, s.c_str());
	return s;
} // /////////////////////////////////////////////////////////////////////////////
std::string Lays::DumpF(int idx, const int digits)const{
	std::string s(sDumpF(idx, digits));
	_RPT0(0, s.c_str());
	return s;
} // /////////////////////////////////////////////////////////////////////////////
