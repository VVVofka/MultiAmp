#include "Masks_f.h"
namespace executor{
	Masks_f::Masks_f(){
		gv = NULL;
	} // //////////////////////////////////////////////////////////////////////
	Masks_f::~Masks_f(){
		del_gvMaskF();
	} // //////////////////////////////////////////////////////////////////////
	void Masks_f::create(const vector<float_2>& v_inp){
		_ASSERTE(v_inp.size() == v.size());
		for(size_t j = 0; j < v.size(); j++)
			v[j] = v_inp[j];
		del_gvMaskF();
		gv = new concurrency::array<float_2, 2>(16, 4, v.begin());
	} // //////////////////////////////////////////////////////////////////////
	void Masks_f::create(const vector<float>& v_inp){
		_ASSERTE(v_inp.size() == v.size() * 2);
		for(size_t j = 0; j < v.size(); j++){
			v[j].x = v_inp[j * 2];
			v[j].y = v_inp[j * 2 + 1];
		}
		del_gvMaskF();
		gv = new concurrency::array<float_2, 2>(16, 4, v.begin());
	} // //////////////////////////////////////////////////////////////////////
	void Masks_f::dump(){
		std::array<float_2, 16 * 4> vdump;
		concurrency::copy(*gv, vdump.begin());
		for(size_t j = 0; j < v.size() / 4; j++){
			printf("%d\n", (int)j);
			for(size_t i = 0; i < 4; i++){
				auto n = (i + 2) % 4;
				float_2 f2 = v[j * 4 + n];
				printf("%+.2f%+.2f ", f2.x, f2.y);
				if(n & 1)
					printf("\n");
			}
			printf("\n");
		}
	} // /////////////////////////////////////////////////////////////////////
	void Masks_f::del_gvMaskF(){
		if(gv != NULL)
			delete gv;
	} // //////////////////////////////////////////////////////////////////////
}