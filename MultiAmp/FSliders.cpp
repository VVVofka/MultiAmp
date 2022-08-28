#include "pch.h"
#include "FSliders.h"
#include <array>
#include <utility>
#include <string>
#include <format>

FSliders::~FSliders(){
	for(size_t j = 1; j < vsl.size()-1; j++)
		if(vsl[j] != NULL)
			delete vsl[j];
} // /////////////////////////////////////////////////////////////////////////
void FSliders::activate(CWnd* grp, CSliderCtrl* example_slider, CEdit* example_edit, std::vector<float>* v_k){
	vk = v_k;
	frame = grp;
	exampleSlider = example_slider;
	exampleEdit = example_edit;
	activate();
} // /////////////////////////////////////////////////////////////////////////////////////////
void FSliders::activate(){
	//if (exampleSlider == NULL)
	exampleSlider->SetBuddy(exampleEdit);
	return;
	exampleSlider->ShowWindow(SW_SHOW);
	exampleEdit->ShowWindow(SW_SHOW);
	CRect rctGrp;
	frame->GetClientRect(rctGrp);

	int sz = int(vk->size());
	vsl.clear();
	vsl.resize(sz);
	vsl[0] = & sl
	double heigh = (rctGrp.Height() * (1 - shifthtop - shifthbottom)) / (sz + (sz + 1.0) * kgaph);
	double heighT = heigh * (1 + kgaph);
	double top = shifthtop * rctGrp.Height() + heigh * kgaph;

	double width = (1 - 2 * kgapw) * rctGrp.Width();
	int left = (int)(kgapw * rctGrp.Width());
	int right = (int)((1 - kgapw) * rctGrp.Width());

	CRect rctEdit, rctSlider;
	exampleEdit->GetClientRect(rctEdit);
	CRect rctSlider(rctEdit.Width(), (int)(0.5 + top), rctGrp.Width() - left, (int)(0.5 + top + heighT));
	CRect rctEdit(left, (int)(0.5 + top), rctEdit.Width(), (int)(0.5 + top + heighT));
	for(int j = 1; j < sz - 1; j++){
		rctSlider = CRect(rctEdit.Width(), (int)(0.5 + top + j * heighT), rctGrp.Width() - left, (int)(0.5 + top + (j + 1.0) * heighT));
		vsl[j] = new CSliderCtrl();
		vsl[j]->Create(exampleSlider->GetStyle(), rctSlider, frame, 188999 + 1 + j);
		vsl[j]->SetRange((int)(fmin * kslayer), (int)(fmax * kslayer), TRUE);
		vsl[j]->SetPos((int)(vk->at(j) * kslayer));

//		CRect rctEdit(left, (int)(0.5 + top + j * heighT), rctEdit.Width(), (int)(0.5 + top + (j + 1.0) * heighT));
		vsl[j].edit = new CEdit();
		vsl[j].edit->Create(exampleEdit->GetStyle(), rctEdit, frame, 189999 + 1 + j);
		vsl[j].edit->SetFont(exampleEdit->GetFont());
		//vsl[j].edit->Number(exampleEdit->GetFont());

		char buf[8];
		int res = snprintf(buf, sizeof(buf), "%.2f", vk->at(j));
		vsl[j].edit->SetWindowTextA(buf);
	}
	exampleSlider->ShowWindow(SW_HIDE);
	exampleEdit->ShowWindow(SW_HIDE);
} // /////////////////////////////////////////////////////////////////////////
void FSliders::saveVK(size_t newsize){
	if(vk == NULL)
		return;
	if(newsize != vk->size())
		rescale(newsize);
	else
		for(size_t j = 0; j < vsl.size(); j++){
			int pos = vsl[j].slider->GetPos();
			int min = vsl[j].slider->GetRangeMin();
			int max = vsl[j].slider->GetRangeMax();
			double k = ((double)pos - min) / ((double)max - min);
			vk->at(j) = (float)(fmin + fmax * k);
		}
	activate();
} // /////////////////////////////////////////////////////////////////////////
void FSliders::rescale(size_t newsize){
	size_t oldsize = vk->size();
	std::vector<std::pair<double, double>> vold(oldsize);
	std::vector<std::pair<double, double>> vnew(newsize);

	for(size_t j = 0; j < oldsize; j++)
		vold[j] = std::pair<double, double>(j / (oldsize - 1.0), vsl[j].slider->GetPos() / (double)kslayer);
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
