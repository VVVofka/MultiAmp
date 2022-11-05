#pragma once
#include <amp.h>
#include <amp_graphics.h>
#include <D3D11.h>
#include <vector>
//#include <random>

//#include "Model2D.h"
//#include "RunA.h"
//#include "RunD.h"
//#include "RunDlast.h"
//#include "Masks.h"
//#include "Options.h"
#include "Vertex.h"
#include "Utils.h"
#include "myRnd.h"
#include "Lays.h"

using namespace Concurrency;
using namespace concurrency::direct3d;

class Engine2{
	accelerator_view m_accl_view;
	//size_t nlastlay = 0;     // N last lay

	std::unique_ptr<array<Vertex2D, 1>>	ar_screen; // for screen
	std::vector<std::unique_ptr<array<int, 2>>> vgpu_a;
	std::vector<std::unique_ptr<array<DrQuadro, 2>>> vgpu_f;
	std::unique_ptr<array<FLT2, 2>> ar_last_dirs;
	std::unique_ptr<array<int, 1>> amask;
	std::vector<std::unique_ptr<array<FLT2, 1>>> ar_masks;

public:
	Lays lays;

	Engine2(ID3D11Device* d3ddevice);
	void run();    // main function in render

	HRESULT get_data_d3dbuffer(void** d3dbuffer) const;	// for screen
}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

