#include "pch.h"
#include "AMPEng2.h"

AMPEng2::AMPEng2(ID3D11Device* d3ddevice) : m_accl_view(Concurrency::direct3d::create_accelerator_view(d3ddevice)){
	distrLastAY = std::uniform_int_distribution<int>(0, model.sizeY() - 1);
	distrLastAX = std::uniform_int_distribution<int>(0, model.sizeX() - 1);
	nlastlay = size_t(model.LaysCnt() - 1); // N last lay

	int layscnt = (int)model.v_areas.size();
	_ASSERTE(layscnt == nlastlay + 1);
	for(int nlay = 0; nlay < layscnt; nlay++){
		const INT2 size = model.sizeYX(nlay);

		vgpu_a.push_back(std::unique_ptr<array<int, 2>>());
		auto pareas = new array<int, 2>(size.y, size.x, model.v_areas[nlay].begin(), m_accl_view);
		vgpu_a[nlay] = std::unique_ptr<array<int, 2>>(pareas);

		if(nlay < layscnt - 1){
			auto tmp = new array<DrQuadro, 2>(size.y, size.x, model.v_dirs[nlay].begin(), m_accl_view);
			vgpu_f.push_back(std::unique_ptr<array<DrQuadro, 2>>(tmp));
		}
		if(nlay < layscnt - 2){
			FLT2 tmp[Options::szDirs];
			float k = (float)model.options.kLays(nlay);
			for(int j = 0; j < _countof(tmp); j++){
				tmp[j].y = model.options.blocks2D2.vin[j].y * k;
				tmp[j].x = model.options.blocks2D2.vin[j].x * k;
			}
			auto v = new array<FLT2, 1>(Options::szDirs, tmp, m_accl_view);
			ar_masks.push_back(std::unique_ptr<array<FLT2, 1>>(v));
		}
	}
	auto pscreen = new array<Vertex2D, 1>(int(model.v_scr.size()), model.v_scr.begin(), m_accl_view);
	ar_screen = std::unique_ptr<array<Vertex2D, 1>>(pscreen);

	auto plast_dirs = new array<FLT2, 2>(model.sizeY(), model.sizeX(), model.ar_last_dirs.begin(), m_accl_view);
	ar_last_dirs = std::unique_ptr<array<FLT2, 2>>(plast_dirs);

	auto pamsk = new array<int, 1>(16, model.options.aMask(), m_accl_view);
	amask = std::unique_ptr<array<int, 1>>(pamsk);


} // ///////////////////////////////////////////////////////////////////////////////////////////////
void AMPEng2::run(){
	//INT2 shift(distrLastAY(model.rnd_gen), distrLastAX(model.rnd_gen));   // rand shift
	INT2 shift(model.myrnd.rand(model.sizeY()), model.myrnd.rand(model.sizeX()));   // rand shift
	//printf("\nshift = y:%d x:%d\n", shift.y, shift.x);	dumpA(nlastlay);
	RunA::RunLast(shift, *vgpu_a[nlastlay], *vgpu_a[nlastlay - 1], *amask);
	for(int nlay = (int)nlastlay - 1; nlay > 0; nlay--){
		//dumpA(nlay);
		RunA::Run(*vgpu_a[nlay], *vgpu_a[nlay - 1], *amask);
		//RunA::RunConst(*vgpu_a[nlay], *vgpu_a[nlay - 1], cmask);
	}
	//dumpA(0);

	// Back to down
	for(size_t nlay = 1; nlay < nlastlay; nlay++){
		RunD::Run(*vgpu_f[nlay - 1], *vgpu_f[nlay], *vgpu_a[nlay], *ar_masks[nlay - 1]);
		//concurrency::copy(*ar_screen, vpos.data());
		//for(int n=0; n<(int)vpos.size(); n++) printf("%d\t%f\t%f\n", n, vpos[n].Pos.y, vpos[n].Pos.x);
	}
	RunDlast::Run(shift, *vgpu_f[nlastlay - 1], *ar_screen, *vgpu_a[nlastlay], *ar_last_dirs, model.sizeYX(), model.options.normDir());
} // ///////////////////////////////////////////////////////////////////////////////////////////////
HRESULT AMPEng2::get_data_d3dbuffer(void** d3dbuffer) const{
	return Concurrency::direct3d::get_buffer(*ar_screen)->QueryInterface(__uuidof(ID3D11Buffer), (LPVOID*)d3dbuffer);
} // ///////////////////////////////////////////////////////////////////////////////////////////////
void AMPEng2::dumpA(size_t nlay){
	const char separ[] = " ";
	if(nlay < 0) nlay = model.LaysCnt() - 1;
	model.setConsole();
	array<int, 2> av(*vgpu_a[nlay].get());
	std::cout << "A[" << nlay << "] y*x: " << av.extent[0] << "*" << av.extent[1] << std::endl;
	if(nlay == vgpu_a.size() - 1){
		for(int y = 0; y < av.extent[0]; y++){
			for(int x = 0; x < av.extent[1]; x++){
				int q = av[y][x];
				if(q < 0)
					std::cout << " . ";
				else
					printf("%2d ", q);
			}
			std::cout << std::endl;
		}
	} else{
		for(int y = 0; y < av.extent[0]; y++){
			for(int x = 0; x < av.extent[1]; x++){
				int q = av[y][x];
				assert(q == 0 || q == 1);
				if(q < 0)
					std::cout << ". ";
				else
					std::cout << q << separ;
					//std::cout << (q >> 3) << (1 & (q >> 2)) << (1 & (q >> 1)) << (1 & q) << separ;
			}
			std::cout << std::endl;
		}
	}
} // ////////////////////////////////////////////////////////////////
void AMPEng2::dumpA(){
	model.setConsole();
	for(int nlay = 0; nlay < (int)model.LaysCnt(); nlay++){
		dumpA(nlay);
		std::cout << std::endl;
	}
} // ////////////////////////////////////////////////////////////////////////////////////////
void AMPEng2::dumpD(size_t nlay){
	if(nlay < 0) nlay = model.LaysCnt() - 1;
	model.setConsole();
	array<DrQuadro, 2> av(*vgpu_f[nlay].get());
	std::cout << "Dirs[" << nlay << "] y*x: " << av.extent[0] << "*" << av.extent[1] << std::endl;
	for(int y = 0; y < av.extent[0]; y++){
		for(int x = 0; x < av.extent[1]; x++){
			//if(av[y][x].not0()){
			std::cout << " Y=" << y << " X=" << x << std::endl;
			av[y][x].dump();
			std::cout << std::endl;
		//}
		}
	}
	std::cout << std::endl;
} // ////////////////////////////////////////////////////////////////
void AMPEng2::dumpD(){
	for(int nlay = 0; nlay < (int)model.LaysCnt() - 1; nlay++)
		dumpD(nlay);
	dumpDLast();
} // ////////////////////////////////////////////////////////////////////////////////////////
void AMPEng2::dumpDLast(){
	int szy = ar_last_dirs->extent[0],
		szx = ar_last_dirs->extent[1];
	if(szy <= 0 || szx <= 0) return;
	array<FLT2, 2> av(*ar_last_dirs);
	std::cout << "DirsLast[" << model.LaysCnt() - 1 << "] y*x: " << szy << "*" << szx;
	for(int y = 0; y < szy; y++){
		printf("\n%+.2f", av[0][0].y);
		for(int x = 1; x < szx; x++)
			printf("  %+.2f", av[y][x].y);

		printf("\n%+.2f", av[0][0].x);
		for(int x = 1; x < szx; x++)
			printf("  %+.2f", av[y][x].x);
		printf("\n");
	}
} // ///////////////////////////////////////////////////////////////////////////////////////////////
void AMPEng2::dumpPos(){
	array_view<Vertex2D, 1> avpos(ar_screen->extent[0]);
	ar_screen.get()->copy_to(avpos);
	for(int n = 0; n < (int)avpos.extent[0]; n++){
		auto p = avpos[n].Pos;
		printf("%d:\t%+.3f %+.3f\n", n, p.y, p.x);
	}
} // ////////////////////////////////////////////////////////////////////////////////////////
