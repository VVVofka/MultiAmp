#include "pch.h"
#include "CppUnitTest.h"
#include "../WinDxDLL/myRnd.h"
#include <array>
#include <algorithm>
#pragma warning(disable : 4996)
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UTstWinDll{
	TEST_CLASS(UTstWinDll){
public:

	TEST_METHOD(Rnd1){
		LehmerRng rnd(0);
		FILE* f = fopen("rnd.txt", "w");
		for(int j = 0; j < 1000; j++){
			uint32_t r = rnd.rand();
			std::string s = std::to_string(r) + " ";
			fputs(s.c_str(), f);
		}
		fclose(f);
		//remove("rnd.txt");
	} // //////////////////////////////////////////////////////////////////////
	TEST_METHOD(RndsetUpper6){
		LehmerRng rnd;
		rnd.setUpper(6);
		std::array<uint64_t, 6> v = {0};
		uint64_t cnttest = 60000000;
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
		Assert::IsTrue(k < 0.2);
		remove("rnd.txt");
	} // //////////////////////////////////////////////////////////////////////
	TEST_METHOD(Rnd6){
		LehmerRng rnd;
		const size_t sz = 2;
		std::array<uint64_t, sz> v = {0};
		uint64_t cnttest = sz * 10000000;
		for(uint64_t j = 0; j < cnttest; j++){
			uint32_t r = rnd.rand(sz);
			Assert::IsTrue(r < sz);
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
