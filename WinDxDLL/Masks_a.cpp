#include "Masks_a.h"
#include "Utils.h"

Masks_a::Masks_a(){
	v = {0};
	gv = NULL;	// amp maskA
} // ///////////////////////////////////////////////////////////////////////
Masks_a::~Masks_a(){
	SAFE_DELETE(gv);
} // //////////////////////////////////////////////////////////////////////////
bool Masks_a::load(const std::vector<int>& mask_A){	//	16
	if(mask_A.size() != 16) return false;
	for(size_t j = 0; j < v.size(); j++)
		v[j] = mask_A[j];

	SAFE_DELETE(gv);
	gv = new concurrency::array<int, 1>((int)v.size(), v.data());
	return gv != NULL;
} // ///////////////////////////////////////////////////////////////////////////
