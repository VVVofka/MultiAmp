#include "OneLine0.h"

OneLine0::OneLine0(){} // //////////////////////////////////////////////////////////////////////
OneLine0::~OneLine0(){
	SAFE_DELETE(pscr);
} // //////////////////////////////////////////////////////////////////////
void OneLine0::Create(const size_t sz_x, const size_t sz_y, std::vector<size_t>* v_in_out){
	szx = sz_x, szy = sz_y, szall = szx * szy;
	szdata = v_in_out->size();
	pv = v_in_out;
	fill_vscr();
} // //////////////////////////////////////////////////////////////////////
void OneLine0::fill_vscr(){
	SAFE_DELETE(pscr);
	pscr = new Vertex2D[szdata];
	for(size_t j = 0; j < szdata; j++){
		const size_t pos = pv->at(j);
		const size_t x = pos % szx;
		pscr[j].Pos.x = NORMAL_TO_AREA(x, szx);
		const size_t y = pos / szx;
		pscr[j].Pos.y = NORMAL_TO_AREA(y, szy);
	}
} // //////////////////////////////////////////////////////////////////////

