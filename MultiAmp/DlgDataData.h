#pragma once
#include <vector>
#include <amp_short_vectors.h>
#include <random>
#include <algorithm>
using namespace Concurrency::graphics;
	struct DlgDataDataItem{
		size_t offset;
		float_2 speed;
	};
class DlgDataData{
public:

	size_t szX;
	size_t szY;
	float sigma = 0;
	std::vector<DlgDataDataItem> v;

	bool create(size_t sz_x, size_t sz_y, float proc, float sigma);

	size_t cnt(){ return v.size(); }
	size_t szAll(){ return szX * szY; }
	size_t getPosX(size_t offset){ return offset % szX; }
	size_t getPosY(size_t offset){ return offset / szY; }
	size_t getPosXid(size_t idx){ return v[idx].offset % szX; }
	size_t getPosYid(size_t idx){ return v[idx].offset / szY; }

	DlgDataDataItem* getItem(size_t idx){ return &v[idx]; }
	size_t getOffset(size_t idx){ return getItem(idx)->offset; }
	float_2 getSpeed(size_t idx){ return getItem(idx)->speed; }
	float getProc(){ return (float)v.size() / szAll(); }
};

