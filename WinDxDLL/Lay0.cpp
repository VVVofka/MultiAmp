#include "pch.h"
#include "Lay0.h"

void Lay0::Create(const int_2 sz_0, const std::vector<int>& va_inp, const std::vector<float_2>& vf_inp){
	sz = sz_0;
	countPoint = defPointsCnt(va_inp);
	va.Create(sz, va_inp, CPUtype::GPU);
	vf.Create(sz, vf_inp, CPUtype::GPU);
	cpuPoint2gpuPoint(countPoint);
} // /////////////////////////////////////////////////////////////////
Lay0::~Lay0(){
	SAFE_DELETE(vgpuScreen);
} // ///////////////////////////////////////////////////////////////////////////////
int Lay0::SetRndScreenPoints(const int count, std::mt19937& gen){
	const int sz1 = sz.x * sz.y;
	std::vector<int> v(sz1);
	for(int j = 0; j < sz1; j++){
		v[j] = j;
		va.vcpu[j] = -1;
	}
	std::shuffle(v.begin(), v.end(), gen);
	for(int j = 0; j < count; j++)
		va.vcpu[v[j]] = j;

	SAFE_DELETE(vgpuScreen);
	vgpuScreen = new concurrency::array<Vertex2D, 1>(count);
	return sz1;
} // ///////////////////////////////////////////////////////////////////////////////
void Lay0::SetScreenPoints(const int count, const int_2* ptr){
	SAFE_DELETE(vgpuScreen);
	vgpuScreen = new concurrency::array<Vertex2D, 1>(count);
} // ///////////////////////////////////////////////////////////////////////////////
void Lay0::cpuPoint2gpuPoint(const int count_point){
	_ASSERTE(count_point >= 0);
	int ret = 0;
	std::vector<Vertex2D> cpuv(count_point);
	for(int y = 0; y < sz.y; y++)
		for(int x = 0; x < sz.x; x++)
			if(va.vcpu[y * sz.x + x] >= 0){
				cpuv[ret].Pos.x = (float)(2 * x + 1) * sz.x - 1.f;
				cpuv[ret].Pos.y = (float)(2 * y + 1) * sz.y - 1.f;
				ret++;
			}
	_ASSERTE(ret == count_point);
	SAFE_DELETE(vgpuScreen);
	vgpuScreen = new concurrency::array<Vertex2D, 1>(ret, cpuv.begin());
} // ///////////////////////////////////////////////////////////////////////////////
bool Lay0::isLoad()const{
	if(sz.x <= 0) return false;
	if(sz.y <= 0) return false;
	if(va.vcpu.size() < 4) return false;
	if(va.vgpu == NULL) return false;
	if(vgpuScreen == NULL) return false;
	return true;
} // ///////////////////////////////////////////////////////////////////////////////
std::string Lay0::sDumpA(const int digits)const{
	return "a: Lay0: x*y= " + std::to_string(sz.x) + '*' + std::to_string(sz.y) + '\n' + LayBase::sDumpA(digits);
} // ////////////////////////////////////////////////////////////////
std::string Lay0::sDumpF(const int digits)const{
	return "f: Lay0: x*y= " + std::to_string(sz.x) + '*' + std::to_string(sz.y) + '\n' + LayBase::sDumpF(digits);
} // ////////////////////////////////////////////////////////////////	
std::string Lay0::DumpA(const int digits) const{
	std::string s(sDumpA(digits));
	_RPT0(0, s.c_str());
	return s;
} // ////////////////////////////////////////////////////////////////
std::string Lay0::DumpF(const int digits) const{
	std::string s(sDumpF(digits));
	_RPT0(0, s.c_str());
	return s;
} // ////////////////////////////////////////////////////////////////
int Lay0::defPointsCnt(const std::vector<int>& v){
	int ret = 0;
	for(int j = 0; j < (int)v.size(); j++) 
		if(v[j] >= 0) 
			ret++;
	return ret;
} // /////////////////////////////////////////////////////////////////////////////
