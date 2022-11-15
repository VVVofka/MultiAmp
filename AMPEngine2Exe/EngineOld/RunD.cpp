#include "RunD.h"

void RunD::Run(const array<DrQuadro, 2>& srcd,
			   array<DrQuadro, 2>& dstd,
			   const array<int, 2>& dsta,
			   const array<FLT2, 1>& masksD){
	parallel_for_each(srcd.extent, [&srcd, &dstd, &dsta, &masksD](index<2> idx) restrict(amp){
		const INT2 src(idx);
		const INT2 dst = src * 2;

		const int y0 = dst.y;
		const int y1 = y0 + 1;
		const int x0 = dst.x;
		const int x1 = x0 + 1;

		const int tl = dsta[y0][x0];
		const int tr = dsta[y0][x1];
		const int bl = dsta[y1][x0];
		const int br = dsta[y1][x1];
		int nmask = 16 * ((tl & 1) + ((tr & 1) * 2) + ((bl & 1) * 4) + ((br & 1) * 8));

		const FLT2* srcitems = srcd[src.y][src.x].items;
		FLT2* dstitems = dstd[y0][x0].items;
		dstitems->set(srcitems->y + masksD[nmask].y, srcitems->x + masksD[nmask].x); nmask++;
		(++dstitems)->set(srcitems->y + masksD[nmask].y, srcitems->x + masksD[nmask].x); nmask++;
		(++dstitems)->set(srcitems->y + masksD[nmask].y, srcitems->x + masksD[nmask].x); nmask++;
		(++dstitems)->set(srcitems->y + masksD[nmask].y, srcitems->x + masksD[nmask].x); nmask++;

		srcitems++;
		dstitems = dstd[y0][x1].items;
		dstitems->set(srcitems->y + masksD[nmask].y, srcitems->x + masksD[nmask].x); nmask++;
		(++dstitems)->set(srcitems->y + masksD[nmask].y, srcitems->x + masksD[nmask].x); nmask++;
		(++dstitems)->set(srcitems->y + masksD[nmask].y, srcitems->x + masksD[nmask].x); nmask++;
		(++dstitems)->set(srcitems->y + masksD[nmask].y, srcitems->x + masksD[nmask].x); nmask++;

		srcitems++;
		dstitems = dstd[y1][x0].items;
		dstitems->set(srcitems->y + masksD[nmask].y, srcitems->x + masksD[nmask].x); nmask++;
		(++dstitems)->set(srcitems->y + masksD[nmask].y, srcitems->x + masksD[nmask].x); nmask++;
		(++dstitems)->set(srcitems->y + masksD[nmask].y, srcitems->x + masksD[nmask].x); nmask++;
		(++dstitems)->set(srcitems->y + masksD[nmask].y, srcitems->x + masksD[nmask].x); nmask++;

		srcitems++;
		dstitems = dstd[y1][x1].items;
		dstitems->set(srcitems->y + masksD[nmask].y, srcitems->x + masksD[nmask].x); nmask++;
		(++dstitems)->set(srcitems->y + masksD[nmask].y, srcitems->x + masksD[nmask].x); nmask++;
		(++dstitems)->set(srcitems->y + masksD[nmask].y, srcitems->x + masksD[nmask].x); nmask++;
		(++dstitems)->set(srcitems->y + masksD[nmask].y, srcitems->x + masksD[nmask].x);
	});
} // ///////////////////////////////////////////////////////////////////////////////////////////////
