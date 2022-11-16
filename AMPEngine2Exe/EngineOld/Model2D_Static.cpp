#include "Model2D_Static.h"

Vertex2D Model2D_Static::norm(int curpos, const INT2& sizes){
	const int iy = curpos / sizes.x;
	const float y = NORMAL_TO_AREA(iy, sizes.y);
	const int ix = curpos % sizes.x;
	const float x = NORMAL_TO_AREA(ix, sizes.x);
	return Vertex2D(y, x);
} // /////////////////////////////////////////////////////////////////////////////////
void Model2D_Static::fillScreenPoints(const std::vector<size_t>& vin, std::vector<Vertex2D>& vout, const INT2& sz){
	vout.resize(vin.size());
	for(size_t j = 0; j < vin.size(); j++){
		const Vertex2D vert2 = norm((int)vin[j], sz);
		vout[j] = vert2;
	}
} // /////////////////////////////////////////////////////////////////////////////////
void Model2D_Static::setConsole(){
#pragma warning(push)
#pragma warning(disable : 4996)
	if(::GetConsoleWindow() == NULL){
		if(::AllocConsole()){
			(void)freopen("CONIN$", "r", stdin);
			(void)freopen("CONOUT$", "w", stdout);
			(void)freopen("CONOUT$", "w", stderr);
			SetFocus(::GetConsoleWindow());
		}
	}
#pragma warning(pop)
} // ///////////////////////////////////////////////////////////////////////////
