#include "pch.h"
#include "MDX2.h"
HRESULT MDX2::InitDevice(HWND ghWnd, std::vector<Vertex2D> vertices, D3D_PRIMITIVE_TOPOLOGY Primitive){// Create Direct3D device and shaders. Call from wWinMain()
	HRESULT hr = MDX::InitDevice(ghWnd, Primitive);
	g_numVertices = (unsigned int)vertices.size();
	RETURN_IF_FAIL(MDX::CreateSwapChain());

	RETURN_IF_FAIL(MDX::CreateVertexShader("VS2"));
	RETURN_IF_FAIL(CreateComputeShader());
	
	RETURN_IF_FAIL(MDX::CreatePixelShader());
	return hr;
} // ///////////////////////////////////////////////////////////////////////////////////////////////////
void MDX2::Render(){				//  Call from main loop wWinMain()
	g_pAMPComputeEngine->run();		// work with lays ( MAIN )
	MDX::Render(sizeof(Vertex2D));	// draw on screen
} // ///////////////////////////////////////////////////////////////////////////////////////////////////
void MDX2::CleanupDevice(){     //  Call from wWinMain() twice: onExit & onError
	MDX::CleanupDevice();
	SAFE_DELETE(g_pAMPComputeEngine);
} // ///////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT MDX2::CreateComputeShader(){
	g_pAMPComputeEngine = new AMPEng2(g_pd3dDevice);
	RETURN_IF_FAIL(g_pAMPComputeEngine->get_data_d3dbuffer(reinterpret_cast<void**>(&g_pVertexPosBuffer)));
	return MDX::CreateComputeShader();
} // ///////////////////////////////////////////////////////////////////////////////////////////////////
