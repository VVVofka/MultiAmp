#include "LayBase.h"

void LayBase::Create(const int_2 xy, const bool is_gpu, accelerator_view& m_accl_view){
	sz = xy;
	va.Create(sz, is_gpu, m_accl_view);
} // ///////////////////////////////////////////////////////////////////////////////
void LayBase::Create(const int_2 xy, const std::vector<int>& va_inp, const bool is_gpu, accelerator_view& m_accl_view){
	sz = xy;
	va.Create(sz, va_inp, is_gpu, m_accl_view);
} // ///////////////////////////////////////////////////////////////////////////////
bool LayBase::isLoad() const{
	if(sz.x <= 0 || sz.y <= 0) return false;
	return va.vcpu.size() > 0;
} // ///////////////////////////////////////////////////////////////////////////////
std::string LayBase::sDumpA(const int digits)const{
	std::string ret, sformat("%" + std::to_string(digits) + "d ");
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
		ret += "\n";
	}
	return ret;
} // ////////////////////////////////////////////////////////////////
