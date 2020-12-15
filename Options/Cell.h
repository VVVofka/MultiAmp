#pragma once
#include <cassert>
namespace CppCLRWinformsProjekt{
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace CppCLRWinformsProjekt;

private ref class Cell{
	int dir;
public:
	Cell(){dir = 0;	}
	void setDir(int Dir){dir = Dir;}
	int getDir(){return dir;}
	void nextDir(int shiftDir){dir = (dir + shiftDir + 9) % 9;}
	void setRotate(Cell^ src){
		//static const int matrdirs[9] = {0,7,8,1,2,3,4,5,6};
		static const int matrdirs[9] = {0,3,4,5,6,7,8,1,2};
		int srcdir = src->getDir();
		dir = matrdirs[srcdir];
	} // ///////////////////////////////////////////////////////////////////////
	void drawArrow(Graphics^ g, int x0, int y0, int width, int heigh){
		const int penwidth = (width + heigh) / 16;
		Pen^ pen = gcnew Pen(Color::Black, float(penwidth));
		const int gap = (width + heigh) / 16;
		const int lenarx = width / 4;
		const int lenary = heigh / 4;

		const int xc = x0 + width / 2;
		const int x1 = x0 + gap;
		const int x2 = x1 + int(lenarx * 1.5 + 0.5);
		const int x4 = x0 + width - gap;
		const int x3 = x4 - int(lenarx * 1.5 + 0.5);

		const int yc = y0 + heigh / 2;
		const int y1 = y0 + gap;
		const int y2 = y1 + int(lenary * 1.5 + 0.5);
		const int y4 = y0 + heigh - gap;
		const int y3 = y4 - int(lenary * 1.5 + 0.5);
		switch(dir){
			case 0:{
				Pen^ penc = gcnew Pen(Color::Black, 1);
				g->DrawEllipse(penc, xc - lenarx, yc - lenary, lenarx * 2, lenary * 2);
				break; }
			case 1:      //  tl
				g->DrawLine(pen, x1, y1, x4, y4);                  //  \           '
				g->DrawLine(pen, x1, y1 - penwidth / 2, x1, y2);   //  |
				g->DrawLine(pen, x1 - penwidth / 2, y1, x2, y1);   //  -
				break;
			case 2:     //  t
				g->DrawLine(pen, xc, y1, xc, y4);                 //  |
				g->DrawLine(pen, xc, y1, xc - lenarx, y2);        //  /
				g->DrawLine(pen, xc, y1, xc + lenarx, y2);        //  \           '
				break;
			case 3:     // tr
				g->DrawLine(pen, x4, y1, x1, y4);                  //  /
				g->DrawLine(pen, x4 + penwidth / 2, y1, x3, y1);   //  -
				g->DrawLine(pen, x4, y1 - penwidth / 2, x4, y2);   //  |
				break;
			case 4:    // r
				g->DrawLine(pen, x4, yc, x1, yc);
				g->DrawLine(pen, x4, yc, x3, yc - lenary);
				g->DrawLine(pen, x4, yc, x3, yc + lenary);
				break;
			case 5:  // br
				g->DrawLine(pen, x4, y4, x1, y1);                 //  \          '
				g->DrawLine(pen, x4, y4 + penwidth / 2, x4, y3);  //  |
				g->DrawLine(pen, x4 + penwidth / 2, y4, x3, y4);  //  _
				break;
			case 6:    // b
				g->DrawLine(pen, xc, y4, xc, y1);           // |
				g->DrawLine(pen, xc, y4, xc - lenarx, y3);  // \         '
				g->DrawLine(pen, xc, y4, xc + lenarx, y3);  // /
				break;
			case 7:    // br
				g->DrawLine(pen, x1, y4, x4, y1);                 //  /
				g->DrawLine(pen, x1 - penwidth / 2, y4, x2, y4);  //  -
				g->DrawLine(pen, x1, y4 + penwidth / 2, x1, y3);  //  |
				break;
			case 8:    // r
				g->DrawLine(pen, x1, yc, x4, yc);           //  -
				g->DrawLine(pen, x1, yc, x2, yc - lenary);  //  /
				g->DrawLine(pen, x1, yc, x2, yc + lenary);  //  \         '
				break;
			default:
				assert(dir <= 8 && dir > 0);
				break;
		}
	} // ///////////////////////////////////////////////////////////////////////
}; // *************************************************************************************
}
