#pragma once

//#pragma warning(push)
//#pragma warning(disable:4005 26812) 
#include <DirectXMath.h>
//#pragma warning(pop)

struct Vertex2D{
    DirectX::XMFLOAT2 Pos;

    Vertex2D(){ Pos.x = Pos.y = 0; }
    Vertex2D(float y, float x){ Pos.x = x; Pos.y = y; }
}; // ********************************************************************************************
//struct Vertex3D{
//    DirectX::XMFLOAT3 Pos;
//}; // ********************************************************************************************
