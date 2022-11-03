#include "pch.h"
#include "CppUnitTest.h"
//#include "../WinDxDLL/myRnd.h"
#include "../WinDxDLL/OneLine0.h"
#include <array>
#include <algorithm>
#pragma warning(disable : 4996)
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UTstWinDll{
	TEST_CLASS(UTstOneLine){
public:

	TEST_METHOD(fillScreenPoints){
		OneLine0 oneline0;
		std::vector<size_t> vin;
		std::vector<Vertex2D> vout;
		const INT2 sz(8, 8);
		vin.push_back(0 + 5 * sz.x);
		vin.push_back(5 + 3 * sz.x);
		vin.push_back(6 + 3 * sz.x);
		vin.push_back(5 + 4 * sz.x);
		vin.push_back(6 + 4 * sz.x);
		vin.push_back(6 + 5 * sz.x);
		vin.push_back(7 + 6 * sz.x);
		oneline0.Create(sz.x, sz.y, &vin);
		model.fillScreenPoints(vin, vout, sz);
		Assert::AreEqual(-0.6666666666f, vout[0].Pos.y, 0.0001f, L"0y");

		Assert::AreEqual(0.75f, vout[1].Pos.x, 0.0001f, L"1x");
		Assert::AreEqual(0.6666666666f, vout[1].Pos.y, 0.0001f, L"1y");

		Assert::AreEqual(0.25f, vout[2].Pos.x, 0.0001f, L"2x");
		Assert::AreEqual(0.0f, vout[2].Pos.y, 0.0001f, L"2y");

		Assert::AreEqual(-0.75f, vout[3].Pos.x, 0.0001f, L"3x");
		Assert::AreEqual(0.6666666666f, vout[3].Pos.y, 0.0001f, L"3y");
		//Logger::WriteMessage(s.c_str());
	} // //////////////////////////////////////////////////////////////////////
	};
}
