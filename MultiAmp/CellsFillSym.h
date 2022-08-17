#pragma once
#include "Directs.h"
#include <array>
class CellsFillSym{
public:
	std::array<Direct, 16> vout;
	std::array<bool, 16> vIsEnabled;

	std::array<Direct, 16>& fill(size_t mask, const std::array<Direct, 16>& v_in);
private:
	void w0(const std::array<Direct, 16>& v_in);
};

