#include "pch.h"
#include "CellsFillSym.h"

std::array<Direct, 16>& CellsFillSym::fill(size_t mask, const std::array<Direct, 16>* v_in){
	vin = v_in;
	switch(mask){
	case 0b0000:
	case 0b1111:
		w0();
		break;
	case 0b0001:
	case 0b1110:
		wslope();
		break;
	case 0b0011:
		wvert();
		break;
	case 0b0101:
		whoriz();
		break;
	case 0b1001:
		wdiag();
		break;

	default:
		assert(false);
		break;
	}
	return vout;
} // ///////////////////////////////////////////////////////////////////////////
void CellsFillSym::w0(){
	// quadro #0
	Direct actdir((*vin)[0]);	// active position
	vout[0] = actdir;			vIsEnabled[0] = true;
	vout[5] = actdir.vert();	vIsEnabled[5] = false;
	vout[15] = actdir.rise();	vIsEnabled[15] = false;
	vout[10] = actdir.vert();	vIsEnabled[10] = false;

	actdir = (*vin)[1];		// active position
	vout[1] = actdir;					vIsEnabled[1] = true;
	vout[4] = actdir.vert();			vIsEnabled[4] = false;
	vout[7] = actdir.vert().rise();		vIsEnabled[7] = false;
	vout[13] = actdir.rise();			vIsEnabled[13] = false;
	vout[14] = actdir.vert().horiz();	vIsEnabled[14] = false;
	vout[11] = actdir.horiz();			vIsEnabled[11] = false;
	vout[8] = actdir.vert().slope();	vIsEnabled[8] = false;
	vout[2] = actdir.slope();			vIsEnabled[2] = false;

	actdir = (*vin)[3];		// active position
	vout[3] = actdir;			vIsEnabled[3] = true;
	vout[6] = actdir.vert();	vIsEnabled[6] = false;
	vout[12] = actdir.rise();	vIsEnabled[12] = false;
	vout[9] = actdir.horiz();	vIsEnabled[9] = false;
} // ///////////////////////////////////////////////////////////////////////////
void CellsFillSym::wslope(){
	// quadro #0
	activ(0);
	slope(1, 2);
	activ(3);

	// quadro #1
	slope(4, 8);
	slope(5, 10);
	slope(6, 9);
	slope(7, 11);

	// quadro #3	
	activ(12);
	slope(13, 14);
	activ(15);
} // ///////////////////////////////////////////////////////////////////////////
void CellsFillSym::wvert(){
	// quadro #0
	vert(0, 5);	
	vert(1, 4);	
	vert(2, 7);	
	vert(3, 6);

	// quadro #2
	vert(8, 13);
	vert(9, 12);
	vert(10, 15);
	vert(11, 14);	
} // ///////////////////////////////////////////////////////////////////////////
void CellsFillSym::whoriz(){
	// quadro #0
	vert(0, 10);	
	vert(1, 11);	
	vert(2, 8);	
	vert(3, 9);

	// quadro #1
	vert(4, 14);
	vert(5, 15);
	vert(6, 12);
	vert(7, 13);	
} // ///////////////////////////////////////////////////////////////////////////
void CellsFillSym::wdiag(){
	// quadro #0
	rise(0, 10);	
	slope(1, 2);	
	rise(3, 12);
	rotate180(1, 14);

	// quadro #1
	rise(4, 7);
	slope(5, 10);
	slope(6, 9);
	rotate180(4, 11);
} // ///////////////////////////////////////////////////////////////////////////

void CellsFillSym::activ(int act){
	Direct actdir((*vin)[act]);		// active position
	vout[act] = actdir;				vIsEnabled[act] = true;
} // ///////////////////////////////////////////////////////////////////////////
void CellsFillSym::slope(int act, int pos){
	Direct actdir((*vin)[act]);		// active position
	vout[act] = actdir;				vIsEnabled[act] = true;
	vout[pos] = actdir.slope();		vIsEnabled[pos] = false;
} // //////////////////////////////////////////////////////////////////////////////
void CellsFillSym::rise(int act, int pos){
	Direct actdir((*vin)[act]);		// active position
	vout[act] = actdir;				vIsEnabled[act] = true;
	vout[pos] = actdir.rise();		vIsEnabled[pos] = false;
} // //////////////////////////////////////////////////////////////////////////////
void CellsFillSym::vert(int act, int pos){
	Direct actdir((*vin)[act]);		// active position
	vout[act] = actdir;				vIsEnabled[act] = true;
	vout[pos] = actdir.vert();		vIsEnabled[pos] = false;
} // //////////////////////////////////////////////////////////////////////////////
void CellsFillSym::horiz(int act, int pos){
	Direct actdir((*vin)[act]);		// active position
	vout[act] = actdir;				vIsEnabled[act] = true;
	vout[pos] = actdir.horiz();		vIsEnabled[pos] = false;
} // //////////////////////////////////////////////////////////////////////////////
void CellsFillSym::rotate180(int act, int pos){
	Direct actdir((*vin)[act]);		// active position
	vout[act] = actdir;					vIsEnabled[act] = true;
	vout[pos] = actdir.horiz().vert();	vIsEnabled[pos] = false;
} // //////////////////////////////////////////////////////////////////////////////