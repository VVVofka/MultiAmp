#include "MLayMid.h"

void MLayMid::Create(const int_2 xy, const MCPUtype cpu_type, const bool gpu_in){
	const bool is_gpu = gpu_in || cpu_type == MCPUtype::GPU;
	MLayBase::Create(xy, is_gpu);
	cpuType = cpu_type;
	gpuIn = gpu_in;
} // /////////////////////////////////////////////////////////////////////////////////
std::string MLayMid::sDumpA(const int digits)const{
	return  "a: " + sInfo() + "\n" + MLayBase::sDumpA(digits);
} // ///////////////////////////////////////////////////////////////////////////////
std::string MLayMid::sDumpF(const int digits)const{
	return "f: " + sInfo() + "\n" + MLayBase::sDumpF(digits);
} // ///////////////////////////////////////////////////////////////////////////////
std::string MLayMid::sInfo() const{
	return "size x*y=" + std::to_string(sz.x) + '*' + std::to_string(sz.y) + ' ';
} // ///////////////////////////////////////////////////////////////////////////////
