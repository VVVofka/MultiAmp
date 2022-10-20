#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <exception>
#include <d3dcompiler.h>
#include <D3D11.h>
#include "Vertex.h"
//#ifndef SAFE_DELETE_ARRAY
//#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
//#endif    
//#ifndef SAFE_RELEASE_DELETE
//#define SAFE_RELEASE_DELETE(p)	{ if(p) { (p)->Release(); delete (p); (p)=NULL; } }
//#endif
#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#endif    

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }
#endif

#ifndef RETURN_IF_FAIL
#define RETURN_IF_FAIL(x)    { HRESULT thr = (x); if (FAILED(thr)) { return E_FAIL; } }
#endif

class MDX{
protected:
	HWND                        g_hWnd = NULL;
	D3D_DRIVER_TYPE             g_driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL           g_featureLevel = D3D_FEATURE_LEVEL_11_0;
	ID3D11Device*				g_pd3dDevice = NULL;
	ID3D11DeviceContext*		g_pImmediateContext = NULL;
	IDXGISwapChain*				g_pSwapChain = NULL;
	ID3D11RenderTargetView*		g_pRenderTargetView = NULL;
	ID3D11ComputeShader*		g_pComputeShader = NULL;
	ID3D11VertexShader*			g_pVertexShader = NULL;
	ID3D11PixelShader*			g_pPixelShader = NULL;
	ID3D11InputLayout*			g_pVertexLayout = NULL;
	ID3D11Buffer*				g_pVertexBuffer = NULL;
	ID3D11Buffer*				g_pVertexPosBuffer = NULL;
	ID3D11ShaderResourceView*	g_pVertexPosBufferRV = NULL;
	ID3D11UnorderedAccessView*	g_pVertexPosBufferUAV = NULL;
public:
	unsigned int				g_numVertices = 0;
	//D3D_PRIMITIVE_TOPOLOGY primitive = D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	D3D_PRIMITIVE_TOPOLOGY primitive = D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
	float BackColor[4] = {0.0f, 0.125f, 0.3f, 1.0f}; // red,green,blue,alpha
	HRESULT InitDevice(HWND ghWnd, D3D_PRIMITIVE_TOPOLOGY Primitive = D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	void CleanupDevice();
protected:
	HRESULT CreateSwapChain();
	HRESULT CreateVertexShader(const char* snaderName);
	HRESULT CompileShaderFromFile(LPCWSTR szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
	HRESULT CreatePixelShader();
	void Render(UINT stride);
	HRESULT CreateComputeShader();
}; // ******************************************************************************************

