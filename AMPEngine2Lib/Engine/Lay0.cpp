#include "Lay0.h"
#include "..\myUtil.h"
//#include "LaysCPUCfg.h"

Lay0::Lay0(structAll* cfg_all, accelerator_view* m_accl_view) : LayBase(0, cfg_all, m_accl_view){
	LayBase::cpuType = CPUtype::GPU;
	fill_va();
	fill_vf();
	fill_vmaskmove();
	fill_vScreen();
} // ///////////////////////////////////////////////////////////////////////////////
Lay0::~Lay0(){
	SAFE_DELETE(vgpuScreen);
	SAFE_DELETE(vgpuMaskMove);
} // ///////////////////////////////////////////////////////////////////////////////
//int Lay0::SetRndScreenPoints(const int count, std::mt19937& gen){
//	const int sz1 = sz.x * sz.y;
//	std::vector<int> vcpu(sz1);
//	for(int j = 0; j < sz1; j++){
//		vcpu[j] = j;
//		va.vcpu[j] = -1;
//	}
//	std::shuffle(vcpu.begin(), vcpu.end(), gen);
//	for(int j = 0; j < count; j++)
//		va.vcpu[vcpu[j]] = j;
//
//	SAFE_DELETE(vgpuScreen);
//	vgpuScreen = new concurrency::array<Vertex2D, 1>(count);
//	return sz1;
//} // ///////////////////////////////////////////////////////////////////////////////
//void Lay0::SetScreenPoints(const int count, const int_2* ptr){
//	SAFE_DELETE(vgpuScreen);
//	vgpuScreen = new concurrency::array<Vertex2D, 1>(count);
//} // ///////////////////////////////////////////////////////////////////////////////
concurrency::array<Vertex2D, 1>* Lay0::cpuPoint2gpuPoint(const uint count_point){
	_ASSERTE(count_point >= 0);
	int ret = 0;
	std::vector<Vertex2D> cpuv(count_point);
	for(size_t y = 0; y < sz; y++)
		for(size_t x = 0; x < sz; x++){
			size_t idx = y * sz + x;
			if(va.vcpu[idx] >= 0){
				cpuv[ret].Pos.x = (float)(2 * x + 1) * sz - 1.f;
				cpuv[ret].Pos.y = (float)(2 * y + 1) * sz - 1.f;
				ret++;
			}
		}
	_ASSERTE(ret == count_point);
	SAFE_DELETE(vgpuScreen);
	vgpuScreen = new concurrency::array<Vertex2D, 1>(ret, cpuv.begin());
	return vgpuScreen;
} // ///////////////////////////////////////////////////////////////////////////////
bool Lay0::isLoad()const{
	if(sz <= 0) return false;
	if(va.vcpu.size() < 4) return false;
	if(va.vgpu == NULL) return false;
	if(vgpuScreen == NULL) return false;
	return true;
} // ///////////////////////////////////////////////////////////////////////////////
void Lay0::fill_vScreen(){
	countPoint = (int)cfg_all->data.v.size();	// defPointsCnt(va_inp);
	vcpuScreen.resize(countPoint);
	size_t szBottom = cfg_all->lays.sizeBottom();
	for(int j = 0; j < countPoint; j++){
		const size_t idx = cfg_all->data.v[j];

		const size_t ux = idx % szBottom;
		const float x = NORMAL_TO_AREA(ux, szBottom);

		const size_t uy = idx / szBottom;
		const float y = NORMAL_TO_AREA(uy, szBottom);

		vcpuScreen[j] = Vertex2D(y, x);
	}
	SAFE_DELETE(vgpuScreen);
	vgpuScreen = new concurrency::array<Vertex2D, 1>(countPoint, vcpuScreen.begin(), *m_accl_view);
} // ///////////////////////////////////////////////////////////////////////////////
void Lay0::fill_va(){
	countPoint = cfg_all->data.v.size();
	std::vector<int> vtmp(sz * sz, -1);
	for(int j = 0; j < countPoint; j++){
		const size_t idx = cfg_all->data.v[j];
		vtmp[idx] = j;
	}
	va.Create(sz, vtmp, true, m_accl_view);
} // ///////////////////////////////////////////////////////////////////////////////
void Lay0::fill_vf(){
	std::vector<float_2> vtmp(sz * sz, float_2(0.f, 0.f));
	vf.Create(sz, vtmp, true, m_accl_view);
} // ///////////////////////////////////////////////////////////////////////////////
void Lay0::fill_vmaskmove(){
	std::vector<uint> vtmp = {
		 0,20, 0, 0,25,40,25,25, 0,20, 0, 0,17, 0,17, 0,  30,60,30,30,45,60,45,45,30,30,30,30,30,30, 0,30,
		 0,20, 0, 0,25,40,25,25, 0,20, 0, 0,17, 0,17, 0,  22,20,22,22, 0, 0, 0, 0,22,22,22,22,34, 0,34, 0,
		 0,20, 0, 0,25,40,25,25, 0,20, 0, 0,17, 0,17, 0,   0,20, 0, 0, 0, 0, 0, 0, 0,20, 0, 0,17, 0,17, 0,
		 0,20, 0, 0,25,40,25,25, 0,20, 0, 0,17, 0,17, 0,  22,20,22,22, 0, 0, 0, 0,22,22,22,22,34, 0,34, 0,

		 0,20, 0, 0,25,40,25,25, 0,20, 0, 0,17, 0,17, 0,  30,20,30,30,45,60,45,45,30,20,30,30, 0,30,17,30,
		 0,20, 0, 0,25,40,25,25, 0,20, 0, 0,17, 0,17, 0,  22,20,22,22, 0, 0, 0, 0,22,22,22,22,34, 0,34, 0,
		27,20,27,27,25,40,25,25,27, 0,27,27,27,27,17,27,   0,20, 0, 0, 0, 0, 0, 0, 0,20, 0, 0,17, 0,17, 0,
		27, 0,27,27,27,27,27,27,27,27,27,27,27,27,51,27,  39,20,39,39, 0, 0, 0, 0,39,39,39,39,51, 0,51, 0
	};
	SAFE_DELETE(vgpuMaskMove);
	vgpuMaskMove = new concurrency::array<uint, 1>(vtmp.size(), vtmp.begin(), *m_accl_view);
} // ///////////////////////////////////////////////////////////////////////////////
