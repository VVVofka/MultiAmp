#pragma once
#include "NewEngine.h"
#include "MDX.h"
#include "AMPEng2.h"
#include "Vertex.h"
#include <vector>
#include "Engine2.h"

class MDX2 : public MDX{

	// TODO: del g_pAMPComputeEngine 
#ifndef NEW_ENGINE // not NEW_ENGINE
	AMPEng2* g_pAMPComputeEngine = NULL;
public:
	HRESULT InitDevice(HWND ghWnd, std::vector<Vertex2D> vertices,
		D3D_PRIMITIVE_TOPOLOGY Primitive = D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
#else // NEW_ENGINE
	Engine2* g_pAMPComputeEngine = NULL;
public:
	structAll* cfg_all;
	HRESULT InitDevice(HWND ghWnd, structAll* cfg_all,
		D3D_PRIMITIVE_TOPOLOGY Primitive = D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
#endif // NEW_ENGINE

	void Render();
	void CleanupDevice();
private:
	HRESULT CreateComputeShader(structAll* cfg_all = NULL);
}; // ***********************************************************************
   /*
D3D11_INPUT_ELEMENT_DESC layout[] =
{
	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
};
SimpleVertex vertices[] =
{
	{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
	{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
	{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) },
	{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
	{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) },
	{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },
	{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
	{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) }
};
*/
