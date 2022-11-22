#pragma once
#include <array>
#include <amp_short_vectors.h>
using namespace Concurrency::graphics;	//	float_2

class structMasksCfg{
public:
	//structMasksCfg(){ seta("0001011101111111"); }
	// 0-none; 1-yes
	std::array<int, 16> va;
	void seta(const std::string& s);

	// 0145
	// 2367
	// 89CD
	// ABEF
	// 0-none; 1-up; 2-right+up; 3-right ... 8-left+up
	std::array<float_2, 16 * 4 * 4> vf;
	void setf(const std::string& s);

private:
	static float_2 char2float_2(const char ch);
}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@