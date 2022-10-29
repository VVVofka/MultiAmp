#include "MLay0.h"
#include "Utils.h"
void MLay0::Create(const int_2 sz_0, const std::vector<int>& va_inp, const std::vector<float_2>& vf_inp, concurrency::array<Vertex2D, 1>* vgpu_Screen){
	sz = sz_0;
	countPoint = defPointsCnt(va_inp);
	va.Create(sz, va_inp, MCPUtype::GPU);
	vf.Create(sz, vf_inp, MCPUtype::GPU);
	cpuPoint2gpuPoint(countPoint);
	vgpuScreen = vgpu_Screen;
} // /////////////////////////////////////////////////////////////////
MLay0::~MLay0(){
	SAFE_DELETE(vgpuScreen);
} // ///////////////////////////////////////////////////////////////////////////////

void MLay0::SetScreenPoints(const int count, const int_2* ptr){
	SAFE_DELETE(vgpuScreen);
	vgpuScreen = new concurrency::array<Vertex2D, 1>(count);
} // ///////////////////////////////////////////////////////////////////////////////
void MLay0::cpuPoint2gpuPoint(const int count_point){
	_ASSERTE(count_point >= 0);
	int ret = 0;
	std::vector<Vertex2D> cpuv(count_point);
	for(int y = 0; y < sz.y; y++)
		for(int x = 0; x < sz.x; x++)
			if(va.vcpu[y * sz.x + x] >= 0){
				cpuv[ret].Pos.y = NORMAL_TO_AREA(y, sz.y);	//cpuv[ret].Pos.y = (float)(2 * y + 1) * sz.y - 1.f;
				cpuv[ret].Pos.x = NORMAL_TO_AREA(x, sz.x);	//cpuv[ret].Pos.x = (float)(2 * x + 1) * sz.x - 1.f;
				ret++;
			}
	_ASSERTE(ret == count_point);
	SAFE_DELETE(vgpuScreen);
	vgpuScreen = new concurrency::array<Vertex2D, 1>(ret, cpuv.begin());
} // ///////////////////////////////////////////////////////////////////////////////
bool MLay0::isLoad()const{
	if(sz.x <= 0) return false;
	if(sz.y <= 0) return false;
	if(va.vcpu.size() < 4) return false;
	if(va.vgpu == NULL) return false;
	if(vgpuScreen == NULL) return false;
	return true;
} // ///////////////////////////////////////////////////////////////////////////////
std::string MLay0::sDumpA(const int digits)const{
	std::string ret("a: MLay0: x*y: " + std::to_string(sz.x) + '*' + std::to_string(sz.y) + '\n');
	return ret + MLayBase::sDumpA(digits);
} // ////////////////////////////////////////////////////////////////
std::string MLay0::sDumpF(const int digits)const{
	std::string ret("f: MLay0: x*y: " + std::to_string(sz.x) + '*' + std::to_string(sz.y) + '\n');
	return ret + MLayBase::sDumpF(digits);
} // ////////////////////////////////////////////////////////////////	
std::string MLay0::DumpA(const int digits) const{
	std::string s(sDumpA(digits));
	_RPT0(0, s.c_str());
	return s;
} // ////////////////////////////////////////////////////////////////
std::string MLay0::DumpF(const int digits) const{
	std::string s(sDumpF(digits));
	_RPT0(0, s.c_str());
	return s;
} // ////////////////////////////////////////////////////////////////
int MLay0::defPointsCnt(const std::vector<int>& v){
	int ret = 0;
	for(int j = 0; j < (int)v.size(); j++)
		if(v[j] >= 0)
			ret++;
	return ret;
} // /////////////////////////////////////////////////////////////////////////////
