#include "pch.h"
#include "MDX.h"

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

