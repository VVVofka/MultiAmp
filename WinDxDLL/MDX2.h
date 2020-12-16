#pragma once
#ifdef MODEA

#include "MDX.h"
#include "AMPEng2.h"
#include "Vertex.h"
#include <vector>

class MDX2 : public MDX {
	AMPEng2* g_pAMPComputeEngine = NULL;
public:
    HRESULT InitDevice(HWND ghWnd,
                       std::vector<Vertex2D> vertices,
                       D3D_PRIMITIVE_TOPOLOGY Primitive = D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST)
    {// Create Direct3D device and shaders. Call from wWinMain()
        HRESULT hr = MDX::InitDevice(ghWnd, Primitive);
        g_numVertices = (unsigned int)vertices.size();
        RETURN_IF_FAIL(MDX::CreateSwapChain());
#ifdef MYAREA
        RETURN_IF_FAIL(CreateComputeShader());
#else
        RETURN_IF_FAIL(CreateComputeShader(vertices));
#endif
        RETURN_IF_FAIL(MDX::CreateVertexShader("VS2"));
        RETURN_IF_FAIL(MDX::CreatePixelShader());
        return hr;
    } // //////////////////////////////////////////////////////////////////////////////////
    //void Create(int minszX, int minszY, int maxsz, double kFill){
    //    g_pAMPComputeEngine->Create(minszX, minszY, maxsz, kFill);
    //} // //////////////////////////////////////////////////////////////////////////////////
private:
#ifdef MYAREA
 HRESULT CreateComputeShader() {
        g_pAMPComputeEngine = new AMPEng2(g_pd3dDevice);
        g_pAMPComputeEngine->initialize_data();
        //g_pAMPComputeEngine->Create(4, 3, 1000, 0.33);
        RETURN_IF_FAIL(g_pAMPComputeEngine->get_data_d3dbuffer(reinterpret_cast<void**>(&g_pVertexPosBuffer)));
        return MDX::CreateComputeShader();
    } // /////////////////////////////////////////////////////////////////////////////////////////////
#else
 HRESULT CreateComputeShader(std::vector<Vertex2D>& vertices) {
        g_pAMPComputeEngine = new AMPEngine2(g_pd3dDevice);
        g_pAMPComputeEngine->initialize_data(vertices);
        //g_pAMPComputeEngine->Create(4, 3, 1000, 0.33);
        RETURN_IF_FAIL(g_pAMPComputeEngine->get_data_d3dbuffer(reinterpret_cast<void**>(&g_pVertexPosBuffer)));
        return MDX::CreateComputeShader();
    } // /////////////////////////////////////////////////////////////////////////////////////////////
#endif
 public:
    void Render() {               //  Call from main loop wWinMain()
        g_pAMPComputeEngine->run();    
        MDX::Render(sizeof(Vertex2D));
        //MDX::Render(28); //!!!
    } // ///////////////////////////////////////////////////////////////////////////////////////////////////
    void CleanupDevice(){     //  Call from wWinMain() twice: onExit & onError
        MDX::CleanupDevice();
        SAFE_DELETE(g_pAMPComputeEngine);
    } // //////////////////////////////////////////////////////////////////////////////////////////
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
#endif  // MODEA
