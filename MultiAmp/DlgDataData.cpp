#include "pch.h"
#include "DlgDataData.h"

bool DlgDataData::create(size_t sz_x, size_t sz_y, std::vector<size_t>* in_v, float* in_sigma, UINT32* in_seed){
	szX = sz_x, szY = sz_y;
	voffset = in_v;
	sigma = in_sigma;
	seed = in_seed;

	//auto sz = sz_x * sz_y;
	//if(sz != in_v->size()){
	//	*sigma = 0;
	//	generRndFlat(sz);
	//}
	return true;
} // ////////////////////////////////////////////////////////////////////////////////////////////////////////
bool DlgDataData::generRndFlat(size_t new_count){
	voffset->resize(new_count);
	std::vector<int> ar(szX * szY, -1);

	std::random_device rd;   // non-deterministic generator
	std::mt19937 gen(rd());  // to seed mersenne twister.
	std::uniform_int_distribution<> distOfsX(0, szX - 1);	// distribute results between  inclusive.
	std::uniform_int_distribution<> distOfsY(0, szY - 1);	// distribute results between  inclusive.
	std::uniform_real_distribution<> distSpeed(-1, 1);		// distribute results between  inclusive.

	UINT64 dog = ar.size() * (UINT64)10;
	for(size_t j = 0; j < voffset->size(); j++){
		size_t ofsX, ofsY, ofs;
		while(true){
			ofsX = distOfsX(gen);
			ofsY = distOfsY(gen);
			ofs = ofsY * szX + ofsX;
			if(ar[ofs] == -1){
				ar[ofs] = j;
				(*voffset)[j] = ofs;
				//v[j].speed = float_2((float)distSpeed(gen), (float)distSpeed(gen));
				break;
			}
			if(dog-- == 0)
				return false;
		}
	}
	return false;
} // ////////////////////////////////////////////////////////////////////////////////////////////////////////
