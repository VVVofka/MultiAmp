#include "pch.h"
#include "FSliders.h"
#include <array>
#include <utility>

FSliders::FSliders() {
} // /////////////////////////////////////////////////////////////////////////
FSliders::~FSliders() {
	for (size_t j = 0; j < vsl.size(); j++)
		delete vsl[j];
} // /////////////////////////////////////////////////////////////////////////
void FSliders::activate(CButton* grp, CSliderCtrl* Example, std::vector<double>* v_k) {
	vk = v_k;
	frame = grp;
	example = Example;
	activate();
} // /////////////////////////////////////////////////////////////////////////////////////////
void FSliders::activate() {
	//CButton* grp = (CButton*)dlg->GetDlgItem(IDC_LAYSCFG_SLIDERS_GROUP);
	if (example == NULL)
		return;
	example->ShowWindow(SW_SHOW);
	CRect rctGrp;
	frame->GetClientRect(rctGrp);

	//double kmin = *std::min_element(vk.begin(), vk.end());
	//double kmax = *std::max_element(vk.begin(), vk.end());
	int sz = int(vk->size());
	for (size_t j = 0; j < vsl.size(); j++)
		delete vsl[j];
	vsl.resize(sz);
	double heigh = (rctGrp.Height() * (1 - shifthtop - shifthbottom)) / (sz + (sz + 1.0) * kgaph);
	double heighT = heigh * (1 + kgaph);
	double top = shifthtop * rctGrp.Height() + heigh * kgaph;

	double width = (1 - 2 * kgapw) * rctGrp.Width();
	double left = kgapw * rctGrp.Width();
	double right = (1 - kgapw) * rctGrp.Width();
	for (int j = 0; j < sz; j++) {
		CRect rct((int)left, (int)(0.5 + top + j * heighT), (int)(0.5 + right), (int)(0.5 + top + (j + 1.0) * heighT));
		vsl[j] = new CSliderCtrl();
		vsl[j]->Create(example->GetStyle(), rct, frame, 188999 + 1 + j);
		vsl[j]->SetRange((int)(fmin * kslayer), (int)(fmax * kslayer), TRUE);
		vsl[j]->SetPos((int)(vk->at(j) * kslayer));
	}
	example->ShowWindow(SW_HIDE);
} // /////////////////////////////////////////////////////////////////////////
void FSliders::saveVK(size_t newsize) {
	if (vk == NULL)
		return;
	if (newsize != vk->size())
		rescale(newsize);
	else
		for (size_t j = 0; j < vsl.size(); j++) {
			int pos = vsl[j]->GetPos();
			int min = vsl[j]->GetRangeMin();
			int max = vsl[j]->GetRangeMax();
			double k = ((double)pos - min) / ((double)max - min);
			vk->at(j) = fmin + fmax * k;
		}
} // /////////////////////////////////////////////////////////////////////////
void FSliders::rescale(size_t newsize) {
	size_t oldsize = vk->size();
	std::vector<std::pair<double, double>> vold(oldsize);
	std::vector<std::pair<double, double>> vnew(newsize);
	double oldstep = 1.0 / (oldsize - 1);
	double newstep = 1.0 / (newsize - 1);

	for (size_t j = 0; j < oldsize; j++)
		vold[j] = std::pair<double, double>(j / (oldsize - 1.0), vsl[j]->GetPos() / (double)kslayer);
	for (size_t j = 1; j < newsize - 1; j++)
		vnew[j] = std::pair<double, double>(j / (newsize - 1.0), 0);

	vnew[0] = vold[0];
	vnew[newsize - 1] = vold[oldsize - 1];
	for (size_t j = 1; j < newsize - 1; j++) {
		for (size_t i = 0; i < oldsize; i++) {
			if (vnew[j].first >= vold[i].first) {
				std::pair<double, double> oldleft = vold[i];
				std::pair<double, double> oldright = vold[i >= oldsize - 1 ? oldsize - 1 : i + 1];
				double k = (vnew[j].first - oldleft.first) / (oldright.first - oldleft.first);
				double second = oldleft.second + k * (oldright.second - oldleft.second);
				vnew[j] = std::pair<double, double>(j / (newsize - 1.0), second);
			}
		}
	}
	vk->resize(newsize);
	for (size_t j = 0; j < vk->size(); j++)
		vk->at(j) = vnew[j].second;
} // ////////////////////////////////////////////////////////////////////////
