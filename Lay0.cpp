#include "Lay0.h"
#include "HDelete.h"
#include <random>
#include <list>
#include <algorithm>
#include <array>

namespace executor{
	//using namespace std;
	void Lay0::Create(
		const int_2 sz_0,
		const std::vector<int>& va_inp,			// xy.x * xy.y
		const vector<float_2>& vf_inp,		// (szx_0 * szy_0)
		const vector<float_2>& vv_inp,		// (szx_0 * szy_0)
		const float k_decAfterMove){
		sz = sz_0;
		kDecAfterMove = k_decAfterMove;
		countPoint = defPointsCnt(va_inp);
		va.Create(sz, va_inp, CPUtype::GPU);
		vf.Create(sz, vf_inp, CPUtype::GPU);
		vv.Create(sz, vv_inp, CPUtype::GPU);
		cpuPoint2gpuPoint(countPoint);
	} // ///////////////////////////////////////////////////////////////////////////////
	Lay0::~Lay0(){
		SAFE_DELETE(vgpuScreen);
	} // ///////////////////////////////////////////////////////////////////////////////
	int Lay0::SetRndScreenPoints(const int count, const int seed){
		std::mt19937 gen;        // to seed mersenne twister. rand: gen(rd())
		if(seed >= 0)
			gen.seed(seed);
		else{
			std::random_device rd;   // non-deterministic generator
			gen.seed(rd());
		}
		const int sz1 = sz.x * sz.y;
		std::vector<int> v(sz1);
		for(int j = 0; j < sz1; j++){
			v[j] = j;
			va.vcpu[j] = -1;
		}
		shuffle(v.begin(), v.end(), gen);
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
	string Lay0::sDumpA(const int digits)const{
		char buf[4096];
		sprintf_s(buf, "a: Lay0: x*y: %d*%d\n", sz.x, sz.y);
		string ret(buf);
		return ret + LayBase::sDumpA(digits);
	} // ////////////////////////////////////////////////////////////////
	string Lay0::sDumpF(const int digits)const{
		char buf[4096];
		sprintf_s(buf, "f: Lay0: x*y= %d*%d\n", sz.x, sz.y);
		string ret(buf);
		return ret + LayBase::sDumpF(digits);
	} // ////////////////////////////////////////////////////////////////	//int Lay0::va_at(const int x, const int y) const{
	string Lay0::sDumpV(const int digits)const{
		char buf[4096];
		sprintf_s(buf, "v: Lay0: x*y= %d*%d\n", sz.x, sz.y);
		string ret(buf);
		return ret + LayBase::sDumpV(digits);
	} // ////////////////////////////////////////////////////////////////	//int Lay0::va_at(const int x, const int y) const{
	string Lay0::DumpA(const int digits) const{
		string s(sDumpA(digits));
		_RPT0(0, s.c_str());
		return s;
	} // ////////////////////////////////////////////////////////////////
	string Lay0::DumpF(const int digits) const{
		string s(sDumpF(digits));
		_RPT0(0, s.c_str());
		return s;
	} // ////////////////////////////////////////////////////////////////
	string Lay0::DumpV(const int digits) const{
		string s(sDumpV(digits));
		_RPT0(0, s.c_str());
		return s;
	} // ////////////////////////////////////////////////////////////////
	//	int idx = vcpuIdx[y * (size_t)sz.x + x].i;
	//	return vcpuIdx[idx].i;
	//} // /////////////////////////////////////////////////////////////////////////////
	//float_2 Lay0::vf_at(const int x, const int y) const{
	//	int idx = vcpuIdx[y * (size_t)sz.x + x].i;
	//	return vcpuIdx[idx].f;
	//} // /////////////////////////////////////////////////////////////////////////////
	int Lay0::defPointsCnt(const std::vector<int>& v){
		int ret = 0;
		for(int j = 0; j < v.size(); j++) if(v[j] >= 0) ret++;
		return ret;
	} // /////////////////////////////////////////////////////////////////////////////
}