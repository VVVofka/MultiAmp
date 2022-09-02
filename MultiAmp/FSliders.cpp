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

	double h = ((double)rctSliderBottom.top - rctSliderTop.top) / (vsliders.size() + 1);
	rctSlider.top = rctSliderTop.top - rctFrame.top;
	rctSlider.bottom = rctSliderTop.bottom - rctFrame.top;
	rctSlider.left = rctSliderTop.left - rctFrame.left;
	rctSlider.right = rctSliderTop.right - rctFrame.left;

	for(int j = 1; j < (int)(vsliders.size() - 1); j++){
		int d = (int)(h * (j + 1) + 0.5);
		rctSlider.top = rctSliderTop.top + d - rctFrame.top;
		rctSlider.bottom = rctSliderTop.bottom + d - rctFrame.top;
		vsliders[j] = new CSliderCtrl();
		vsliders[j]->Create(sliderTop->GetStyle(), rctSlider, frame, 188999 + 2 + j);
	}
	for(size_t j = 0; j < vsliders.size(); j++){
		vsliders[j]->SetRange(fmin, fmax, FALSE);
		vsliders[j]->SetPos(vkoefs->at(j));
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
	size_t oldsize = vkoefs->size();
	std::vector<std::pair<double, double>> vold(oldsize);
	std::vector<std::pair<double, double>> vnew(newsize);

	for(size_t j = 0; j < oldsize; j++){
		vold[j].first = j / (oldsize - 1.0);
		vold[j].second = vsliders[j - 1]->GetPos();
	}
	for(size_t j = 0; j < newsize; j++)
		vnew[j].first = j / (newsize - 1.0);

	for(size_t j = 1; j < newsize - 1; j++){
		for(size_t i = 0; i < oldsize; i++){
			if(vnew[j].first >= vold[i].first){
				std::pair<double, double> oldleft = vold[i];
				std::pair<double, double> oldright = vold[i >= oldsize - 1 ? oldsize - 1 : i + 1];
				double k = (vnew[j].first - oldleft.first) / (oldright.first - oldleft.first);
				vnew[j].second = oldleft.second + k * (oldright.second - oldleft.second);
			}
		}
	}
	vkoefs->resize(newsize);
	for(size_t j = 0; j < vkoefs->size(); j++)
		vkoefs->at(j) = lround(vnew[j].second);
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
