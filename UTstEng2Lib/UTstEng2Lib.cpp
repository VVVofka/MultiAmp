#include "pch.h"
#include "CppUnitTest.h"
#include "..\OptsTinyLib\structAll.h"
#include "..\AMPEngine2Lib\AMPEngine2Lib.h"
#include "..\AMPEngine2Lib\Engine\EngineDbg.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UTstEng2Lib{
	TEST_CLASS(UTstEng2LibA){
		structAll cfgall;
		structLaysCfg& lays = cfgall.lays;
		structMiscCfg& misc = cfgall.misc;
		structMasksCfg& masks = cfgall.masks;

		double tol = 0.000001;
public:
	TEST_METHOD(TestMethod1){
		byCPU(2, 0);
		byCPU(0, 0);
		byCPU(0, 1);
		byCPU(1, 0);
		byCPU(0, 2);
		byCPU(1, 1);
		byCPU(0, 3);
		byCPU(1, 2);
		byCPU(2, 1);
		byCPU(3, 0);
	} // ////////////////////////////////////////////////////////////
private:
	void byCPU(size_t one, size_t mt){
		Logger::WriteMessage((" one:" + std::to_string(one) + " mt:" + std::to_string(mt)).c_str());
		string sdata = "88 61 51 121 32 49 70 63 42 33 21 34 47 12 38 24 113 65 20 8 111 11 97 90 75 114 74 115 44 103 79 52 58 96 41 36 98";
		size_t scr_cnt = cfgall.data.fill_v(sdata);
		Assert::AreEqual(size_t(37), scr_cnt, L"scr_cnt");
		Assert::AreEqual(size_t(88), cfgall.data.v[0], L" cfgall.data.v[0]");
		Assert::AreEqual(size_t(98), cfgall.data.v[scr_cnt - 1], L" cfgall.data.v[scr_cnt-1]");

		size_t cntlays = lays.setConfig(2, 1, one, mt, "0.91  0.72  0,43");
		Assert::AreEqual(size_t(4), cntlays, L"cntlays");
		Assert::AreEqual(cntlays, lays.cntlays, L"lays.cntlays");
		Assert::AreEqual(size_t(16), lays.sizeX(0), L"lays.sizeX(0)");
		Assert::AreEqual(size_t(8), lays.sizeY(0), L"lays.sizeY(0)");
		Assert::AreEqual(size_t(8), lays.sizeX(1), L"lays.sizeX(1)");
		Assert::AreEqual(size_t(4), lays.sizeY(1), L"lays.sizeY(1)");
		Assert::AreEqual(size_t(4), lays.sizeX(2), L"lays.sizeX(2)");
		Assert::AreEqual(size_t(2), lays.sizeY(2), L"lays.sizeY(2)");
		Assert::AreEqual(size_t(2), lays.sizeX(3), L"lays.sizeX(3)");
		Assert::AreEqual(size_t(1), lays.sizeY(3), L"lays.sizeY(3)");
		Assert::AreEqual(0.91, lays.koefsF[0], tol, L"lays.koefsF[0]");
		Assert::AreEqual(0.72, lays.koefsF[1], tol, L"lays.koefsF[1]");
		Assert::AreEqual(0.43, lays.koefsF[2], tol, L"lays.koefsF[2]");
		//Assert::IsTrue(lays.isGPU(0), L"lays.isGPU(0)");
		//Assert::IsFalse(lays.isGPU(1), L"lays.isGPU(1)");
		//Assert::IsFalse(lays.isGPU(2), L"lays.isGPU(2)");
		//Assert::IsFalse(lays.isGPU(3), L"lays.isGPU(3)");
		//Assert::IsFalse(lays.isMT(0), L"lays.isMT(0)");
		//Assert::IsTrue(lays.isMT(1), L"lays.isMT(1)");
		//Assert::IsFalse(lays.isMT(2), L"lays.isMT(2)");
		//Assert::IsFalse(lays.isMT(3), L"lays.isMT(3)");

		misc.cntForStop = 1;
		misc.curRndSeed = 12345;

		masks.seta("0001011101111111");

		eng2::runEngine2Lib(&cfgall);

		auto& va = EngineDbg::va;
		Assert::AreEqual(14, va[1][0], L"va 1 0");
		Assert::AreEqual(2, va[1][1], L"va 1 1");
		Assert::AreEqual(4, va[1][16], L"va 1 16");
		Assert::AreEqual(15, va[1][23], L"va 1 23");
		Assert::AreEqual(8, va[1][24], L"va 1 24");
		Assert::AreEqual(0, va[1][31], L"va 1 31");

		Assert::AreEqual(1, va[2][0], L"va 2 0");
		Assert::AreEqual(10, va[2][1], L"va 2 1");
		Assert::AreEqual(0, va[2][2], L"va 2 2");
		Assert::AreEqual(3, va[2][3], L"va 2 3");
		Assert::AreEqual(0, va[2][4], L"va 2 4");
		Assert::AreEqual(4, va[2][5], L"va 2 5");
		Assert::AreEqual(4, va[2][6], L"va 2 6");
		Assert::AreEqual(3, va[2][7], L"va 2 7");

		//auto z = eng2::mdx.cfg_all;	// TODO: restore mdx.CleanupDevice() in wndAMP.cpp::MainLoop() !!!

	} // ////////////////////////////////////////////////////////////
	}; // #####################################################################
} // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
