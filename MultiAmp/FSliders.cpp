#include "pch.h"
#include "FSliders.h"
#include <array>
#include <utility>
#include <string>
#include <locale.h>

FSliders::~FSliders(){
	for(size_t j = 0; j < vsl.size(); j++)
		if(vsl[j] != NULL)
			delete vsl[j];
} // /////////////////////////////////////////////////////////////////////////
void FSliders::activate(CWnd* grp, CSliderCtrl* slider_top, CEdit* edit_top, 
	CSliderCtrl* slider_bottom, CEdit* edit_bottom, std::vector<float>* v_k){
	vk = v_k;
	frame = grp;
	exampleSliderTop = slider_top;
	exampleEditTop = edit_top;
	exampleSliderBottom = slider_bottom;
	exampleEditBottom = edit_bottom;
	activate();
} // /////////////////////////////////////////////////////////////////////////////////////////
void FSliders::activate(){
	exampleSliderTop->SetBuddy(exampleEditTop);
	exampleSliderBottom->SetBuddy(exampleEditBottom);
	CRect rctGrp;
	frame->GetClientRect(rctGrp);

	int sz = int(vk->size());
	vsl.clear();
	vsl.resize(sz - 2);
	double heigh = (rctGrp.Height() * (1 - shifthtop - shifthbottom)) / (sz + (sz + 1.0) * kgaph);
	double heighT = heigh * (1 + kgaph);
	double top = shifthtop * rctGrp.Height() + heigh * kgaph;

	double width = (1 - 2 * kgapw) * rctGrp.Width();
	int left = (int)(kgapw * rctGrp.Width());
	int right = (int)((1 - kgapw) * rctGrp.Width());

	CRect rctEdit, rctSlider;
	exampleEditTop->GetClientRect(rctEdit);
	exampleSliderTop->GetClientRect(rctSlider);
	setMinMax();
	exampleSliderTop->SetRange((int)(fmin * kslayer), (int)(fmax * kslayer), TRUE);
	exampleSliderTop->SetPos((int)(vk->at(0) * kslayer));
	for(int j = 0; j < vsl.size(); j++){
		rctSlider = CRect(rctEdit.Width(), (int)(1.5 + top + j * heighT), rctGrp.Width() - left, (int)(0.5 + top + (j + 2.0) * heighT));
		vsl[j] = new CSliderCtrl();
		vsl[j]->Create(exampleSliderTop->GetStyle(), rctSlider, frame, 188999 + 2 + j);
		vsl[j]->SetRange((int)(fmin * kslayer), (int)(fmax * kslayer), TRUE);
		vsl[j]->SetPos((int)(vk->at(j + 1) * kslayer));
	}
	exampleSliderTop->SetRange((int)(fmin * kslayer), (int)(fmax * kslayer), TRUE);
	exampleSliderTop->SetPos((int)(vk->at(vk->size() - 1) * kslayer));
} // /////////////////////////////////////////////////////////////////////////
void FSliders::saveVK(size_t newsize){
	if(vk == NULL)
		return;
	if(newsize != vk->size())
		rescale(newsize);
	else{
		int pos = exampleSliderTop->GetPos();
		int min = exampleSliderTop->GetRangeMin();
		int max = exampleSliderTop->GetRangeMax();
		double k = ((double)pos - min) / ((double)max - min);
		vk->at(0) = (float)(fmin + fmax * k);
		for(size_t j = 0; j < vsl.size(); j++){
			int pos = vsl[j]->GetPos();
			int min = vsl[j]->GetRangeMin();
			int max = vsl[j]->GetRangeMax();
			double k = ((double)pos - min) / ((double)max - min);
			vk->at(j + 1) = (float)(fmin + fmax * k);
		}
		pos = exampleSliderTop->GetPos();
		min = exampleSliderTop->GetRangeMin();
		max = exampleSliderTop->GetRangeMax();
		k = ((double)pos - min) / ((double)max - min);
		vk->at(vk->size()-1) = (float)(fmin + fmax * k);
	}
	activate();
} // /////////////////////////////////////////////////////////////////////////
void FSliders::rescale(size_t newsize){
	size_t oldsize = vk->size();
	std::vector<std::pair<double, double>> vold(oldsize);
	std::vector<std::pair<double, double>> vnew(newsize);

	for(size_t j = 0; j < oldsize; j++)
		vold[j] = std::pair<double, double>(j / (oldsize - 1.0), vsl[j]->GetPos() / (double)kslayer);
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
	vk->resize(newsize);
	for(size_t j = 0; j < vk->size(); j++)
		vk->at(j) = (float)vnew[j].second;
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
	double val_top = getF(exampleEditTop);
	double val_bot = getF(exampleEditBottom);
	fmin = __min(val_top, val_bot);
	fmax = __max(val_top, val_bot);
} // ///////////////////////////////////////////////////////////////////////////
