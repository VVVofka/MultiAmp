#include "pch.h"
#include "DlgDataData.h"

void DlgDataData::create(size_t sz_x, size_t sz_y, vector<size_t>* in_v, string* in_sigma, string* in_seed){
	szX = sz_x, szY = sz_y;
	voffset = in_v;
	sigma = in_sigma;
	seed = in_seed;
} // ////////////////////////////////////////////////////////////////////////////////////////////////////////
bool DlgDataData::generRndFlat(size_t new_count){
	voffset->resize(new_count);
	std::vector<int> ar(szX * szY, -1);

	std::random_device rd;   // non-deterministic generator
	std::mt19937 gen(rd());  // to seed mersenne twister.
	std::uniform_int_distribution<> distOfsX(0, szX - 1);	// distribute results between  inclusive.
	std::uniform_int_distribution<> distOfsY(0, szY - 1);	// distribute results between  inclusive.
	//std::uniform_real_distribution<> distSpeed(-1, 1);		// distribute results between  inclusive.

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
				break;
			}
			if(dog-- == 0)
				return false;
		}
	}
	return true;
} // ////////////////////////////////////////////////////////////////////////////////////////////////////////
bool DlgDataData::generRndNorm(size_t new_count, float sigma){
	voffset->resize(new_count);
	std::vector<int> ar(szX * szY, -1);

	const double Mean = 0;	// мат ож
	const double Sigma = (double)sigma;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::normal_distribution<> distNorm(Mean, Sigma);
	UINT64 dog = ar.size() * (UINT64)10;
	double boundx = szX * 0.5;
	double boundy = szY * 0.5;
	for(size_t j = 0; j < voffset->size(); j++){
		size_t ofsX, ofsY, ofs;
		while(true){
			if(dog-- == 0)
				return false;
			double rndx = distNorm(gen);	//-3*sigma .. +3*sigma
			if(fabs(rndx) >= 0.5) continue;
			double rndy = distNorm(gen);
			if(fabs(rndy) >= 0.5) continue;
			rndx += 0.5;	// 0...1
			rndy += 0.5;
			ofsX = size_t(rndx * szX);
			ofsY = size_t(rndy * szY);
			ofs = ofsY * szX + ofsX;
			if(ar[ofs] == -1){
				ar[ofs] = j;
				(*voffset)[j] = ofs;
				break;
			}
		}
	}
	return true;
} // ////////////////////////////////////////////////////////////////////////////////////////////////////////