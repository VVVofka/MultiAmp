#pragma once
#include <random>
#include <cmath>
#include <vector>

#include <D3D11.h>
#include <DirectXMath.h>

#include "Model2D_Static.h"
#include "Masks.h"

#include "Options.h"

#include "..\..\OptsTinyLib\structAll.h"
#include "..\myRnd.h"

class Model2D : public Model2D_Static{
public:
	structAll* cfgAll;
	Options options;
	std::vector<Vertex2D> v_scr;
	std::vector<std::vector<int>> v_areas;
	std::vector<std::vector<DrQuadro>> v_dirs;
	std::vector<FLT2> ar_last_dirs;
	std::vector<INT2> vsz;

	std::vector<int> lastArea() const { return v_areas[v_areas.size() - 1]; }

	int sizeY(int nlay) const { return vsz[nlay].y; }
	int sizeY() const { return vsz[vsz.size() - 1].y; }
	int sizeX(int nlay) const { return vsz[nlay].x; }
	int sizeX() const { return vsz[vsz.size() - 1].x; }
	const INT2& sizeYX(int nlay) const {return vsz[nlay];}
	const INT2& sizeYX() const {return vsz[vsz.size() - 1];}
	size_t LaysCnt() const { return v_areas.size(); }
	size_t sizeAll(int nlay) const{ return vsz[nlay].Square(); }
	size_t sizeAll() const{ return vsz[vsz.size() - 1].Square();}

	bool Create();
	bool CreateOld(structAll* cfg_all);
	void dumpA(int nlay) const;
	void dumpD(int nlay) const;
	FLT2* getFLT2(){return options.getFLT2();}

	LehmerRng myrnd;	//std::mt19937 rnd_gen; // to seed mersenne twister. rand: gen(rd())

protected:
	void fillrnd(int nlay, size_t szarea, double kFill, DBL2 kSigma);
	// TODO: static
}; // *****************************************************************************
