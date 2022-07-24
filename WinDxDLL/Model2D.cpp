#include "pch.h"
#include "Model2D.h"
void Model2D::Create(){
	INT2 minsz = INT2(options.iArr[InpOptions::LaysSzUpY], options.iArr[InpOptions::LaysSzUpX]);
	int maxszXY = options.iArr[InpOptions::LaysSzDn];
	double kRnd = options.dArr[InpOptions::kFillRnd];
	DBL2 kSigma(options.dArr[InpOptions::kSigmaY], options.dArr[InpOptions::kSigmaX]);

	const int RESERV_LAYS_CNT = 16;
	//v_poss.clear(); v_poss.reserve(RESERV_LAYS_CNT);
	v_areas.clear(); v_areas.reserve(RESERV_LAYS_CNT);
	v_dirs.clear(); v_dirs.reserve(RESERV_LAYS_CNT);
	vsz.clear(); vsz.reserve(RESERV_LAYS_CNT);
	size_t nlay = 0;
	INT2 sz(minsz);
	int szmaxxy = sz.Max();
	while(szmaxxy <= maxszXY / 2){ // without last lay (it don't contnent v_dirs)
		size_t szarea = size_t(sz.x) * size_t(sz.y);

		v_areas.push_back(std::vector<int>(szarea, -1)); // -1 - empty value
		v_dirs.push_back(std::vector<DrQuadro>(szarea));
		//v_poss.push_back(std::vector<Vertex2D>());
		vsz.push_back(sz);

		sz *= 2; szmaxxy *= 2;
		nlay++;
	} // while(szmaxxy <= maxszXY / 2){ // without last lay (it not contnent v_dirs)

	  // Last lay
	vsz.push_back(sz);
	const size_t szarea = size_t(sz.x) * size_t(sz.y);
	v_areas.push_back(std::vector<int>(szarea, -1)); // -1 - empty value
	ar_last_dirs.resize(szarea, FLT2(0, 0));

	// fill v_poss (for screen only) & v_areas for the last lay
	//v_poss.push_back(std::vector<Vertex2D>());
	fillrnd((int)nlay, (int)szarea, kRnd, kSigma);
	//filltest(nlay);
	options.iArr[InpOptions::LaysCnt] = int(nlay);
	options.saveAuto();
} // //////////////////////////////////////////////////////////////////////////////////
Vertex2D Model2D::norm(int curpos, INT2 sizes) const{
	const int iy = curpos / sizes.x;
	const float y = NORMAL_TO_AREA(iy, sizes.y);
	const int ix = curpos % sizes.x;
	const float x = NORMAL_TO_AREA(ix, sizes.x);
	return Vertex2D(y, x);
} // /////////////////////////////////////////////////////////////////////////////////
void Model2D::fillrnd(int nlay, size_t szarea, double kFill, DBL2 kSigma){
	std::mt19937 gen;  // to seed mersenne twister. rand: gen(rd())

	int seed = options.seedRnd();
	if(seed >= 0)
		gen.seed(seed);
	else{
		std::random_device rd;   // non-deterministic generator
		gen.seed(rd());
	}
	std::uniform_int_distribution<int> dist(0, int(szarea) - 1);
	size_t szpos = size_t(szarea * kFill + 0.5);
	v_scr.reserve(szpos);

	const INT2 sz(vsz[nlay]);
	std::normal_distribution<> distry(sz.y * 0.5, sz.y * 0.3 * kSigma.y);
	std::normal_distribution<> distrx(sz.x * 0.5, sz.x * 0.3 * kSigma.x);

	while(v_scr.size() < szpos){
		int curpos=0;
		do{
			//curpos = dist(gen);
			int y=0, x=0;
			do{
				y = (int)distry(gen);
			} while(y < 0 || y >= sz.y);
			do{
				x = (int)distrx(gen);
			} while(x < 0 || x >= sz.x);

			curpos = y * sz.x + x;
			assert(curpos < (int)v_areas[nlay].size());
		} while(v_areas[nlay][curpos] >= 0);
		v_areas[nlay][curpos] = (unsigned int)v_scr.size(); // 0 ... szpos-1

		const Vertex2D vert2 = norm(curpos, sz);
		v_scr.push_back(vert2);
	} // 	while(v_poss[nlay].size() < szpos)
}// /////////////////////////////////////////////////////////////////////////////////
void Model2D::dumpA(int nlay) const{
	setConsole();
	std::cout << " y*x: " << sizeY(nlay) << "*" << sizeX(nlay) << std::endl;
	for(int y = 0; y < sizeY(nlay); y++){
		for(int x = 0; x < sizeX(nlay); x++){
			const int val = v_areas[nlay][y * sizeX(nlay) + x];
			printf(" %c", val >= 0 ? '*' : '.');
		}
		printf("\n");
	}
} // ////////////////////////////////////////////////////////////////////////////////////////////////
void Model2D::dumpD(int nlay) const{
	setConsole();
	std::cout << " y*x: " << sizeY(nlay) << "*" << sizeX(nlay) << std::endl;
	for(int y = 0; y < sizeY(nlay); y++){
		for(int x = 0; x < sizeX(nlay); x++){
			const int val = v_areas[nlay][y * sizeX(nlay) + x];
			printf(" %c", val >= 0 ? '*' : '.');
		}
		printf("\n");
	}
} // ////////////////////////////////////////////////////////////////////////////////////////////////
