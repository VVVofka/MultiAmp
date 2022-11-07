#include "LayBase.h"
#include "Lay0.h"
#include "LayMid.h"
#include "Lays.h"

std::string LayBase::sDumpA(const int digits)const{
	std::string ret, sformat('%' + std::to_string(digits) + "d ");
	for(int y = 0; y < sz.y; y++){
		//int y = sz.y - yr - 1;
		for(int x = 0; x < sz.x; x++){
			int idx = id(x, y);
			int q = va.vcpu[idx];
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
} // ////////////////////////////////////////////////////////////////

std::string Lay0::sDumpA(const int digits)const{
	return "a: Lay0: x*y= " + std::to_string(sz.x) + '*' + std::to_string(sz.y) + '\n' + LayBase::sDumpA(digits);
} // ////////////////////////////////////////////////////////////////
std::string Lay0::DumpA(const int digits) const{
	std::string s(sDumpA(digits));
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
std::string LayMid::sDumpA(const int digits)const{
	return "a: " + sInfo() + '\n' + LayBase::sDumpA(digits);
} // ///////////////////////////////////////////////////////////////////////////////
std::string LayMid::sDumpF(const int digits)const{
	return "f: " + sInfo() + '\n' + sDumpvf(vf, digits);
} // ///////////////////////////////////////////////////////////////////////////////
std::string LayMid::sInfo() const{
	return "size x*y=" + std::to_string(sz.x) + '*' + std::to_string(sz.y) + ' ';
} // ///////////////////////////////////////////////////////////////////////////////

std::string Lays::sDumpA(int idx, const int digits)const{
	if(idx > cntMidLays)
		return "";
	if(idx == 0)
		return "a:Lay0: " + lay0.sDumpA(digits);
	if(idx > 0)
		return "a:Lay" + std::to_string(idx) + ": " + vMidLays[idx - 1]->sDumpA(digits);

	// if(idx < 0)
	std::string ret = "a:Lay0: " + lay0.sDumpA(digits);
	for(int jmid = 0; jmid < cntMidLays; jmid++)
		ret += "a:Lay" + std::to_string(jmid + 1) + ": " + vMidLays[jmid]->sDumpA(digits);
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
