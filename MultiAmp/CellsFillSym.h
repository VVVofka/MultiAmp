#pragma once
#include "Directs.h"
#include <array>
class CellsFillSym{
public:
	std::array<Direct, 16> vout;
	std::array<bool, 16> vIsEnabled;

	std::array<Direct, 16>& fill(size_t mask, const std::array<Direct, 16>* v_in);
private:
	const std::array<Direct, 16>* vin;
	void w0();
	void wslope();
	void wvert();
	void whoriz();
	void wdiag();

	void activ(int act);
	void slope(int act, int pos);
	void rise(int act, int pos);
	void vert(int act, int pos);
	void horiz(int act, int pos);
	void rotate180(int act, int pos);
};

