#pragma once
#include <array>
#include <amp_graphics.h>
namespace executor {
	using namespace std;
	using namespace Concurrency::graphics;

	class Masks_a {
	public:
		std::array<int, 16> v;
		const concurrency::array<int, 1>* gv;

		Masks_a();
		~Masks_a();
		
		bool load(const vector<int>& mask_A);	// 16
	private:
		void deleteMaskA();
	};
}