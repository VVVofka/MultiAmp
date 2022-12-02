#include "pch.h"
#include "CppUnitTest.h"
#include "..\OptsTinyLib\structAll.h"
#include "..\AMPEngine2Lib\AMPEngine2Lib.h"
#include "..\AMPEngine2Lib\Engine\EngineDbg.h"
#include <string>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
namespace UTstEng2Lib{
	TEST_CLASS(UTstEng2LibF){
		structAll cfgall;
		structLaysCfg& lays = cfgall.lays;
		structMiscCfg& misc = cfgall.misc;
		structMasksCfg& masks = cfgall.masks;
		double tol = 0.000001;
public:
	UTstEng2LibF(){
		string sdata = "88 61 51 121 32 49 70 63 42 33 21 34 47 12 38 24 113 65 20 8 111 11 97 90 75 114 74 115 44 103 79 52 58 96 41 36 98";
		size_t scr_cnt = cfgall.data.fill_v(sdata);
		Assert::AreEqual(size_t(37), scr_cnt, L"scr_cnt");
		Assert::AreEqual(size_t(37), cfgall.data.v.size(), L"cfgall.data.v.size()");
		Assert::AreEqual(size_t(88), cfgall.data.v[0], L" cfgall.data.v[0]");
		Assert::AreEqual(size_t(98), cfgall.data.v[scr_cnt - 1], L" cfgall.data.v[scr_cnt-1]");
		string sfmask = "6576544378812312000100000000000000000040000000000000000000000000000000000800000000000000000000000002000000006000000000000000222000000000000020000000008004000000000000000000000000000000880800000000000000000000000040440000000006660000000000006666444488882222";
		cfgall.masks.setf(sfmask);
	} // //////////////////////////////////////////////////////////////////////////////
	TEST_METHOD(MinProcess){
		byCPU(0, 0);	//	Hereeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
	} // //////////////////////////////////////////////////////////////////////////////
	TEST_METHOD(ProcessA){
		byCPU(0, 0);
		byCPU(0, 1);
		byCPU(1, 0);
		byCPU(0, 2);
		byCPU(1, 1);
		byCPU(2, 0);

		// restrict cpu
		byCPU(3, 0);
		byCPU(2, 1);

		// restrict mt
		byCPU(0, 3);
		byCPU(1, 2);

		// restrict mt & cpu
		byCPU(5, 5);
	} // ////////////////////////////////////////////////////////////
	TEST_METHOD(ProcessA_1Pass){
		byCPU_A1(0, 0);
		byCPU_A1(0, 1);
		byCPU_A1(1, 0);
		byCPU_A1(0, 2);
		byCPU_A1(1, 1);
		byCPU_A1(2, 0);

		// restrict cpu
		byCPU_A1(3, 0);
		byCPU_A1(2, 1);

		// restrict mt
		byCPU_A1(0, 3);
		byCPU_A1(1, 2);

		// restrict mt & cpu
		byCPU_A1(5, 5);
	} // ////////////////////////////////////////////////////////////
private:
	void byCPU(size_t one, size_t mt){
		Logger::WriteMessage((" one:" + std::to_string(one) + " mt:" + std::to_string(mt)).c_str());

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

		misc.cntForStop = 1;
		misc.curRndSeed = 12345;

		//def:		0001011101111111
		masks.seta("0001011101111111");

		eng2::runEngine2Lib(&cfgall);

		vector<vector<int>>& va = EngineDbg::va;
		Assert::AreEqual(14, va[1][0], L"va 1 0");
		Assert::AreEqual(2, va[1][1], L"va 1 1");
		Assert::AreEqual(4, va[1][16], L"va 1 16");
		Assert::AreEqual(15, va[1][23], L"va 1 23");
		Assert::AreEqual(8, va[1][24], L"va 1 24");
		Assert::AreEqual(0, va[1][31], L"va 1 31");

		// for MaskA[1] = 1
		Assert::AreEqual(1, va[1][12], L"va maskA1 1 12");
		Assert::AreEqual(1, va[1][14], L"va maskA1 1 14");
		Assert::AreEqual(1, va[1][15], L"va maskA1 1 15");
		Assert::AreEqual(1, va[1][18], L"va maskA1 1 18");

		Assert::AreEqual(1, va[2][0], L"va 2 0");		// for MaskA[1] = 1
		Assert::AreEqual(10, va[2][1], L"va 2 1");
		Assert::AreEqual(0, va[2][2], L"va 2 2");
		Assert::AreEqual(3, va[2][3], L"va 2 3");
		Assert::AreEqual(0, va[2][4], L"va 2 4");
		Assert::AreEqual(4, va[2][5], L"va 2 5");
		Assert::AreEqual(4, va[2][6], L"va 2 6");
		Assert::AreEqual(3, va[2][7], L"va 2 7");

		vector<vector<float_2>>& vf = EngineDbg::vf;
		Assert::AreEqual(14, va[1][0], L"vf 1 0");

	} // ////////////////////////////////////////////////////////////
	 // eq void byCPU(size_t one, size_t mt), but Mask[1] = 1
	void byCPU_A1(size_t one, size_t mt){
		Logger::WriteMessage((" one:" + std::to_string(one) + " mt:" + std::to_string(mt)).c_str());

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

		misc.cntForStop = 1;
		misc.curRndSeed = 12345;

		//def:		0001011101111111
		masks.seta("0101011101111111");

		eng2::runEngine2Lib(&cfgall);

		auto& va = EngineDbg::va;
		Assert::AreEqual(14, va[1][0], L"va 1 0");
		Assert::AreEqual(2, va[1][1], L"va 1 1");
		Assert::AreEqual(4, va[1][16], L"va 1 16");
		Assert::AreEqual(15, va[1][23], L"va 1 23");
		Assert::AreEqual(8, va[1][24], L"va 1 24");
		Assert::AreEqual(0, va[1][31], L"va 1 31");

		// for MaskA[1] = 1
		Assert::AreEqual(1, va[1][12], L"va maskA1 1 12");
		Assert::AreEqual(1, va[1][14], L"va maskA1 1 14");
		Assert::AreEqual(1, va[1][15], L"va maskA1 1 15");
		Assert::AreEqual(1, va[1][18], L"va maskA1 1 18");

		Assert::AreEqual(1, va[2][0], L"va 2 0");
		Assert::AreEqual(10, va[2][1], L"va 2 1");
		Assert::AreEqual(4, va[2][2], L"va 2 2");	// MaskA[1] = 1
		Assert::AreEqual(15, va[2][3], L"va 2 3");	// MaskA[1] = 1
		Assert::AreEqual(0, va[2][4], L"va 2 4");
		Assert::AreEqual(5, va[2][5], L"va 2 5");	// MaskA[1] = 1
		Assert::AreEqual(4, va[2][6], L"va 2 6");
		Assert::AreEqual(3, va[2][7], L"va 2 7");
	} // ////////////////////////////////////////////////////////////
	}; // #####################################################################
} // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
