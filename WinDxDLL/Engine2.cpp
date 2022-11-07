#include "Engine2.h"

Engine2::Engine2(ID3D11Device* d3ddevice, structAll* cfg_all) : 
		m_accl_view(Concurrency::direct3d::create_accelerator_view(d3ddevice)), lays(cfg_all, &m_accl_view)
		{
} // /////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT Engine2::get_data_d3dbuffer(void** d3dbuffer) const{
	return Concurrency::direct3d::get_buffer(*lays.lay0.vgpuScreen)->QueryInterface(__uuidof(ID3D11Buffer), (LPVOID*)d3dbuffer);
} // ///////////////////////////////////////////////////////////////////////////////////////////////
void Engine2::run(){
	////INT2 shift(distrLastAY(model.rnd_gen), distrLastAX(model.rnd_gen));   // rand shift
	//INT2 shift(model.myrnd.rand(model.sizeY()), model.myrnd.rand(model.sizeX()));   // rand shift
	////printf("\nshift = y:%d x:%d\n", shift.y, shift.x);	dumpA(nlastlay);
	//RunA::RunLast(shift, *vgpu_a[nlastlay], *vgpu_a[nlastlay - 1], *amask);
	//for(int nlay = (int)nlastlay - 1; nlay > 0; nlay--){
	//	//dumpA(nlay);
	//	RunA::Run(*vgpu_a[nlay], *vgpu_a[nlay - 1], *amask);
	//	//RunA::RunConst(*vgpu_a[nlay], *vgpu_a[nlay - 1], cmask);
	//}
	////dumpA(0);

	//// Back to down
	//for(size_t nlay = 1; nlay < nlastlay; nlay++){
	//	RunD::Run(*vgpu_f[nlay - 1], *vgpu_f[nlay], *vgpu_a[nlay], *ar_masks[nlay - 1]);
	//	//concurrency::copy(*ar_screen, vpos.data());
	//	//for(int n=0; n<(int)vpos.size(); n++) printf("%d\t%f\t%f\n", n, vpos[n].Pos.y, vpos[n].Pos.x);
	//}
	//RunDlast::Run(shift, *vgpu_f[nlastlay - 1], *ar_screen, *vgpu_a[nlastlay], *ar_last_dirs, model.sizeYX(), model.options.normDir());
} // ///////////////////////////////////////////////////////////////////////////////////////////////
