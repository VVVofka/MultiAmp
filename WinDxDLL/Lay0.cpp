#include "Lay0.h"
#include "Utils.h"

Lay0::Lay0(structAll* cfg_all, accelerator_view* m_accl_view) : LayBase(0, cfg_all, m_accl_view){
	countPoint = cfg_all->data.v.size();	// defPointsCnt(va_inp);
	cpuPoint2gpuPoint(countPoint);
} // ///////////////////////////////////////////////////////////////////////////////
Lay0::~Lay0(){
	SAFE_DELETE(vgpuScreen);
} // ///////////////////////////////////////////////////////////////////////////////
//concurrency::array<Vertex2D, 1>* Lay0::Create(const int_2 sz_0, const std::vector<int>& va_inp, accelerator_view& m_accl_view){
//}// ///////////////////////////////////////////////////////////////////////////////
//int Lay0::SetRndScreenPoints(const int count, std::mt19937& gen){
//	const int sz1 = sz.x * sz.y;
//	std::vector<int> v(sz1);
//	for(int j = 0; j < sz1; j++){
//		v[j] = j;
//		va.vcpu[j] = -1;
//	}
//	std::shuffle(v.begin(), v.end(), gen);
//	for(int j = 0; j < count; j++)
//		va.vcpu[v[j]] = j;
//
//	SAFE_DELETE(vgpuScreen);
//	vgpuScreen = new concurrency::array<Vertex2D, 1>(count);
//	return sz1;
//} // ///////////////////////////////////////////////////////////////////////////////
//void Lay0::SetScreenPoints(const int count, const int_2* ptr){
//	SAFE_DELETE(vgpuScreen);
//	vgpuScreen = new concurrency::array<Vertex2D, 1>(count);
//} // ///////////////////////////////////////////////////////////////////////////////
concurrency::array<Vertex2D, 1>* Lay0::cpuPoint2gpuPoint(const int count_point){
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
	return vgpuScreen;
} // ///////////////////////////////////////////////////////////////////////////////
bool Lay0::isLoad()const{
	if(sz.x <= 0) return false;
	if(sz.y <= 0) return false;
	if(va.vcpu.size() < 4) return false;
	if(va.vgpu == NULL) return false;
	if(vgpuScreen == NULL) return false;
	return true;
} // ///////////////////////////////////////////////////////////////////////////////
