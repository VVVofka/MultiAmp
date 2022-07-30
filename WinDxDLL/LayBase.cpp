#include "pch.h"
#include "LayBase.h"

void LayBase::Create(const int_2 xy, const bool is_gpu){
	sz = xy;
	va.Create(sz, is_gpu);
	vf.Create(sz, is_gpu);
} // ////////////////////////////////////////////////////////////
void LayBase::gpu2cpu(){
	va.gpu2cpu();
	vf.gpu2cpu();
} // ///////////////////////////////////////////////////////////////////////////////
void LayBase::cpu2gpu(){
	va.cpu2gpu();
	vf.cpu2gpu();
} // ///////////////////////////////////////////////////////////////////////////////
bool LayBase::isLoad() const{
	if(sz.x <= 0) return false;
	if(sz.y <= 0) return false;
	if(va.vcpu.size() == 0) return false;
	if(vf.vcpu.size() == 0) return false;
	return true;
} // ///////////////////////////////////////////////////////////////////////////////
std::string LayBase::sDumpA(const int digits)const{
	char buf[4096];
	std::string ret, sformat("%" + std::to_string(digits) + "d ");
	for(int y = 0; y < sz.y; y++){
		//int y = sz.y - yr - 1;
		for(int x = 0; x < sz.x; x++){
			int idx = id(x, y);
			int q = va.vcpu[idx];
			if(q < 0){
				ret += " . ";
			} else{
				sprintf_s(buf, sformat.c_str(), q);
				ret += buf;
			}
		}
		ret += "\n";
	}
	return ret;
} // ////////////////////////////////////////////////////////////////
std::string LayBase::sDump(const VGpuCpu<float_2>& v, const int digits)const{
	char buf[4096];
	std::string ret, sformat("%+." + std::to_string(digits) + "f ");
	for(int y = 0; y < sz.y; y++){
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
std::string LayBase::sDumpF(const int digits)const{
	return sDump(vf, digits);
} // ////////////////////////////////////////////////////////////////
