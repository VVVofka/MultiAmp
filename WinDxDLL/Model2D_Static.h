#pragma once
#include "Vertex.h"
#include "Utils.h"
#include <vector>

class Model2D_Static{
public:
	//	using Model2D::fillScreenPoints;
	static void setConsole();
	static void fillScreenPoints(const std::vector<size_t>& vin, std::vector<Vertex2D>& v, const INT2& sz);
private:
	static Vertex2D norm(int curpos, const INT2& sizes);
}; // *****************************************************************************