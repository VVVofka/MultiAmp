#include "pch.h"
#include "CppUnitTest.h"
#include "../WinDxDLL/myRnd.h"
#include "../WinDxDLL/Model2D.h"
#include "../WinDxDLL/mywnd.h"
#include <array>
#include <algorithm>
#pragma warning(disable : 4996)
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UTstWinDll{
	TEST_CLASS(UTstWinDll){
public:

	TEST_METHOD(fillScreenPoints){
		Model2D_Static model;
		std::vector<size_t> vin;
		std::vector<Vertex2D> vout;
		const INT2 sz(3, 4);
		vin.push_back(1);  // x=1 y=0
		vin.push_back(11); // x=3 y=2 (right bottom)
		vin.push_back(6);  // x=2 y=1
		vin.push_back(8);  // x=0 y=2 (left bottom)
		model.fillScreenPoints(vin, vout, sz);
		Assert::AreEqual(-0.25f, vout[0].Pos.x, 0.0001f, L"0x");
		Assert::AreEqual(-0.6666666666f, vout[0].Pos.y, 0.0001f, L"0y");

		Assert::AreEqual(0.75f, vout[1].Pos.x, 0.0001f, L"1x");
		Assert::AreEqual(0.6666666666f, vout[1].Pos.y, 0.0001f, L"1y");

		Assert::AreEqual(0.25f, vout[2].Pos.x, 0.0001f, L"2x");
		Assert::AreEqual(0.0f, vout[2].Pos.y, 0.0001f, L"2y");

		Assert::AreEqual(-0.75f, vout[3].Pos.x, 0.0001f, L"3x");
		Assert::AreEqual(0.6666666666f, vout[3].Pos.y, 0.0001f, L"3y");
	} // //////////////////////////////////////////////////////////////////////
	TEST_METHOD(RndsetUpper6){
		LehmerRng rnd;
		const size_t sz = 2;
		rnd.setUpper(sz);
		std::array<uint64_t, sz> v = {0};
		const uint64_t cnttest = sz * 10000000;
		for(uint64_t j = 0; j < cnttest; j++){
			uint32_t r = rnd.randk();
			Assert::IsTrue(r < v.size());
			v[r]++;
		}
		auto min = *std::min_element(v.begin(), v.end());
		auto max = *std::max_element(v.begin(), v.end());
		double k = 100 * ((max - min) / (cnttest / 6.0));
		std::string s = std::to_string(k) + "%: ";
		for(size_t j = 0; j < v.size(); j++)
			s += std::to_string(v[j]) + ' ';
		Logger::WriteMessage(s.c_str());
		Assert::IsTrue(k < 0.4);
	} // //////////////////////////////////////////////////////////////////////
	TEST_METHOD(Rnd6){
		LehmerRng rnd;
		const size_t sz = 2;
		std::array<uint64_t, sz> v = {0};
		const uint64_t cnttest = sz * 10000000;
		for(uint64_t j = 0; j < cnttest; j++){
			uint32_t r = rnd.rand(sz);
			Assert::IsTrue(r < v.size());
			v[r]++;
		}
		auto min = *std::min_element(v.begin(), v.end());
		auto max = *std::max_element(v.begin(), v.end());
		double k = 100 * ((max - min) / (cnttest / double(sz)));
		std::string s = std::to_string(k) + "%: ";
		for(size_t j = 0; j < sz; j++)
			s += std::to_string(v[j]) + ' ';
		Logger::WriteMessage(s.c_str());
		Assert::IsTrue(k < 0.2);
	} // //////////////////////////////////////////////////////////////////////
	};
}
