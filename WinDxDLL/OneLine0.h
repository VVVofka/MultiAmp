#pragma once
#include <vector>
#include "Vertex.h"
#include "Utils.h"

class OneLine0{
public:
	OneLine0();
	~OneLine0();

	size_t szx = 0, szy = 0, szall = 0;	// size of area
	size_t szdata = 0;
	Vertex2D* pscr = NULL;
	std::vector<size_t>* pv = NULL;	// input & output

	void Create(const size_t sz_x, const size_t sz_y, std::vector<size_t>* v_in_out);
private:
	void fill_vscr();
};	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

