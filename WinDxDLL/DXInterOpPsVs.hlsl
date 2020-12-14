// --------------------------------------------------------------------------------------
// File: DXInterOp.hlsl
//
// Copyright (c) Microsoft Corporation. All rights reserved.
// --------------------------------------------------------------------------------------

// This structured buffer is mapped to the ID3D11Buffer which is associated to the 
// array used in the parallel_for_each kernel in the compute engine. The type of the 
// RWStructured buffer is uint, which has the same memory size of type float.
ByteAddressBuffer posBufVS : register( t0);

// --------------------------------------------------------------------------------------
// Vertex Shader
// --------------------------------------------------------------------------------------
float4 VS2( uint id : SV_VERTEXID ) : SV_POSITION
{
	// vertex type is declared as a struct of XMFLOAT2. So to access the buffer, we need 
	// to adjust the indexing. 
    return float4(asfloat(posBufVS.Load(id*8+0)), asfloat(posBufVS.Load(id*8+4)), 0.0f, 1.0f );
}
float4 VS3(uint id : SV_VERTEXID) : SV_POSITION
{
	// vertex type is declared as a struct of XMFLOAT2. So to access the buffer, we need 
	// to adjust the indexing. 
	return float4(asfloat(posBufVS.Load(id * 8 + 0)), asfloat(posBufVS.Load(id * 8 + 4)), asfloat(posBufVS.Load(id * 8 + 8)), 1.0f);
}

// --------------------------------------------------------------------------------------
// Pixel Shader
// --------------------------------------------------------------------------------------
float4 PS( float4 Pos : SV_POSITION ) : SV_Target
{
    return float4( 1.0f, 1.0f, 0.0f, 1.0f );    // Yellow, with Alpha = 1
}
