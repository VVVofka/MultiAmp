#pragma once
#include <array>
#include <amp_graphics.h>

//#include "../Models/DirXY.h"

namespace executor{
	using namespace std;
	using namespace Concurrency::graphics;
	class Masks_f{
	public:
		std::array<float_2, 16 * 4> v;
		const concurrency::array<float_2, 2>* gv;	// amp maskF 16 * 4 float_2

		Masks_f();
		~Masks_f();

		void create(const vector<float>& val);
		void create(const vector<float_2>& val);
		void dump();

	private:
		void del_gvMaskF();
	}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
}