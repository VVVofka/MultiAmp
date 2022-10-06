#include "pch.h"
#include "DlgDataData.h"

bool DlgDataData::create(size_t sz_x, size_t sz_y, float proc, float in_sigma){
	sigma = in_sigma;
	v.resize((size_t)((szX = sz_x) * (szY = sz_y) * proc + 0.5));
	std::vector<int> ar(szX * szY, -1);

	std::random_device rd;   // non-deterministic generator
	std::mt19937 gen(rd());  // to seed mersenne twister.
	std::uniform_int_distribution<> distOfsX(0, szX - 1);	// distribute results between  inclusive.
	std::uniform_int_distribution<> distOfsY(0, szY - 1);	// distribute results between  inclusive.
	std::uniform_real_distribution<> distSpeed(-1, 1);		// distribute results between  inclusive.

	UINT64 dog = ar.size() * (UINT64)10;
	for(size_t j = 0; j < v.size(); j++){
		size_t ofsX, ofsY, ofs;
		while(true){
			ofsX = distOfsX(gen);
			ofsY = distOfsY(gen);
			ofs = ofsY * szX + ofsX;
			if(ar[ofs] == -1){
				ar[ofs] = j;
				v[j].offset = ofs;
				v[j].speed = float_2((float)distSpeed(gen), (float)distSpeed(gen));
				break;
			}
			if(dog-- == 0)
				return false;
		}
	}
	return true;
} // ////////////////////////////////////////////////////////////////////////////////////////////////////////
