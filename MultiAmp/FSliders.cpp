#include "pch.h"
#include "FSliders.h"
#include <utility>
#include <string>
#include <locale.h>

void FSliders::create(CDialog* dlg, int id_grp, int id_slider_top, int id_edit_top, size_t size_visible, size_t size_capacity){
	this->dlg = dlg;
	frame = (CWnd*)dlg->GetDlgItem(id_grp);
	vsliders.resize(size_capacity);
	vedits.resize(size_capacity);
	for(size_t j = 0; j < size_capacity; j++){
		vsliders[j] = (CSliderCtrl*)dlg->GetDlgItem(id_slider_top + j);
		vedits[j] = (CEdit*)dlg->GetDlgItem(id_edit_top + j);
		
		vsliders[j]->SetBuddy(vedits[j]);

		const int show_mode = j < size_visible ? SW_SHOWNORMAL : SW_HIDE;
		vsliders[j]->ShowWindow(show_mode);
		vedits[j]->ShowWindow(show_mode);
	}
	sliderTop = vsliders[0];
	editTop = vedits[0];

	szVisible = size_visible;
	if(szVisible == 0) 
		return;
	sliderBottom = vsliders[szVisible - 1];
} // /////////////////////////////////////////////////////////////////////////
void FSliders::draw(){
	CRect rctFrame, rctSlider, rctSliderTop, rctSliderBottom;
	frame->GetWindowRect(rctFrame);
	sliderTop->GetWindowRect(rctSliderTop);
	sliderBottom->GetWindowRect(rctSliderBottom);

	double h = ((double)rctSliderBottom.top - rctSliderTop.top) / (vsliders.size() - 1);
	rctSlider.top = rctSliderTop.top - rctFrame.top;
	rctSlider.bottom = rctSliderTop.bottom - rctFrame.top;
	rctSlider.left = rctSliderTop.left - rctFrame.left;
	rctSlider.right = rctSliderTop.right - rctFrame.left;

	CRect rctEdit;
	editTop->GetWindowRect(rctEdit);
	for(size_t j = 1; j < vedits.size(); j++){
		vedits[j] = new CEdit();
		vedits[j]->Create(editTop->GetStyle(), rctEdit, frame, 188999 + 2 + j + 100);
		vedits[j]->SetFont(editTop->GetFont());
	}
	for(int j = 1; j < (int)(vsliders.size() - 1); j++){
		int d = (int)(h * j + 0.5);
		rctSlider.top = rctSliderTop.top + d - rctFrame.top;
		rctSlider.bottom = rctSliderTop.bottom + d - rctFrame.top;
		vsliders[j] = new CSliderCtrl();
		vsliders[j]->Create(sliderTop->GetStyle(), rctSlider, frame, 188999 + 2 + j);
		vsliders[j]->SetBuddy(vedits[j]);
	}
	sliderBottom->SetBuddy(vedits[vedits.size() - 1]);

	for(size_t j = 0; j < vsliders.size(); j++){
		vsliders[j]->SetRange(fmin, fmax, TRUE);
		vsliders[j]->SetPos(vkoefs->at(j));
		vsliders[j]->SetTicFreq(100);
		vedits[j]->SetWindowTextA(std::to_string(vkoefs->at(j)).c_str());
	}
	vedits[vedits.size() - 1]->SetWindowTextA(std::to_string(vkoefs->at(vsliders.size() - 1)).c_str());
} // /////////////////////////////////////////////////////////////////////////
void FSliders::saveVK(size_t newsize){
	if(vkoefs == NULL)
		return;
	if(newsize != vkoefs->size())
		rescale(newsize);
	else{
		for(size_t j = 0; j < vsliders.size(); j++)
			vkoefs->at(j) = sliderTop->GetPos();
	}
	setElements();
} // /////////////////////////////////////////////////////////////////////////
void FSliders::setElements(){
	CRect rctFrame, rctSlider, rctSliderTop, rctSliderBottom;
	frame->GetWindowRect(rctFrame);
	sliderTop->GetWindowRect(rctSliderTop);
	sliderBottom->GetWindowRect(rctSliderBottom);

	double h = ((double)rctSliderBottom.top - rctSliderTop.top) / (vsliders.size() - 1);
	rctSlider.top = rctSliderTop.top - rctFrame.top;
	rctSlider.bottom = rctSliderTop.bottom - rctFrame.top;
	rctSlider.left = rctSliderTop.left - rctFrame.left;
	rctSlider.right = rctSliderTop.right - rctFrame.left;

	CRect rctEdit;
	editTop->GetWindowRect(rctEdit);
	for(size_t j = 1; j < vedits.size(); j++){
		vedits[j] = new CEdit();
		vedits[j]->Create(editTop->GetStyle(), rctEdit, frame, 188999 + 2 + j + 100);
		vedits[j]->SetFont(editTop->GetFont());
	}
	for(int j = 1; j < (int)(vsliders.size() - 1); j++){
		int d = (int)(h * j + 0.5);
		rctSlider.top = rctSliderTop.top + d - rctFrame.top;
		rctSlider.bottom = rctSliderTop.bottom + d - rctFrame.top;
		vsliders[j] = new CSliderCtrl();
		vsliders[j]->Create(sliderTop->GetStyle(), rctSlider, frame, 188999 + 2 + j);
		vsliders[j]->SetBuddy(vedits[j]);
	}
	sliderBottom->SetBuddy(vedits[vedits.size() - 1]);

	for(size_t j = 0; j < vsliders.size(); j++){
		vsliders[j]->SetRange(fmin, fmax, TRUE);
		vsliders[j]->SetPos(vkoefs->at(j));
		vsliders[j]->SetTicFreq(100);
		vedits[j]->SetWindowTextA(std::to_string(vkoefs->at(j)).c_str());
	}
	vedits[vedits.size() - 1]->SetWindowTextA(std::to_string(vkoefs->at(vsliders.size() - 1)).c_str());
} // /////////////////////////////////////////////////////////////////////////
void FSliders::rescale(size_t newsize){
	struct xy{ double x, y; };
	sliderBottom = vsliders[newsize - 1];

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
	CSliderCtrl* pslider = NULL;
	CEdit* pedit = NULL;
	for(size_t j = 0; j < vsliders.size(); j++){
		if(vsliders[j]->m_hWnd == hwnd){
			pslider = vsliders[j];
			pedit = vedits[j];
			break;
		}
	}
	if(pslider == NULL)
		return false;
	pedit->SetWindowTextA(std::to_string(pslider->GetPos()).c_str());
	return true;
} // /////////////////////////////////////////////////////////////////////////
