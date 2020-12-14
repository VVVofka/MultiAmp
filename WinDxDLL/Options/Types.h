#pragma once
#include <cassert>
struct INTXY{
	int x = 0;
	int y = 0;
}; // *******************************************************************************************

struct Dir : public INTXY{
	void set(int nDirect){
		switch(nDirect){
			case 0:                     // none
				x = 0, y = 0; break;
			case 1:                     // top left
				x = -1, y = -1; break;
			case 2:                     // top
				x = 0, y = -1; break;
			case 3:                     // top right
				x = 1, y = -1; break;
			case 4:                     // right
				x = 1, y = 0; break;
			case 5:                     // bottom right
				x = 1, y = 1; break;
			case 6:                     // bottom
				x = 0, y = 1; break;
			case 7:                     // bottom left
				x = -1, y = 1; break;
			case 8:                     // left
				x = -1, y = 0; break;
			default:
				assert(nDirect <= 8); break;
		}
	}
}; // *******************************************************************************************

