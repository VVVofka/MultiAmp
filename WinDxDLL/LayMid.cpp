#include "pch.h"
#include "LayMid.h"

void LayMid::Create(const int_2 xy, const CPUtype cpu_type, const bool gpu_in){
	const bool is_gpu = gpu_in || cpu_type == CPUtype::GPU;
	LayBase::Create(xy, is_gpu);
	cpuType = cpu_type;
	gpuIn = gpu_in;
} // /////////////////////////////////////////////////////////////////////////////////
void LayMid::gpu2cpu(){
	LayBase::gpu2cpu();
	vf.gpu2cpu();
} // /////////////////////////////////////////////////////////////////////////////////
void LayMid::cpu2gpu(){
	LayBase::cpu2gpu();
	vf.cpu2gpu();
} // /////////////////////////////////////////////////////////////////////////////////
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
