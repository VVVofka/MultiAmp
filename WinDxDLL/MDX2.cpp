#include "pch.h"
#include "MDX2.h"

#ifndef NEW_ENGINE // not NEW_ENGINE
// from 2x: dWInterOp.cpp mn() & dlg options
HRESULT MDX2::InitDevice(HWND ghWnd, std::vector<Vertex2D> vertices, D3D_PRIMITIVE_TOPOLOGY Primitive){// Create Direct3D device and shaders. Call from wWinMain()
	HRESULT hr = MDX::InitDevice(ghWnd, Primitive);
	g_numVertices = (unsigned int)vertices.size();
	RETURN_IF_FAIL(MDX::CreateSwapChain());
	RETURN_IF_FAIL(CreateComputeShader());	// init g_pAMPComputeEngine
	RETURN_IF_FAIL(MDX::CreateVertexShader("VS2"));
	RETURN_IF_FAIL(MDX::CreatePixelShader());
	return hr;
} // ///////////////////////////////////////////////////////////////////////////////////////////////////
#else // NEW_ENGINE
// from 2x: dWInterOp.cpp mn() & dlg options
HRESULT MDX2::InitDevice(HWND ghWnd, structAll* cfg_all, D3D_PRIMITIVE_TOPOLOGY Primitive){// Create Direct3D device and shaders. Call from wWinMain()
	if(g_pAMPComputeEngine != NULL)
		CleanupDevice();
	HRESULT hr = MDX::InitDevice(ghWnd, Primitive);
	g_numVertices = (unsigned int)cfg_all->data.v.size();
	RETURN_IF_FAIL(MDX::CreateSwapChain());
	RETURN_IF_FAIL(CreateComputeShader(cfg_all));	// init g_pAMPComputeEngine
	RETURN_IF_FAIL(MDX::CreateVertexShader("VS2"));
	RETURN_IF_FAIL(MDX::CreatePixelShader());
	return hr;
} // ///////////////////////////////////////////////////////////////////////////////////////////////////
#endif // NEW_ENGINE
void MDX2::CleanupDevice(){     //  Call from wWinMain() twice: onExit & onError
	MDX::CleanupDevice();
	SAFE_DELETE(g_pAMPComputeEngine);
} // ///////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT MDX2::CreateComputeShader(structAll* cfg_all){ // from this->InitDevice()
#ifndef NEW_ENGINE
	g_pAMPComputeEngine = new AMPEng2(g_pd3dDevice);
#else
	g_pAMPComputeEngine = new Engine2(g_pd3dDevice, cfg_all);
#endif // NEWENINE
	RETURN_IF_FAIL(g_pAMPComputeEngine->get_data_d3dbuffer(reinterpret_cast<void**>(&g_pVertexPosBuffer)));
	return MDX::CreateComputeShader();
} // ///////////////////////////////////////////////////////////////////////////////////////////////////
void MDX2::Render(){				//  Call from main loop wWinMain()
	g_pAMPComputeEngine->run();		// work with lays ( MAIN )
	MDX::Render();					// draw on screen
} // ///////////////////////////////////////////////////////////////////////////////////////////////////
