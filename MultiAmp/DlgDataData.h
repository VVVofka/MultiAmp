#pragma once
#include <vector>
#include <amp_short_vectors.h>
#include <random>
#include <algorithm>
//using namespace Concurrency::graphics;
	//struct DlgDataDataItem{
	//	size_t offset = 0;
	//	float_2 speed;
	//};
class DlgDataData{
public:
	size_t szX = 0;
	size_t szY = 0;
	float* sigma = NULL;
	UINT32* seed = NULL;
	std::vector<size_t>* voffset = NULL;
	//std::vector<float_2> vspeed;

	bool create(size_t sz_x, size_t sz_y, std::vector<size_t>* v_in, float* sigma, UINT32* seed);
	bool generRndFlat(size_t new_count);

	size_t cnt(){ return voffset->size(); }
	size_t szAll(){ return szX * szY; }
	size_t getPosX(size_t offset){ return offset % szX; }
	size_t getPosY(size_t offset){ return offset / szY; }
	size_t getPosXid(size_t idx){ return (*voffset)[idx] % szX; }
	size_t getPosYid(size_t idx){ return (*voffset)[idx] / szY; }

	//DlgDataDataItem* getItem(size_t idx){ return &v[idx]; }
	size_t getOffset(size_t idx){ return (*voffset)[idx]; }
	//float_2 getSpeed(size_t idx){ return getItem(idx)->speed; }
	float getProc(){ return (float)voffset->size() / szAll(); }
};

