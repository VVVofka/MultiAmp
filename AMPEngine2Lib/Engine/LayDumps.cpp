#include "LayBase.h"
#include "Lay0.h"
#include "LayMid.h"
#include "Lays.h"
std::string LayBase::sDumpV(const std::vector<int>& v, const int_2 sz, const int digits){
	std::string ret, sformat('%' + std::to_string(digits) + "d ");
	for(int yr = 0; yr < sz.y; yr++){
		int y = sz.y - yr - 1;
		for(int x = 0; x < sz.x; x++){
			int idx = y * sz.x + x;
			int q = v[idx];
			if(q < 0){
				ret += " . ";
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
std::string LayBase::sDumpAcpu(const int digits)const{
	return LayBase::sDumpV(va.vcpu, sz, digits);
} // ////////////////////////////////////////////////////////////////
std::string LayBase::sDumpAgpu(const int digits)const{
	std::vector<int> vtmp(va.vcpu.size());
	gpu2other(vtmp);
	return LayBase::sDumpV(vtmp, sz, digits);
} // ////////////////////////////////////////////////////////////////

std::string Lay0::sDumpAcpu(const int digits)const{
	return "a cpu: Lay0: x*y= " + std::to_string(sz.x) + '*' + std::to_string(sz.y) + '\n' + LayBase::sDumpAcpu(digits);
} // ////////////////////////////////////////////////////////////////
std::string Lay0::sDumpAgpu(const int digits)const{
	return "a gpu: Lay0: x*y= " + std::to_string(sz.x) + '*' + std::to_string(sz.y) + '\n' + LayBase::sDumpAgpu(digits);
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

std::string LayMid::sDumpvf(const VGpuCpu<float_2>& v, const int digits)const{
	std::string ret, sformat("%+." + std::to_string(digits) + "f ");
	for(int y = 0; y < sz.y; y++){
		char buf[64];
		//int y = sz.y - yr - 1;
		for(int x = 0; x < sz.x; x++){
			int idx = id(x, y);
			float_2 cur = v.vcpu[idx];
			sprintf_s(buf, sformat.c_str(), cur.x);
			ret += buf;
		}
		ret += "\n";
		for(int x = 0; x < sz.x; x++){
			int idx = id(x, y);
			float_2 cur = v.vcpu[idx];
			sprintf_s(buf, sformat.c_str(), cur.y);
			ret += buf;
		}
		ret += "\n\n";
	}
	return ret;
} // ////////////////////////////////////////////////////////////////
std::string LayMid::sDumpAcpu(const int digits)const{
	return "a cpu: " + sInfo() + '\n' + LayBase::sDumpAcpu(digits);
} // ///////////////////////////////////////////////////////////////////////////////
std::string LayMid::sDumpAgpu(const int digits)const{
	return "a gpu: " + sInfo() + '\n' + LayBase::sDumpAgpu(digits);
} // ///////////////////////////////////////////////////////////////////////////////
std::string LayMid::sDumpF(const int digits)const{
	return "f: " + sInfo() + '\n' + sDumpvf(vf, digits);
} // ///////////////////////////////////////////////////////////////////////////////
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
	if(idx == 0)
		return "Lay0 a gpu: " + lay0.sDumpAgpu(digits) + "Lay0 a cpu: " + lay0.sDumpAcpu(digits);
	if(idx > 0)
		return "Lay" + std::to_string(idx) + " a gpu: " + vMidLays[idx - 1]->sDumpAgpu(digits) + "a cpu: " + vMidLays[idx - 1]->sDumpAcpu(digits);
	// idx < 0
	std::string ret = "a gpu:Lay0: " + lay0.sDumpAgpu(digits);
	ret += "a cpu:Lay0: " + lay0.sDumpAcpu(digits);
	for(int jmid = 0; jmid < cntMidLays; jmid++){
		ret += "a gpu:Lay" + std::to_string(jmid + 1) + ": " + vMidLays[jmid]->sDumpAgpu(digits);
		ret += "a cpu:Lay" + std::to_string(jmid + 1) + ": " + vMidLays[jmid]->sDumpAcpu(digits);
	}
	return ret;
} // /////////////////////////////////////////////////////////////////////////////

std::string Lays::sDumpF(int idx, const int digits)const{
	if(idx > cntMidLays || idx == 0)
		return "";
	if(idx > 0)
		return "f:Lay" + std::to_string(idx) + ": " + vMidLays[idx - 1]->sDumpF(digits);

	// if(idx < 0)
	std::string ret;
	for(int jmid = 0; jmid < cntMidLays; jmid++)
		ret += "f:Lay" + std::to_string(jmid + 1) + ": " + vMidLays[jmid]->sDumpF(digits);
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
std::string Lays::DumpF(int idx, const int digits)const{
	std::string s(sDumpF(idx, digits));
	_RPT0(0, s.c_str());
	return s;
} // /////////////////////////////////////////////////////////////////////////////
