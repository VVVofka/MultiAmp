#pragma once
#ifdef MODEA

#include <amp.h>
#include <amp_graphics.h>
#include <vector>
#include <random>

//#pragma warning(push)
//#pragma warning(disable:4005 26812) 
#include <D3D11.h>
//#pragma warning(pop)

#include "Model2D.h"
#include "Vertex.h"
#include "RunA.h"
#include "RunD.h"
#include "RunDlast.h"
#include "Masks.h"
#include "Utils.h"
#include "Options.h"

extern Model2D model;

using namespace Concurrency;
using namespace concurrency::direct3d;

class AMPEng2{
	accelerator_view					m_accl_view;

	std::unique_ptr<array<Vertex2D, 1>>	m_data; // for screen
	std::vector<std::unique_ptr<array<int, 2>>> var_areas;
	std::vector<std::unique_ptr<array<DrQuadro, 2>>> var_dirs;
	std::unique_ptr<array<FLT2, 2>> last_dirs;
	std::unique_ptr<array<int, 1>> amask;
	//std::unique_ptr<array<FLT2, 1>> dmask;
	std::vector<std::unique_ptr<array<FLT2, 1>>> var_masks;

public:
	AMPEng2(ID3D11Device* d3ddevice) : m_accl_view(Concurrency::direct3d::create_accelerator_view(d3ddevice)){
	} // /////////////////////////////////////////////////////////////////////////////////////////////////////

	void initialize_data();
	void run();

	HRESULT get_data_d3dbuffer(void** d3dbuffer) const{
		return Concurrency::direct3d::get_buffer(*m_data)->QueryInterface(__uuidof(ID3D11Buffer), (LPVOID*)d3dbuffer);
	} // ///////////////////////////////////////////////////////////////////////////////////////////////

private:
	std::random_device rd;   // non-deterministic generator
	std::mt19937 gen;  // to seed mersenne twister. rand: gen(rd())
	std::uniform_int_distribution<int> distLastAY, distLastAX;
	size_t nlastlay = 0;  // N last lay

public:
	void dumpA(int nlay);
	void dumpA();
	void dumpD(int nlay);
	void dumpD();
	void dumpDLast();
	void dumpPos();
}; // *******************************************************************************************************
#endif  // MODEA

