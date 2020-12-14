#include "pch.h"
#ifdef MODEA

#include "Masks.h"

FLT2* Blocks2D2::setDefault(){  // x, y !!!
	Add(0b0000,
		-1, -1, 0, -1, 0, -1, 1, -1,
		-1, 0, -1, -1, 1, -1, 1, 0,  // 0 0

		-1, 0, -1, 1, 1, 1, 1, 0,  // 0 0
		-1, 1, 0, 1, 0, 1, 1, 1
	);
	Add(0b0001,
		0, 0, 0, 0, 0, 1, -1, 1,
		0, 0, 0, 0, 0, 0, -1, 1,  // 1 0

		1, 0, 0, 0, 0, 0, -1, 0,  // 0 0
		1, -1, 1, -1, 0, -1, -1, -1
	);
	Add(0b0011,
		-1, 0, -1, 0, 1, 0, 1, 0,
		-1, 0, -1, 0, 1, 0, 1, 0,   // 1 1

		-1, -1, -1, 0, 1, 0, 1, -1,   // 0 0
		-1, -1, -1, -1, 1, -1, 1, -1
		/*
		0, 0,  0, 0,   0, 0,  0, 0,
		0, 0,  0, 0,   0, 0,  0, 0,   // 1 1

		-1, 0, -1, 0,   1, 0,  1, 0,   // 0 0
		-1,-1, -1,-1,   1,-1,  1,-1
		*/
	);
	Add(0b0110,
		1, 1, 1, -1, 1, 0, 1, -1,
		-1, 1, 1, 1, 1, -1, 0, -1,   // 0 1

		0, 1, -1, 1, -1, -1, 1, -1,   // 1 0
		-1, 1, -1, 0, -1, 1, -1, -1
		/*
		1, 1,  1,-1,   0, 0,  0, 0,
		-1, 1,  1, 1,   0, 0,  0, 0,   // 0 1

		0, 0,  0, 0,  -1,-1,  1,-1,   // 1 0
		0, 0,  0, 0,  -1, 1, -1,-1
		*/
	);
	Add(0b0111,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,   // 1 1

		0, 0, 0, 0, 1, 1, 1, -1,   // 1 0
		0, 0, 0, 0, -1, 1, 1, 1
	);
	Add(0b1111,
		-1, -1, 0, -1, 0, -1, 1, -1,
		-1, 0, -1, -1, 1, -1, 1, 0,  // 1 1

		-1, 0, -1, 1, 1, 1, 1, 0,  // 1 1
		-1, 1, 0, 1, 0, 1, 1, 1
	);
	/*
	Blocks2D2(){  // x, y !!!
	Add(0b0000,
	-1,-1,  0,-1,   0,-1,  1,-1,
	-1, 0, -1,-1,   1,-1,  1, 0,  // 0 0

	-1, 0, -1, 1,   1, 1,  1, 0,  // 0 0
	-1, 1,  0, 1,   0, 1,  1, 1
	);
	Add(0b0001,
	0, 0,  0, 0,   0, 1, -1, 1,
	0, 0,  0, 0,   0, 0, -1, 1,  // 1 0

	1, 0,  0, 0,   0, 0, -1, 0,  // 0 0
	1,-1,  1,-1,   0,-1, -1,-1
	);
	Add(0b0011,
	0, 0,  0, 0,   0, 0,  0, 0,
	0, 0,  0, 0,   0, 0,  0, 0,   // 1 1

	-1, 0, -1, 0,   1, 0,  1, 0,   // 0 0
	-1,-1, -1,-1,   1,-1,  1,-1
	);
	Add(0b0110,
	1, 1,  1,-1,   0, 0,  0, 0,
	-1, 1,  1, 1,   0, 0,  0, 0,   // 0 1

	0, 0,  0, 0,  -1,-1,  1,-1,   // 1 0
	0, 0,  0, 0,  -1, 1, -1,-1
	);
	Add(0b0111,
	0, 0,  0, 0,   0, 0,  0, 0,
	0, 0,  0, 0,   0, 0,  0, 0,   // 1 1

	0, 0,  0, 0,   1, 1,  1,-1,   // 1 0
	0, 0,  0, 0,  -1, 1,  1, 1
	);
	Add(0b1111,
	-1,-1,  0,-1,   0,-1,  1,-1,
	-1, 0, -1,-1,   1,-1,  1, 0,  // 1 1

	-1, 0, -1, 1,   1, 1,  1, 0,  // 1 1
	-1, 1,  0, 1,   0, 1,  1, 1
	);
	*/
	for(int a = 0, j = 0; a < szA; a++)
		for(int ncell = 0; ncell < szCells; ncell++)
			for(int nitem = 0; nitem < szItems; nitem++)
				vin[j++] = v[a].v[ncell].dirs[nitem].getFLT2();
	return vin;
} // ///////////////////////////////////////////////////////////////////////////////////////////////
void Blocks2D2::fromDirs(const int* dirs){
	for(int a = 0; a < 16 * 4 * 4; a++)
		vin[a] = maskFLT2[dirs[a]];
}// ////////////////////////////////////////////////////////////////////////////////////////////
void Blocks2D2::toDirs(int* dirs) const{
	for(int n = 0, d; n < szFLT; n++){
		for(d = 0; d <= 8; d++){
			FLT2 f1 = vin[n].sign();
			FLT2 f2 = maskFLT2[d].sign();
			if(f1 == f2)
				break;
		}
		assert(d >= 0 && d <= 8);
		dirs[n] = d;
	}
} // ////////////////////////////////////////////////////////////////////////////////////////////////////
void Blocks2D2::Add(int index,
  int dirx00, int diry00, int dirx01, int diry01, int dirx10, int diry10, int dirx11, int diry11, 
  int dirx02, int diry02, int dirx03, int diry03, int dirx12, int diry12, int dirx13, int diry13, 
  int dirx20, int diry20, int dirx21, int diry21, int dirx30, int diry30, int dirx31, int diry31, 
  int dirx22, int diry22, int dirx23, int diry23, int dirx32, int diry32, int dirx33, int diry33){
	v[index] = Block2D2((index >> 3) & 1, (index >> 2) & 1, (index >> 1) & 1, index & 1);
	int nItem = 0, nCell = 0;
	v[index].setDir(nCell, nItem++, dirx00, diry00);
	v[index].setDir(nCell, nItem++, dirx01, diry01);
	v[index].setDir(nCell, nItem++, dirx02, diry02);
	v[index].setDir(nCell++, nItem, dirx03, diry03);
	nItem = 0;
	v[index].setDir(nCell, nItem++, dirx10, diry10);
	v[index].setDir(nCell, nItem++, dirx11, diry11);
	v[index].setDir(nCell, nItem++, dirx12, diry12);
	v[index].setDir(nCell++, nItem, dirx13, diry13);
	nItem = 0;
	v[index].setDir(nCell, nItem++, dirx20, diry20);
	v[index].setDir(nCell, nItem++, dirx21, diry21);
	v[index].setDir(nCell, nItem++, dirx22, diry22);
	v[index].setDir(nCell++, nItem, dirx23, diry23);
	nItem = 0;
	v[index].setDir(nCell, nItem++, dirx30, diry30);
	v[index].setDir(nCell, nItem++, dirx31, diry31);
	v[index].setDir(nCell, nItem++, dirx32, diry32);
	v[index].setDir(nCell++, nItem, dirx33, diry33);
	//v[index].Dump("Main:");

	Block2D2 hor = v[index].reflectHor();
	Block2D2 ver = v[index].reflectVer();
	Block2D2 dgl1 = v[index].reflectDiag1();
	Block2D2 dgl2 = v[index].reflectDiag2();

	Block2D2 vmodifs[7] = {hor, ver, dgl1, dgl2,
		hor.reflectDiag2(), ver.reflectDiag2(), dgl1.reflectDiag2()};

	for(int m = 0; m < 7; m++){
		int a = vmodifs[m].A();
		v[a] = vmodifs[m];
		//v[a].Dump(" add \tm:" + std::to_string(m) + " \ta:");
	}
} // ///////////////////////////////////////////////////////////////////////////////////////////////
std::string Blocks2D2::dump(){
	std::string ret;
	for(int j = 0; j < 16; j++){
		ret += "\n" + v[j].dump(std::to_string(j) + ":\n");
	}
	return ret;
} // ////////////////////////////////////////////////////////////////////////////////
void Blocks2D2::dumpx(std::string delim){
	for(int j = 0; j < 16; j++){
		std::string s = v[j].dumpx("", delim) + (j == 15 ? std::string("\n") : delim);
		_RPT2(0, "\n%s", s.c_str());
	}
} // ////////////////////////////////////////////////////////////////////////////////
void Blocks2D2::dumpy(std::string delim){
	for(int j = 0; j < 16; j++){
		std::string s = v[j].dumpy("", delim) + (j == 15 ? std::string("\n") : delim);
		_RPT2(0, "\n%s", s.c_str());
	}
}  // ///////////////////////////////////////////////////////////////////////////////////////////////
std::string Block2D2::dump(std::string ret, std::string delim){
	ret += v[0].dump(0) + delim + v[1].dump(0) + "\n";
	ret += v[0].dump(2) + delim + v[1].dump(2) + "\n\n";
	ret += v[2].dump(0) + delim + v[3].dump(0) + "\n";
	ret += v[2].dump(2) + delim + v[3].dump(2) + "\n";
	return ret;
} // ////////////////////////////////////////////////////////////////////////////////
std::string Block2D2::dumpx(std::string ret, std::string delim){
	ret += v[0].dumpx(delim) + delim;
	ret += v[1].dumpx(delim) + delim;
	ret += v[2].dumpx(delim) + delim;
	ret += v[3].dumpx(delim);
	return ret;
} // ////////////////////////////////////////////////////////////////////////////////
std::string Block2D2::dumpy(std::string ret, std::string delim){
	ret += v[0].dumpy(delim) + delim;
	ret += v[1].dumpy(delim) + delim;
	ret += v[2].dumpy(delim) + delim;
	ret += v[3].dumpy(delim);
	return ret;
}  // ///////////////////////////////////////////////////////////////////////////////////////////////
void Block2D2::Dump(std::string ret){
	ret += std::to_string(A()) + "\n";
	_RPT0(0, dump(ret).c_str());
} // ///////////////////////////////////////////////////////////////////////////////////////////////
int Block2D2::A(){
	int ret = 0;
	for(int j = 0; j < 4; j++){
		if(v[j].val != 0)
			ret += (1 << j);
	}
	assert(ret < 16);
	return ret;
} // /////////////////////////////////////////////////////////////////////////////
void Block2D2::setDir(int nCell, int nItem, int dirX, int dirY){
	assert(nCell < 4);
	if(nCell < 4)
		v[nCell].setDir(nItem, dirX, dirY);
} // /////////////////////////////////////////////////////////////////////////
Block2D2 Block2D2::reflectHor(){
	Block2D2 ret;
	ret.v[0] = v[1].reflectHor(); ret.v[0].setVal(v[1].val);
	ret.v[1] = v[0].reflectHor(); ret.v[1].setVal(v[0].val);
	ret.v[2] = v[3].reflectHor(); ret.v[2].setVal(v[3].val);
	ret.v[3] = v[2].reflectHor(); ret.v[3].setVal(v[2].val);
	return ret;
} // //////////////////////////////////////////////////////////////////////////////
Block2D2 Block2D2::reflectVer(){
	Block2D2 ret;
	ret.v[0] = v[2].reflectVer();  ret.v[0].setVal(v[2].val);
	ret.v[1] = v[3].reflectVer();  ret.v[1].setVal(v[3].val);
	ret.v[2] = v[0].reflectVer();  ret.v[2].setVal(v[0].val);
	ret.v[3] = v[1].reflectVer();  ret.v[3].setVal(v[1].val);
	return ret;
}// //////////////////////////////////////////////////////////////////////////////
Block2D2 Block2D2::reflectDiag1(){ // axe Top,Left -> Bottom,Right
	Block2D2 ret;
	ret.v[0] = v[0].reflectDiag1();  ret.v[0].setVal(v[0].val);
	ret.v[1] = v[2].reflectDiag1();  ret.v[1].setVal(v[2].val);
	ret.v[2] = v[1].reflectDiag1();  ret.v[2].setVal(v[1].val);
	ret.v[3] = v[3].reflectDiag1();  ret.v[3].setVal(v[3].val);
	return ret;
} // //////////////////////////////////////////////////////////////////////////////
Block2D2 Block2D2::reflectDiag2(){ // axe Top,Right -> Bottom,Left
	Block2D2 ret;
	ret.v[0] = v[3].reflectDiag2();  ret.v[0].setVal(v[3].val);
	ret.v[1] = v[1].reflectDiag2();  ret.v[1].setVal(v[1].val);
	ret.v[2] = v[2].reflectDiag2();  ret.v[2].setVal(v[2].val);
	ret.v[3] = v[0].reflectDiag2();  ret.v[3].setVal(v[0].val);
	return ret;
} // ///////////////////////////////////////////////////////////////////////////////////////////////

