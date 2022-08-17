#include "pch.h"
#include "CellsFillSym.h"

std::array<Direct, 16>& CellsFillSym::fill(size_t mask, const std::array<Direct, 16>& v_in){
	switch(mask){
	case 0:

		break;
	default:
		break;
	}
	return vout;
} // ///////////////////////////////////////////////////////////////////////////
void CellsFillSym::w0(const std::array<Direct, 16>& vin){
	Direct actdir(vin[0]);	// active position
	vout[0] = actdir;			vIsEnabled[0] = true;
	vout[5] = actdir.vert();	vIsEnabled[5] = false;
	vout[15] = actdir.rise();	vIsEnabled[15] = false;
	vout[10] = actdir.vert();	vIsEnabled[10] = false;

	actdir = vin[1];
	vout[1] = actdir;					vIsEnabled[1] = true;
	vout[4] = actdir.vert();			vIsEnabled[4] = false;
	vout[7] = actdir.vert().rise();		vIsEnabled[7] = false;
	vout[13] = actdir.rise();			vIsEnabled[13] = false;
	vout[14] = actdir.vert().horiz();	vIsEnabled[14] = false;
	vout[11] = actdir.horiz();			vIsEnabled[11] = false;
	vout[8] = actdir.vert().slope();	vIsEnabled[8] = false;
	vout[2] = actdir.slope();			vIsEnabled[2] = false;

	actdir = vin[3];
	vout[3] = actdir;			vIsEnabled[3] = true;
	vout[6] = actdir.vert();	vIsEnabled[6] = false;
	vout[12] = actdir.rise();	vIsEnabled[12] = false;
	vout[9] = actdir.horiz();	vIsEnabled[9] = false;
} // ///////////////////////////////////////////////////////////////////////////
