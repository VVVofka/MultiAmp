#include "pch.h"
#ifdef MODEA
#include "AMPEng2.h"
void AMPEng2::initialize_data(){
	int seed = model.options.seedRnd();
	if(seed >= 0)
		gen.seed(seed);
	else
		gen.seed(rd());
	distLastAY = std::uniform_int_distribution<int>(0, model.sizeY() - 1);
	distLastAX = std::uniform_int_distribution<int>(0, model.sizeX() - 1);
	nlastlay = size_t(model.LaysCnt() - 1); // N last lay

	int layscnt = (int)model.v_areas.size();
	for(int nlay = 0; nlay < layscnt; nlay++){
		const INT2 size = model.sizeYX(nlay);

		var_areas.push_back(std::unique_ptr<array<int, 2>>());
		var_areas[nlay] = std::unique_ptr<array<int, 2>>
			(new array<int, 2>(size.y, size.x, model.v_areas[nlay].begin(), m_accl_view));

		if(nlay < layscnt - 1){
			var_dirs.push_back(std::unique_ptr<array<DrQuadro, 2>>());
			var_dirs[nlay] = std::unique_ptr<array<DrQuadro, 2>>
				(new array<DrQuadro, 2>(size.y, size.x, model.v_dirs[nlay].begin(), m_accl_view));
		}
		if(nlay < layscnt - 2){
			var_masks.push_back(std::unique_ptr<array<FLT2, 1>>());
			FLT2 tmp[Options::szDirs];
			for(int j = 0; j < _countof(tmp); j++){
				tmp[j].y = model.options.blocks2D2.vin[j].y * (float)model.options.kLays(nlay);
				tmp[j].x = model.options.blocks2D2.vin[j].x * (float)model.options.kLays(nlay);
			}
			var_masks[nlay] = std::unique_ptr<array<FLT2, 1>>
				(new array<FLT2, 1>(Options::szDirs, tmp, m_accl_view));
		}
	}
	m_data = std::unique_ptr<array<Vertex2D, 1>>(new array<Vertex2D, 1>(int(model.lastPoss().size()), model.lastPoss().begin(), m_accl_view));
	last_dirs = std::unique_ptr<array<FLT2, 2>>(new array<FLT2, 2>(model.sizeY(), model.sizeX(), model.last_dirs.begin(), m_accl_view));
	amask = std::unique_ptr<array<int, 1>>(new array<int, 1>(16, model.options.aMask(), m_accl_view));
	//for(int j=0; j<16; j++)
	//	cmask.v[j] = model.options.aMask()[j];
} // ///////////////////////////////////////////////////////////////////////////////////////////////
void AMPEng2::run(){
	INT2 shift(distLastAY(gen), distLastAX(gen));   // rand shift
	//printf("\nshift = y:%d x:%d\n", shift.y, shift.x);	dumpA(nlastlay);
	RunA::RunLast(shift, *var_areas[nlastlay], *var_areas[nlastlay - 1], *amask);
	for(int nlay = (int)nlastlay - 1; nlay > 0; nlay--){
		//dumpA(nlay);
		RunA::Run(*var_areas[nlay], *var_areas[nlay - 1], *amask);
		//RunA::RunConst(*var_areas[nlay], *var_areas[nlay - 1], cmask);
	}
	//dumpA(0);

	// Back to down
	for(size_t nlay = 1; nlay < nlastlay; nlay++){
		RunD::Run(*var_dirs[nlay - 1], *var_dirs[nlay], *var_areas[nlay], *var_masks[nlay - 1]);
		//concurrency::copy(*m_data, vpos.data());
		//for(int n=0; n<(int)vpos.size(); n++) printf("%d\t%f\t%f\n", n, vpos[n].Pos.y, vpos[n].Pos.x);
	}
	RunDlast::Run(shift, *var_dirs[nlastlay - 1], *m_data, *var_areas[nlastlay], *last_dirs, model.sizeYX(), model.options.normDir());
} // ///////////////////////////////////////////////////////////////////////////////////////////////

void AMPEng2::dumpA(size_t nlay){
	const char separ[] = " ";
	if(nlay < 0) nlay = model.LaysCnt() - 1;
	setConsole();
	array<int, 2> av(*var_areas[nlay].get());
	std::cout << "A[" << nlay << "] y*x: " << av.extent[0] << "*" << av.extent[1] << std::endl;
	if(nlay == var_areas.size() - 1){
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
	setConsole();
	for(int nlay = 0; nlay < (int)model.LaysCnt(); nlay++){
		dumpA(nlay);
		std::cout << std::endl;
	}
} // ////////////////////////////////////////////////////////////////////////////////////////
void AMPEng2::dumpD(size_t nlay){
	if(nlay < 0) nlay = model.LaysCnt() - 1;
	setConsole();
	array<DrQuadro, 2> av(*var_dirs[nlay].get());
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
	int szy = last_dirs->extent[0],
		szx = last_dirs->extent[1];
	if(szy <= 0 || szx <= 0) return;
	array<FLT2, 2> av(*last_dirs);
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
	array_view<Vertex2D, 1> avpos(m_data->extent[0]);
	m_data.get()->copy_to(avpos);
	for(int n = 0; n < (int)avpos.extent[0]; n++){
		auto p = avpos[n].Pos;
		printf("%d:\t%+.3f %+.3f\n", n, p.y, p.x);
	}
} // ////////////////////////////////////////////////////////////////////////////////////////
#endif  // MODEA
