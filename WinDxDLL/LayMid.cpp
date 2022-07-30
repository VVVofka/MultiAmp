#include "pch.h"
#include "LayMid.h"

void LayMid::Create(const int_2 xy, const CPUtype cpu_type, const bool gpu_in){
	const bool is_gpu = gpu_in || cpu_type == CPUtype::GPU;
	LayBase::Create(xy, is_gpu);
	cpuType = cpu_type;
	gpuIn = gpu_in;
} // /////////////////////////////////////////////////////////////////////////////////
std::string LayMid::sDumpA(const int digits)const{
	char buf[256];
	sprintf_s(buf, "a: %s\n", sInfo().c_str());
	return std::string(buf) + LayBase::sDumpA(digits);
} // ///////////////////////////////////////////////////////////////////////////////
std::string LayMid::sDumpF(const int digits)const{
	char buf[256];
	sprintf_s(buf, "f: %s\n", sInfo().c_str());
	return std::string(buf) + LayBase::sDumpF(digits);
} // ///////////////////////////////////////////////////////////////////////////////
std::string LayMid::sInfo() const{
	char buf[256];
	sprintf_s(buf, "size x*y=%d*%d ", sz.x, sz.y);
	return std::string(buf);
} // ///////////////////////////////////////////////////////////////////////////////
