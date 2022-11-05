#include "pch.h"
#include "MDX.h"
#pragma warning(suppress : 4996)

// Fore color in *.hlsl
// --------------------------------------------------------------------------------------

HRESULT MDX::InitDevice(HWND ghWnd, D3D_PRIMITIVE_TOPOLOGY Primitive){// Create Direct3D device and shaders. Call from wWinMain()
	primitive = Primitive;
	g_hWnd = ghWnd;
	HRESULT hr = S_OK;
	return hr;
} // ///////////////////////////////////////////////////////////////////////////////////////////
void MDX::CleanupDevice(){     //  Call from wWinMain() twice: onExit & onError
	if(g_pImmediateContext) g_pImmediateContext->ClearState();
	SAFE_RELEASE(g_pVertexPosBufferUAV);
	SAFE_RELEASE(g_pVertexPosBufferRV);
	SAFE_RELEASE(g_pVertexPosBuffer);
	SAFE_RELEASE(g_pVertexBuffer);
	SAFE_RELEASE(g_pVertexLayout);
	SAFE_RELEASE(g_pVertexShader);
	SAFE_RELEASE(g_pPixelShader);
	SAFE_RELEASE(g_pRenderTargetView);
	SAFE_RELEASE(g_pSwapChain);
	SAFE_RELEASE(g_pImmediateContext);
	SAFE_RELEASE(g_pd3dDevice);
} // ///////////////////////////////////////////////////////////////////////////////////////////
HRESULT MDX::CreateSwapChain(){
	HRESULT hr = S_OK;
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;
	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_DRIVER_TYPE driverTypes[] =
	{D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);
	D3D_FEATURE_LEVEL featureLevels[] = {D3D_FEATURE_LEVEL_11_0};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	// Create swap chain
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//sd.BufferDesc.Format = DXGI_FORMAT_R8G8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = g_hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	for(UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++){
		g_driverType = driverTypes[driverTypeIndex];
		//g_driverType = driverTypes[2];
		hr = D3D11CreateDeviceAndSwapChain(NULL, g_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &g_featureLevel, &g_pImmediateContext);
		if(SUCCEEDED(hr)) break;
	}
	RETURN_IF_FAIL(hr);

	// Create a render target view
	ID3D11Texture2D* pBackBuffer = NULL;
	RETURN_IF_FAIL(g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer));

	hr = g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_pRenderTargetView);
	SAFE_RELEASE(pBackBuffer);
	RETURN_IF_FAIL(hr);

	g_pImmediateContext->OMSetRenderTargets(1, &g_pRenderTargetView, NULL);

	// Setup the viewport
	D3D11_VIEWPORT vp{};
	vp.Width = (FLOAT)width;
	vp.Height = (FLOAT)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 0.0f;
	//vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_pImmediateContext->RSSetViewports(1, &vp);
	return hr;
} // //////////////////////////////////////////////////////////////////////////////////
HRESULT MDX::CreateVertexShader(const char* snaderName){
	HRESULT hr = S_OK;
	ID3DBlob* pVSBlob = NULL;
	LPCSTR pProfile = (g_pd3dDevice->GetFeatureLevel() >= D3D_FEATURE_LEVEL_11_0) ? "vs_5_0" : "vs_4_0";		//LPCSTR pProfile = "vs_5_0";
	hr = CompileShaderFromFile(L"..\\..\\WinDxDLL\\DXInterOpPsVs.hlsl", snaderName, pProfile, &pVSBlob);	// ..\\..\\ -Win32\Debug
	if(FAILED(hr)){
		hr = CompileShaderFromFile(L"..\\WinDxDLL\\DXInterOpPsVs.hlsl", snaderName, pProfile, &pVSBlob);
		if(FAILED(hr)){
			wchar_t* q = NULL;
			errno_t err = _get_wpgmptr(&q);
			if(err == 0){
				MessageBox(NULL, L"The vertex shader in DXInterOpPsVs.hlsl cannot be compiled", q, MB_OK);
				return hr;
			} else
				return NULL;
		}
	}
	// Create the vertex shader
	hr = g_pd3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &g_pVertexShader);
	if(FAILED(hr)){
		pVSBlob->Release();
		return hr;
	}
	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32_FLOAT,       0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0},
		//{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT numElements = ARRAYSIZE(layout);

	// Create the input layout
	hr = g_pd3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
		pVSBlob->GetBufferSize(), &g_pVertexLayout);
	pVSBlob->Release();
	RETURN_IF_FAIL(hr);

	// Set the input layout
	g_pImmediateContext->IASetInputLayout(g_pVertexLayout);

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex2D) * g_numVertices;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	RETURN_IF_FAIL(g_pd3dDevice->CreateBuffer(&bd, NULL, &g_pVertexBuffer));

	// Set vertex buffer
	UINT stride = sizeof(Vertex2D);
	UINT offset = 0;
	g_pImmediateContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

	// Set primitive topology
	g_pImmediateContext->IASetPrimitiveTopology(primitive);
	return hr;
} // //////////////////////////////////////////////////////////////////////////////////
HRESULT MDX::CompileShaderFromFile(LPCWSTR szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut){
	HRESULT hr = S_OK;
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_OPTIMIZATION_LEVEL2;
#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif
	FILE* f = fopen("tzt.tzt", "w, ccs=UNICODE");		fwrite(szFileName, 2, std::wstring(szFileName).size(), f);		fclose(f);
	// Read shader file to string buffer
	std::ifstream shaderFileStream(szFileName);
	std::stringstream ssbuff;
	ssbuff << shaderFileStream.rdbuf();
	shaderFileStream.close();
	std::string hlslProgram = ssbuff.str();

	ID3DBlob* pErrorBlob;
	hr = D3DCompile(hlslProgram.c_str(), hlslProgram.size(), NULL, NULL, NULL,
		szEntryPoint, szShaderModel, dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
	if(FAILED(hr)){
		if(pErrorBlob != NULL){
			OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
		}
	}
	SAFE_RELEASE(pErrorBlob);
	return hr;
} // ///////////////////////////////////////////////////////////////////////////////////////////////
HRESULT MDX::CreatePixelShader(){
	HRESULT hr = S_OK;
	// Compile the pixel shader
	ID3DBlob* pPSBlob = NULL;
	LPCSTR pProfile = (g_pd3dDevice->GetFeatureLevel() >= D3D_FEATURE_LEVEL_11_0) ? "ps_5_0" : "ps_4_0";

	hr = CompileShaderFromFile(L"..\\..\\WinDxDLL\\DXInterOpPsVs.hlsl", "PS", pProfile, &pPSBlob);	// ..\\..\\ -Win32\Debug
	if(FAILED(hr)){
		hr = CompileShaderFromFile(L"..\\WinDxDLL\\DXInterOpPsVs.hlsl", "PS", pProfile, &pPSBlob);
		if(FAILED(hr)){
			MessageBox(NULL, L"The pixel shader in DXInterOpPsVs.hlsl cannot be compiled.", L"Error", MB_OK);
			return hr;
		}
	}
	// Create the pixel shader
	hr = g_pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &g_pPixelShader);
	pPSBlob->Release();
	return hr;
} // ///////////////////////////////////////////////////////////////////////////////////////////
HRESULT MDX::CreateComputeShader(){
	// Bind a resource view to the CS buffer
	D3D11_BUFFER_DESC descBuf;
	ZeroMemory(&descBuf, sizeof(descBuf));
	g_pVertexPosBuffer->GetDesc(&descBuf);

	D3D11_SHADER_RESOURCE_VIEW_DESC DescRV;
	ZeroMemory(&DescRV, sizeof(DescRV));
	DescRV.Format = DXGI_FORMAT_R32_TYPELESS;
	DescRV.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
	DescRV.BufferEx.Flags = D3D11_BUFFEREX_SRV_FLAG_RAW;
	DescRV.Buffer.FirstElement = 0;
	DescRV.Buffer.NumElements = descBuf.ByteWidth / sizeof(int);
	RETURN_IF_FAIL(g_pd3dDevice->CreateShaderResourceView(g_pVertexPosBuffer, &DescRV, &g_pVertexPosBufferRV));
	return S_OK;
} // ///////////////////////////////////////////////////////////////////////////////////////////////////
void MDX::Render(){ //  Call from main loop wWinMain()
					// Bind the vertex shader data though the compute shader result buffer view
	ID3D11ShaderResourceView* aRViews[1] = {g_pVertexPosBufferRV};
	g_pImmediateContext->VSSetShaderResources(0, 1, aRViews);

	// Clear the back buffer 
	g_pImmediateContext->ClearRenderTargetView(g_pRenderTargetView, BackColor);

	// Render 
	g_pImmediateContext->VSSetShader(g_pVertexShader, NULL, 0);
	g_pImmediateContext->PSSetShader(g_pPixelShader, NULL, 0);
	g_pImmediateContext->Draw(g_numVertices, 0);

	ID3D11ShaderResourceView* ppSRVNULL[1] = {NULL};
	g_pImmediateContext->VSSetShaderResources(0, 1, ppSRVNULL);

	// Present the information rendered to the back buffer to the front buffer (the screen)
	g_pSwapChain->Present(0, 0);
} // ///////////////////////////////////////////////////////////////////////////////////////////////

