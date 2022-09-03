#include "pch.h"
#include "FSliders.h"
#include <utility>
#include <string>
#include <locale.h>

FSliders::~FSliders(){
	vslClear(0);
} // /////////////////////////////////////////////////////////////////////////
void FSliders::create(CWnd* grp, CSliderCtrl* slider_top, CEdit* edit_top,
	CSliderCtrl* slider_bottom, CEdit* edit_bottom, std::vector<int>* v_k){
	vkoefs = v_k;
	frame = grp;
	sliderTop = slider_top;
	editTop = edit_top;
	sliderBottom = slider_bottom;
	editBottom = edit_bottom;

	sliderTop->SetBuddy(editTop);
	sliderBottom->SetBuddy(editBottom);
} // /////////////////////////////////////////////////////////////////////////
void FSliders::makeSliders(){
	vslClear(vkoefs->size());

	CRect rctFrame, rctSlider, rctSliderTop, rctSliderBottom;
	sliderTop->GetWindowRect(rctSliderTop);
	sliderBottom->GetWindowRect(rctSliderBottom);
	frame->GetWindowRect(rctFrame);

	double h = ((double)rctSliderBottom.top - rctSliderTop.top) / (vsliders.size() - 1);
	rctSlider.top = rctSliderTop.top - rctFrame.top;
	rctSlider.bottom = rctSliderTop.bottom - rctFrame.top;
	rctSlider.left = rctSliderTop.left - rctFrame.left;
	rctSlider.right = rctSliderTop.right - rctFrame.left;

	for(int j = 1; j < (int)(vsliders.size() - 1); j++){
		int d = (int)(h * j + 0.5);
		rctSlider.top = rctSliderTop.top + d - rctFrame.top;
		rctSlider.bottom = rctSliderTop.bottom + d - rctFrame.top;
		vsliders[j] = new CSliderCtrl();
		vsliders[j]->Create(sliderTop->GetStyle(), rctSlider, frame, 188999 + 2 + j);
	}
	for(size_t j = 0; j < vsliders.size(); j++){
		vsliders[j]->SetRange(fmin, fmax, TRUE);
		vsliders[j]->SetPos(vkoefs->at(j));
		vsliders[j]->SetTicFreq(100);
		//vsliders[j]->SetFont()
	}
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
	makeSliders();
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
	vkoefs->resize(newsize);
	for(size_t j = 0; j < vkoefs->size(); j++)
		vkoefs->at(j) = lround(vnew[j].y);
} // ////////////////////////////////////////////////////////////////////////
double FSliders::getF(CEdit* edit){
	CString s;
	edit->GetWindowTextA(s);
	s.Replace(',', '.');
	_locale_t us = _create_locale(LC_NUMERIC, "en-US");
	double dbl = _atof_l((LPCSTR)s, us);
	s.Format("%.2f", dbl);
	edit->SetWindowTextA(s);
	return dbl;
} // ///////////////////////////////////////////////////////////////////////////
void FSliders::vslClear(int new_size){
	for(int j = 1; j < (int)vsliders.size() - 1; j++)
		if(vsliders[j] != NULL)
			delete vsliders[j];
	vsliders.clear();

	if(new_size > 1){
		vsliders.resize(new_size);
		vsliders[0] = sliderTop;
		for(int j = 1; j < new_size - 1; j++)
			vsliders[j] = NULL;
		vsliders[new_size - 1] = sliderBottom;
	}
} // ///////////////////////////////////////////////////////////////////////////
