#pragma once
#include <cassert>
#include "Cell.h"
#include "Types.h"
#include <string>
namespace CppCLRWinformsProjekt{
using namespace System;
using namespace System::Windows;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Configuration;

private ref class Cell4{
	array<Cell^>^ cells = gcnew array<Cell^>(16);
public:
	Cell4(PictureBox^ parrent){
		for(int ncell = 0; ncell < 4; ncell++)
			for(int nitem = 0; nitem < 4; nitem++)
				cells[ncell * 4 + nitem] = gcnew Cell();
		int x0 = 1, y0 = 1;
		int x1 = parrent->Width / 2 + 3;
		int y1 = parrent->Height / 2 + 3;
		assert(parrent->Tag != nullptr);
		sval = parrent->Tag->ToString();
		width = parrent->Width;
		heigh = parrent->Height;
		parrent->Paint += gcnew PaintEventHandler(this, &Cell4::cell4_Paint);
		parrent->MouseDown += gcnew MouseEventHandler(this, &Cell4::cell4_MouseDown);
	}    // write to parrent.tag nmask ex:"0110"!
		 // ///////////////////////////////////////////////////////////////////////
	void Rotate(Cell4^ src){
		//src->dump();
		static const int matrpos[4] = {2,0,3,1};
		for(int ncell = 0; ncell < 4; ncell++){
			int ncellsrc = matrpos[ncell];
			for(int nitem = 0; nitem < 4; nitem++){
				int nitemsrc = matrpos[nitem];
				Cell^ csrc = src->getCell(ncellsrc, nitemsrc);
				Cell^ cdst = getCell(ncell, nitem);
				cdst->setRotate(csrc);
				//Diagnostics::Debug::Print("cell:{0} item:{1}", ncell, nitem);
				//dump();
			}
		}
	} // //////////////////////////////////////////////////////////////////////////////////////////////
	Cell^ getCell(int index){return cells[index];}
	Cell^ getCell(int ncell, int nitem){return cells[4 * ncell + nitem];}
	void setDir(int ncell, int nitem, int newdir){ cells[4 * ncell + nitem]->setDir(newdir);}
	// //////////////////////////////////////////////////////////////////////////////////////////////
	void dump(){
		Diagnostics::Debug::Print("{0}\t{1}\t\t{2}\t{3}", cells[0]->getDir(), cells[1]->getDir(), cells[4]->getDir(), cells[5]->getDir());
		Diagnostics::Debug::Print("{0}\t{1}\t\t{2}\t{3}", cells[2]->getDir(), cells[3]->getDir(), cells[6]->getDir(), cells[7]->getDir());
		Diagnostics::Debug::Print("");
		Diagnostics::Debug::Print("{0}\t{1}\t\t{2}\t{3}", cells[8]->getDir(), cells[9]->getDir(), cells[12]->getDir(), cells[13]->getDir());
		Diagnostics::Debug::Print("{0}\t{1}\t\t{2}\t{3}", cells[10]->getDir(), cells[11]->getDir(), cells[14]->getDir(), cells[15]->getDir());
	}
private:
	String^ sval;
	int width, heigh;
	// ///////////////////////////////////////////////////////////////////////
	System::Void cell4_Paint(System::Object^ sender, Forms::PaintEventArgs^ e){
		int shift = 1;
		Graphics^ g = e->Graphics;
		SolidBrush^ blueBrush = gcnew Drawing::SolidBrush(Color::LightSteelBlue); // Brushes::LightSteelBlue
		SolidBrush^ whiteBrush = gcnew Drawing::SolidBrush(Color::GhostWhite); // Brushes::LightSteelBlue
		Pen^ greyPen = gcnew Drawing::Pen(Color::DarkGray, 1); // Brushes::LightSteelBlue
		for(int j = 0; j < 4; j++){
			int x0 = (j & 1) * width / 2 + shift;
			int y0 = (j / 2) * heigh / 2 + shift;
			int w = width / 2 - 2 * shift;
			int h = heigh / 2 - 2 * shift;
			if(sval[3 - j] != '0'){
				g->FillRectangle(blueBrush, x0, y0, w, h);
			} else
				g->FillRectangle(whiteBrush, x0, y0, w, h);
			g->DrawRectangle(greyPen, x0, y0, w, h);
			cells[j * 4 + 0]->drawArrow(g, x0 + 1, y0 + 1, w / 2 - 1, h / 2 - 1);
			cells[j * 4 + 1]->drawArrow(g, x0 + 1 + w / 2, y0 + 1, w / 2 - 1, h / 2 - 1);
			cells[j * 4 + 2]->drawArrow(g, x0 + 1, y0 + 1 + h / 2, w / 2 - 1, h / 2 - 1);
			cells[j * 4 + 3]->drawArrow(g, x0 + 1 + w / 2, y0 + 1 + h / 2, w / 2 - 1, h / 2 - 1);
		}
		return System::Void();
		//g->DrawString("This is a diagonal line drawn on the control", fnt, Brushes::Blue, new Point(30, 30));
	}
	// //////////////////////////////////////////////////////////////////////////////////
	System::Void cell4_MouseDown(System::Object^ sender, Forms::MouseEventArgs^ e){
		const int x = e->X, y = e->Y;
		const int nxcell = (2 * x) / width;
		const int nycell = (2 * y) / heigh;
		const int ncell = 2 * nycell + nxcell;

		const int nxitem = (4 * x) / width;
		const int nyitem = (4 * y) / heigh;
		const int nitem = 2 * (nyitem % 2) + (nxitem % 2);

		const int shift = e->Button == MouseButtons::Left ? -1 : 1;
		cells[ncell * 4 + nitem]->nextDir(shift);
		PictureBox^ pb = (PictureBox^)sender;
		pb->Refresh();
		return System::Void();
	}
}; // ***************************************************************************
}
