#pragma once
#include <vector>
#include <amp_short_vectors.h>
#include <random>
#include <algorithm>
using namespace std;
class DlgDataData{
public:
	size_t szX = 0;
	size_t szY = 0;
	string* sigma = NULL;
	string* seed = NULL;
	vector<size_t>* voffset = NULL;

	void create(size_t sz_x, size_t sz_y, vector<size_t>* v_in, string* sigma, string* seed);
	bool generRndFlat(size_t new_count);

	size_t cnt(){ return voffset->size(); }
	size_t szAll(){ return szX * szY; }
	size_t getPosX(size_t offset){ return offset % szX; }
	size_t getPosY(size_t offset){ return offset / szY; }
	size_t getPosXid(size_t idx){ return (*voffset)[idx] % szX; }
	size_t getPosYid(size_t idx){ return (*voffset)[idx] / szY; }

	size_t getOffset(size_t idx){ return (*voffset)[idx]; }
	float getProc(){ return (float)voffset->size() / szAll(); }
};