void Cell2D::setVal(int Val){
	assert(Val == 0 || Val == 1 || Val == -1);
	val = Val;
}// //////////////////////////////////////////////////////////////
std::string Cell2D::dump(int startpos){
	std::string ret;
	ret = dirs[startpos + 0].dump() + " " + dirs[startpos + 1].dump();
	return ret;
} // /////////////////////////////////////////////////////////////////
std::string Cell2D::dumpx(std::string delimet){
	std::string ret = dirs[0].dumpx() + delimet;
	ret += dirs[1].dumpx() + delimet;
	ret += dirs[2].dumpx() + delimet;
	return ret + dirs[3].dumpx();
} // /////////////////////////////////////////////////////////////////
std::string Cell2D::dumpy(std::string delimet){
	std::string ret = dirs[0].dumpy() + delimet;
	ret += dirs[1].dumpy() + delimet;
	ret += dirs[2].dumpy() + delimet;
	return ret + dirs[3].dumpy();
} // /////////////////////////////////////////////////////////////////
std::string Cell2D::Dump(std::string inp){
	std::string ret = inp;
	ret += dirs[0].dump() + " " + dirs[1].dump() + "\n";
	ret += dirs[2].dump() + " " + dirs[3].dump() + "\n";
	_RPT0(0, ret.c_str());
	return ret;
} // ///////////////////////////////////////////////////////////////////////////////////////////////
void Cell2D::setDir(int nItem, int dirX, int dirY){
	assert(nItem < 4);
	if(nItem < 4)
		dirs[nItem].set(dirX, dirY);
} // /////////////////////////////////////////////////////////////
Cell2D Cell2D::reflectHor(){
	Cell2D ret;
	ret.setVal(val);
	ret.dirs[1] = dirs[0].reflectHor();
	ret.dirs[0] = dirs[1].reflectHor();
	ret.dirs[3] = dirs[2].reflectHor();
	ret.dirs[2] = dirs[3].reflectHor();
	return ret;
} // //////////////////////////////////////////////////////////////////////////////
Cell2D Cell2D::reflectVer(){
	Cell2D ret;
	ret.setVal(val);
	ret.dirs[2] = dirs[0].reflectVer();
	ret.dirs[3] = dirs[1].reflectVer();
	ret.dirs[0] = dirs[2].reflectVer();
	ret.dirs[1] = dirs[3].reflectVer();
	return ret;
} // //////////////////////////////////////////////////////////////////////////////
Cell2D Cell2D::reflectDiag1(){ // axe Top,Left -> Bottom,Right
	Cell2D ret;
	ret.setVal(val);
	ret.dirs[0] = dirs[0].reflectDiag1();
	ret.dirs[2] = dirs[1].reflectDiag1();
	ret.dirs[1] = dirs[2].reflectDiag1();
	ret.dirs[3] = dirs[3].reflectDiag1();
	return ret;
} // //////////////////////////////////////////////////////////////////////////////
Cell2D Cell2D::reflectDiag2(){ // axe Top,Right -> Bottom,Left
	Cell2D ret;
	ret.setVal(val);
	assert(ret.val >= 0);
	ret.dirs[3] = dirs[0].reflectDiag2();
	ret.dirs[1] = dirs[1].reflectDiag2();
	ret.dirs[2] = dirs[2].reflectDiag2();
	ret.dirs[0] = dirs[3].reflectDiag2();
	return ret;
} // ///////////////////////////////////////////////////////////////////////////////////////////////
CellItem::CellItem(int dirX, int dirY){
	if(dirX == -1)
		dir.x = 0, en.x = 1;
	else if(dirX == 0)
		dir.x = 0, en.x = 0;
	else if(dirX == 1)
		dir.x = 1, en.x = 1;
	else
		dir.x = -1, en.x = -1;

	if(dirY == -1)
		dir.y = 0, en.y = 1;
	else if(dirY == 0)
		dir.y = 0, en.y = 0;
	else if(dirY == 1)
		dir.y = 1, en.y = 1;
	else
		dir.y = -1, en.y = -1;
} // /////////////////////////////////////////////////////////////////
void CellItem::set(int dirX, int dirY){
	assert(dirX >= -1 && dirX <= 1);
	if(dirX < 0){
		dir.x = 0, en.x = 1;
	} else if(dirX > 0){
		dir.x = 1, en.x = 1;
	} else{
		dir.x = 0, en.x = 0;
	}

	assert(dirY >= -1 && dirY <= 1);
	if(dirY < 0){
		dir.y = 0, en.y = 1;
	} else if(dirY > 0){
		dir.y = 1, en.y = 1;
	} else{
		dir.y = 0, en.y = 0;
	}
} // ///////////////////////////////////////////////////////////////////////////////////////////////
std::string CellItem::dump(int in_en, int in_dir){
	if(in_en == 1)
		return in_dir == 0 ? "-1" : "+1";
	return in_dir == 0 ? "-0" : "+0";
} // //////////////////////////////////////////////////////////////////
float CellItem::getfloat(int in_en, int in_dir){
	if(in_en == 1)
		return in_dir == 0 ? -1.f : +1.f;
	return 0.f;
} // ///////////////////////////////////////////////////////////////////////////////////////////////
CellItem CellItem::reflectHor(){
	int x = b2i(en.x, dir.x);
	int y = b2i(en.y, dir.y);
	return CellItem(-x, y);
} // //////////////////////////////////////////////////////////////////////////////
CellItem CellItem::reflectVer(){
	int x = b2i(en.x, dir.x);
	int y = b2i(en.y, dir.y);
	return CellItem(x, -y);
} // //////////////////////////////////////////////////////////////////////////////
CellItem CellItem::reflectDiag1(){ // axe Top,Left -> Bottom,Right
	int x = b2i(en.x, dir.x);
	int y = b2i(en.y, dir.y);
	return CellItem(y, x);
} // //////////////////////////////////////////////////////////////////////////////
CellItem CellItem::reflectDiag2(){ // axe Top,Right -> Bottom,Left
	int x = b2i(en.x, dir.x);
	int y = b2i(en.y, dir.y);
	return CellItem(-y, -x);
} // ///////////////////////////////////////////////////////////////////////////////////////////////
int CellItem::b2i(int en, int dir){
	assert((en == 0 || en == 1) && (dir == 0 || dir == 1));
	if(en == 0) return 0;
	if(dir == 0) return -1;
	return 1;
} // ///////////////////////////////////////////////////////////////////////////////////////////////
#endif  // MODEA
