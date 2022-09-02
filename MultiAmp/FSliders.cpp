#include "pch.h"
#include "FSliders.h"
#include <array>
#include <utility>
#include <string>
#include <locale.h>

FSliders::~FSliders(){
	vslClear(0);
} // /////////////////////////////////////////////////////////////////////////
void FSliders::create(CWnd* grp, CSliderCtrl* slider_top, CEdit* edit_top,
	CSliderCtrl* slider_bottom, CEdit* edit_bottom, std::vector<float>* v_k){
	vkoefs = v_k;
	frame = grp;
	sliderTop = slider_top;
	editTop = edit_top;
	sliderBottom = slider_bottom;
	editBottom = edit_bottom;

	sliderTop->SetBuddy(editTop);
	sliderBottom->SetBuddy(editBottom);
} // /////////////////////////////////////////////////////////////////////////
void FSliders::activate(){
	vslClear(int(vkoefs->size()) - 2);

	CRect rctFrame, rctSlider, rctSliderTop, rctSliderBottom;
	sliderTop->GetWindowRect(rctSliderTop);
	sliderBottom->GetWindowRect(rctSliderBottom);
	frame->GetWindowRect(rctFrame);
	setMinMax();

	sliderTop->SetRange((int)(fmin * kslayer), (int)(fmax * kslayer), TRUE);
	sliderTop->SetPos((int)(vkoefs->at(0) * kslayer));

	sliderBottom->SetRange((int)(fmin * kslayer), (int)(fmax * kslayer), TRUE);
	sliderBottom->SetPos((int)(vkoefs->at(vkoefs->size() - 1) * kslayer));

	double h = ((double)rctSliderBottom.top - rctSliderTop.top) / (vsliders.size() + 1);
	rctSlider.top = rctSliderTop.top - rctFrame.top;
	rctSlider.bottom = rctSliderTop.bottom - rctFrame.top;
	rctSlider.left = rctSliderTop.left - rctFrame.left;
	rctSlider.right = rctSliderTop.right - rctFrame.left;
	for(int j = 0; j < (int)vsliders.size(); j++){
		int d = (int)(h * (j + 1) + 0.5);
		rctSlider.top = rctSliderTop.top + d - rctFrame.top;
		rctSlider.bottom = rctSliderTop.bottom + d - rctFrame.top;
		vsliders[j] = new CSliderCtrl();
		vsliders[j]->Create(sliderTop->GetStyle(), rctSlider, frame, 188999 + 2 + j);
		vsliders[j]->SetRange((int)(fmin * kslayer), (int)(fmax * kslayer), TRUE);
		vsliders[j]->SetPos((int)(vkoefs->at(j + 1) * kslayer));
	}
} // /////////////////////////////////////////////////////////////////////////
void FSliders::saveVK(size_t newsize){
	if(vkoefs == NULL)
		return;
	if(newsize != vkoefs->size())
		rescale(newsize);
	else{
		int pos = sliderTop->GetPos();
		int min = sliderTop->GetRangeMin();
		int max = sliderTop->GetRangeMax();
		double k = ((double)pos - min) / ((double)max - min);
		vkoefs->at(0) = (float)(fmin + fmax * k);
		for(size_t j = 0; j < vsliders.size(); j++){
			int pos = vsliders[j]->GetPos();
			int min = vsliders[j]->GetRangeMin();
			int max = vsliders[j]->GetRangeMax();
			double k = ((double)pos - min) / ((double)max - min);
			vkoefs->at(j + 1) = (float)(fmin + fmax * k);
		}
		pos = sliderTop->GetPos();
		min = sliderTop->GetRangeMin();
		max = sliderTop->GetRangeMax();
		k = ((double)pos - min) / ((double)max - min);
		vkoefs->at(vkoefs->size() - 1) = (float)(fmin + fmax * k);
	}
	activate();
} // /////////////////////////////////////////////////////////////////////////
void FSliders::rescale(size_t newsize){
	size_t oldsize = vkoefs->size();
	std::vector<std::pair<double, double>> vold(oldsize);
	std::vector<std::pair<double, double>> vnew(newsize);

	vold[0] = std::pair<double, double>(0, sliderTop->GetPos() / (double)kslayer);
	for(size_t j = 1; j < oldsize - 1; j++)
		vold[j] = std::pair<double, double>(j / (oldsize - 1.0), vsliders[j - 1]->GetPos() / (double)kslayer);
	vold[oldsize - 1] = std::pair<double, double>(oldsize / (oldsize - 1.0), sliderBottom->GetPos() / (double)kslayer);

	for(size_t j = 1; j < newsize - 1; j++)
		vnew[j] = std::pair<double, double>(j / (newsize - 1.0), 0);

	vnew[0] = vold[0];
	vnew[newsize - 1] = vold[oldsize - 1];
	for(size_t j = 1; j < newsize - 1; j++){
		for(size_t i = 0; i < oldsize; i++){
			if(vnew[j].first >= vold[i].first){
				std::pair<double, double> oldleft = vold[i];
				std::pair<double, double> oldright = vold[i >= oldsize - 1 ? oldsize - 1 : i + 1];
				double k = (vnew[j].first - oldleft.first) / (oldright.first - oldleft.first);
				double second = oldleft.second + k * (oldright.second - oldleft.second);
				vnew[j] = std::pair<double, double>(j / (newsize - 1.0), second);
			}
		}
	}
	vkoefs->resize(newsize);
	for(size_t j = 0; j < vkoefs->size(); j++)
		vkoefs->at(j) = (float)vnew[j].second;
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
void FSliders::setMinMax(){
	double val_top = getF(editTop);
	double val_bot = getF(editBottom);
	fmin = __min(val_top, val_bot);
	fmax = __max(val_top, val_bot);
	if(fmax - fmin < 1){
		double favg = (fmin + fmax) / 2;
		fmin = favg - 1.0;
		fmax = favg + 1.0;
	}
} // ///////////////////////////////////////////////////////////////////////////
void FSliders::vslClear(int new_size){
	for(size_t j = 0; j < vsliders.size(); j++)
		if(vsliders[j] != NULL)
			delete vsliders[j];
	vsliders.clear();
	if(new_size > 0){
		vsliders.resize(new_size);
		for(int j = 0; j < new_size; j++)
			vsliders[j] = NULL;
	}
} // ///////////////////////////////////////////////////////////////////////////
float FSliders::round2(float var){
	char str[40];
	sprintf_s(str, "%.2f", var);
	sscanf_s(str, "%f", &var);
	return var;
} // ///////////////////////////////////////////////////////////////////////////
