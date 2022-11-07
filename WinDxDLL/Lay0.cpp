#include "Lay0.h"
#include "Utils.h"

Lay0::Lay0(structAll* cfg_all, accelerator_view* m_accl_view) : LayBase(0, cfg_all, m_accl_view){
	//cpuPoint2gpuPoint(countPoint);
	LayBase::cpuType = CPUtype::GPU;
	LayBase::gpuIn = false;

	fill_vScreen();
	fill_va();
} // ///////////////////////////////////////////////////////////////////////////////
Lay0::~Lay0(){
	SAFE_DELETE(vgpuScreen);
} // ///////////////////////////////////////////////////////////////////////////////
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
	if(sz.x <= 0 || sz.y <= 0) return false;
	if(va.vcpu.size() < 4) return false;
	if(va.vgpu == NULL) return false;
	if(vgpuScreen == NULL) return false;
	return true;
} // ///////////////////////////////////////////////////////////////////////////////
void Lay0::fill_vScreen(){
	countPoint = cfg_all->data.v.size();	// defPointsCnt(va_inp);
	vcpuScreen.resize(countPoint);
	size_t szx = cfg_all->lays.bottomX();
	size_t szy = cfg_all->lays.bottomY();
	for(int j = 0; j < countPoint; j++){
		const size_t idx = cfg_all->data.v[j];

		const size_t ux = idx % szx;
		const float x = NORMAL_TO_AREA(ux, szx);
		
		const size_t uy = idx / szx;
		const float y = NORMAL_TO_AREA(uy, szy);
		
		vcpuScreen[j] = Vertex2D(y, x);
	}
	SAFE_DELETE(vgpuScreen);
	vgpuScreen = new concurrency::array<Vertex2D, 1>(countPoint, vcpuScreen.begin(), *m_accl_view);
} // ///////////////////////////////////////////////////////////////////////////////
void Lay0::fill_va(){
	std::vector<int> vtmp(sz.x * sz.y, -1);
	size_t szx = cfg_all->lays.bottomX();
	size_t szy = cfg_all->lays.bottomY();
	for(int j = 0; j < countPoint; j++){
		const size_t idx = cfg_all->data.v[j];
		vtmp[idx] = j;
	}
	LayBase::va.Create(sz, vtmp, true, m_accl_view);
} // ///////////////////////////////////////////////////////////////////////////////

