#pragma once

//#pragma warning(push)
//#pragma warning(disable:4005 26812) 
#include <DirectXMath.h>
//#pragma warning(pop)

struct Vertex2D{
    Vertex2D(){ Pos.x = Pos.y = 0; }
    Vertex2D(float y, float x){ Pos.x = x; Pos.y = y; }
    DirectX::XMFLOAT2 Pos;
}; // ********************************************************************************************
struct Vertex3D{
    DirectX::XMFLOAT3 Pos;
}; // ********************************************************************************************
