#pragma once
#include <vector>
#include <amp_short_vectors.h>
#include <random>
#include <algorithm>
using namespace Concurrency::graphics;
class DlgDataData{
public:
	struct DlgDataDataItem{
		size_t offset;
		float_2 speed;
	};

	size_t szX;
	size_t szY;
	std::vector<DlgDataDataItem> v;

	void create(size_t sz_x, size_t sz_y, float proc){
		v.resize((size_t)((szX = sz_x) * (szY = sz_y) * proc + 0.5));

		std::random_device rd;   // non-deterministic generator
		std::mt19937 gen(rd());  // to seed mersenne twister.
		std::uniform_int_distribution<> distOfs(0, szAll() - 1); // distribute results between  inclusive.
		std::uniform_real_distribution<> distSpeed(-1, 1);			// distribute results between  inclusive.

		for(size_t j = 0; j < v.size(); j++){
			while(true){
				size_t ofs = distOfs(gen);
				bool found = false;	// std::any_of(v.begin(), v.end(), [&](DlgDataDataItem& i) {return i.offset == ofs; });
				for(size_t i = 0; i < j; i++){
					if(v[i].offset == ofs){
						found = true;
						break;
					}
				}
				if(!found){
					v[j].offset = ofs;
					v[j].speed = float_2((float)distSpeed(gen), (float)distSpeed(gen));
					break;
				}
			}
		}
	}

	size_t cnt(){ return v.size(); }
	size_t szAll(){ return szX * szY; }
	size_t getX(size_t offset){ return offset % szX; }
	size_t getY(size_t offset){ return offset / szY; }

	DlgDataDataItem* getItem(size_t idx){ return &v[idx]; }
	size_t getOffset(size_t idx){ return getItem(idx)->offset; }
	float_2 getSpeed(size_t idx){ return getItem(idx)->speed; }
	float getProc(){ return (float)v.size() / szAll(); }
};

