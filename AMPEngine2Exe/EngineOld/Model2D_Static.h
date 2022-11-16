#pragma once
#include <vector>
#include "..\MDX\Vertex.h"
#include "Utils.h"

class Model2D_Static{
public:
	//	using Model2D::fillScreenPoints;
	static void setConsole();
	static void fillScreenPoints(const std::vector<size_t>& vin, std::vector<Vertex2D>& v, const INT2& sz);
	static Vertex2D norm(int curpos, const INT2& sizes);
private:
	// [-1.0 ... +1.0]
}; // *****************************************************************************