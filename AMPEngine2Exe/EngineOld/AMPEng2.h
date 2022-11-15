#pragma once
#include "..\Engine\NewEngine.h"

#ifndef NEW_ENGINE // not NEW_ENGINE

#include <amp.h>
#include <amp_graphics.h>
#include <vector>
#include <random>
#include <D3D11.h>

#include "Model2D.h"
#include "..\MDX\Vertex.h"
#include "RunA.h"
#include "RunD.h"
#include "RunDlast.h"
#include "Masks.h"
#include "Utils.h"
//#include "Options.h"
#include "..\myRnd.h"

extern Model2D model;

using namespace Concurrency;
using namespace concurrency::direct3d;

class AMPEng2{
	accelerator_view m_accl_view;
	size_t nlastlay = 0;     // N last lay

	std::unique_ptr<array<Vertex2D, 1>>	ar_screen; // for screen
	std::vector<std::unique_ptr<array<int, 2>>> vgpu_a;
	std::vector<std::unique_ptr<array<DrQuadro, 2>>> vgpu_f;
	std::unique_ptr<array<FLT2, 2>> ar_last_dirs;
	std::unique_ptr<array<int, 1>> amask;
	std::vector<std::unique_ptr<array<FLT2, 1>>> ar_masks;

public:
	AMPEng2(ID3D11Device* d3ddevice);
	void run();    // main function in render

	HRESULT get_data_d3dbuffer(void** d3dbuffer) const;

private:
	//std::random_device rd;   // non-deterministic generator
	//std::mt19937 gen;        // to seed mersenne twister. rand: gen(rd())
	std::uniform_int_distribution<int> distrLastAY, distrLastAX;
	LehmerRng m_myrnd;

public:
	void dumpA(size_t nlay);
	void dumpA();
	void dumpD(size_t nlay);
	void dumpD();
	void dumpDLast();
	void dumpPos();
}; // *******************************************************************************************************
#endif // NEW_ENGINE

