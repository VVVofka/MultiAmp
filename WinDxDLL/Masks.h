#pragma once
#ifdef MODEA

#include <cassert>
#include <string>
#include "Utils.h"
struct CellItem{
	INT2 dir;
	INT2 en;
	CellItem(int dirX = -2, int dirY = -2);
	void set(int dirX, int dirY);
	std::string dumpx(){ return dump(en.x, dir.x); }
	std::string dumpy(){ return dump(en.y, dir.y); }
	std::string dump(){ return dumpx() + dumpy(); }
	FLT2 getFLT2(){ return FLT2(getfloat(en.y, dir.y), getfloat(en.x, dir.x)); }
	// ///////////////////////////////////////////////////////////
	std::string dump(int in_en, int in_dir);
	float getfloat(int in_en, int in_dir);
	CellItem reflectHor();
	CellItem reflectVer();
	CellItem reflectDiag1();
	CellItem reflectDiag2();
private:
	static int b2i(int en, int dir);
}; // *************************************************************
struct Cell2D{
	int val = -1;
	CellItem dirs[4] = {};
	void setVal(int Val);
	std::string dump(int startpos);
	std::string dumpx(std::string delimet = ", ");
	std::string dumpy(std::string delimet = ", ");
	std::string Dump(std::string inp);
	void setDir(int nItem, int dirX, int dirY);
	Cell2D reflectHor();
	Cell2D reflectVer();
	Cell2D reflectDiag1();
	Cell2D reflectDiag2();
}; // ***********************************************************************

// 01
// 23
// 3210
// dirY dirX enY enX
struct Block2D2{
	Cell2D v[4] = {};
	Block2D2(int val3 = -1, int val2 = -1, int val1 = -1, int val0 = -1){
		v[0].setVal(val0);
		v[1].setVal(val1);
		v[2].setVal(val2);
		v[3].setVal(val3);
	} // /////////////////////////////////////////////////////////////////////
	std::string dump(std::string ret, std::string delim = " ");
	std::string dumpx(std::string ret, std::string delim = ", ");
	std::string dumpy(std::string ret, std::string delim = ", ");
	void Dump(std::string ret);
	void setDir(int nCell, int nItem, int dirX, int dirY);
	int A();
	Block2D2 reflectHor();
	Block2D2 reflectVer();
	Block2D2 reflectDiag1();
	Block2D2 reflectDiag2();
private:
}; // **************************************************************************

struct Blocks2D2{
	const FLT2 maskFLT2[9] = {FLT2(0,0),FLT2(-1,-1),FLT2(-1,0),FLT2(-1,1),FLT2(0,1),FLT2(1,1),FLT2(1,0),FLT2(1,-1),FLT2(0,-1)};
	static const int szA = 16;
	static const int szCells = 4;
	static const int szItems = 4;
	static const int szFLT = szA * szCells * szItems;
	FLT2 vin[szFLT];
	Block2D2 v[szA] = {};
	Blocks2D2(){setDefault();}

	FLT2* setDefault();
	void fromDirs(const int* dirs);
	void toDirs(int* dirs) const;
 // ////////////////////////////////////////////////////////////////////////////////////////////
	void Add(int index,
			 int dirx00, int diry00, int dirx01, int diry01, int dirx10, int diry10, int dirx11, int diry11,
			 int dirx02, int diry02, int dirx03, int diry03, int dirx12, int diry12, int dirx13, int diry13,
			 int dirx20, int diry20, int dirx21, int diry21, int dirx30, int diry30, int dirx31, int diry31,
			 int dirx22, int diry22, int dirx23, int diry23, int dirx32, int diry32, int dirx33, int diry33
	); // ///////////////////////////////////////////////////////////////////////////////////////////////
	std::string dump();
	void dumpx(std::string delim = ",");
	void dumpy(std::string delim = ",");
private:
}; // ***************************************************************************
#endif  // MODEA
