#include "pch.h"
#include "FSliders.h"
#include <utility>
#include <string>
#include <locale.h>

void FSliders::create(CDialog* dlg, int id_grp, int id_slider_top, int id_edit_top, std::vector<int>* v_koefs, size_t size_capacity){
	this->dlg = dlg;
	frame = (CWnd*)dlg->GetDlgItem(id_grp);
	vsliders.resize(size_capacity);
	vedits.resize(size_capacity);
	vkoefs = v_koefs;
	for(size_t j = 0; j < size_capacity; j++){
		vsliders[j] = (CSliderCtrl*)dlg->GetDlgItem(id_slider_top + j);
		vedits[j] = (CEdit*)dlg->GetDlgItem(id_edit_top + j);
		//vsliders[j]->SetBuddy(vedits[j]);
	}
} // /////////////////////////////////////////////////////////////////////////
void FSliders::draw(){
	CRect rctFrame, rctSlider, rctSlider0;
	frame->GetWindowRect(rctFrame);
	vsliders[0]->GetWindowRect(rctSlider0);
	int height = rctSlider0.Height();

	rctSlider.right = rctFrame.right - rctFrame.left;
	rctSlider.left = rctSlider.right - rctSlider0.Width();

	double h = ((double)rctFrame.Height() - 1.5 * height) / (vkoefs->size() - 1);
	for(size_t j = 0; j < vkoefs->size(); j++){
		rctSlider.top = (LONG)(j * h);
		rctSlider.bottom = rctSlider.top + height;
		vsliders[j]->MoveWindow(rctSlider);
		//_RPT5(0, "%d\t %d * %d   %d * %d\n", j, rctSlider.left, rctSlider.top, rctSlider.right, rctSlider.bottom);
		vsliders[j]->SetRange(fmin, fmax, FALSE);
		vsliders[j]->SetPos(vkoefs->at(j));
		vsliders[j]->SetTicFreq(100);
		vedits[j]->SetWindowTextA(std::to_string(vkoefs->at(j)).c_str());
		vsliders[j]->ShowWindow(SW_SHOWNORMAL);
		vedits[j]->ShowWindow(SW_SHOWNORMAL);
		vsliders[j]->SetBuddy(vedits[j]);
	}
	for(size_t j = vkoefs->size(); j < vsliders.size(); j++){
		vsliders[j]->ShowWindow(SW_HIDE);
		vedits[j]->ShowWindow(SW_HIDE);
	}
} // /////////////////////////////////////////////////////////////////////////
void FSliders::saveVK(size_t newsize){
	if(vkoefs == NULL)
		return;
	if(newsize != vkoefs->size())
		rescale(newsize);
	else{
		for(size_t j = 0; j < vkoefs->size(); j++)
			vkoefs->at(j) = vsliders[j]->GetPos();
	}
	draw();	
} // /////////////////////////////////////////////////////////////////////////
void FSliders::rescale(size_t newsize){
	struct xy{ double x, y; };

	size_t oldsize = vkoefs->size();
	std::vector<xy> vold(oldsize);
	std::vector<xy> vnew(newsize);

	for(size_t j = 0; j < oldsize; j++){
		vold[j].x = j / (oldsize - 1.0);
		vold[j].y = vsliders[j]->GetPos();
	}
	for(size_t j = 0; j < newsize; j++)
		vnew[j].x = j / (newsize - 1.0);

	for(size_t j = 1; j < newsize - 1; j++){
		for(size_t i = 0; i < oldsize; i++){
			if(vnew[j].x >= vold[i].x){
				xy& oldleft = vold[i];
				xy& oldright = vold[i >= oldsize - 1 ? oldsize - 1 : i + 1];
				double k = (vnew[j].x - oldleft.x) / (oldright.x - oldleft.x);
				vnew[j].y = oldleft.y + k * (oldright.y - oldleft.y);
			}
		}
	}
	vnew[0].y = vold[0].y;
	vnew[newsize - 1].y = vold[oldsize - 1].y;

	vkoefs->resize(newsize);
	for(size_t j = 0; j < vkoefs->size(); j++)
		vkoefs->at(j) = lround(vnew[j].y);
} // ////////////////////////////////////////////////////////////////////////
bool FSliders::hscroll(HWND hwnd){
	for(size_t j = 0; j < vkoefs->size(); j++){
		if(vsliders[j]->m_hWnd == hwnd){
			vedits[j]->SetWindowTextA(std::to_string(vsliders[j]->GetPos()).c_str());
			return true;
		}
	}
	return false;
} // /////////////////////////////////////////////////////////////////////////
