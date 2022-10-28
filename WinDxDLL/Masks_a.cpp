#include "Masks_a.h"
namespace executor {
	using namespace std;
	Masks_a::Masks_a() {
		v = { 0 };
		gv = NULL;	// amp maskA
	} // ///////////////////////////////////////////////////////////////////////
	Masks_a::~Masks_a() {
		deleteMaskA();
	} // //////////////////////////////////////////////////////////////////////////
	bool Masks_a::load(const vector<int>& mask_A) {	//	16
		if(mask_A.size() != 16) return false;
		for (size_t j = 0; j < v.size(); j++)
			v[j] = mask_A[j];

		deleteMaskA();
		gv = new concurrency::array<int, 1>((int)v.size(), v.data());
		return gv != NULL;
	} // ///////////////////////////////////////////////////////////////////////////
	void Masks_a::deleteMaskA() {
		if (gv != NULL)
			delete gv;
	} // ///////////////////////////////////////////////////////////////////////////

}