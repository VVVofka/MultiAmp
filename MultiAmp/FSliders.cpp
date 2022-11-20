#include "pch.h"
#include "FSliders.h"
#include <utility>
#include <string>
#include <locale.h>

void FSliders::create(CDialog* dlg, int id_grp, int id_slider_top, int id_edit_top, structLaysCfg& cfg_in, size_t cnt_sliders){
	this->dlg = dlg;
	cfg = &cfg_in;
	cnt = cfg_in.koefsF.size();
	frame = (CWnd*)dlg->GetDlgItem(id_grp);
	vsliders.resize(cnt_sliders);
	vedits.resize(cnt_sliders);
	idxSlider0 = id_slider_top;
	idxEdit0 = id_edit_top;
	for(size_t j = 0; j < cnt_sliders; j++){
		vsliders[j] = (CSliderCtrl*)dlg->GetDlgItem(id_slider_top + j);
		vedits[j] = (CEdit*)dlg->GetDlgItem(id_edit_top + j);
	}
} // /////////////////////////////////////////////////////////////////////////
void FSliders::draw(){
	CRect rctFrame, rctSlider, rctSlider0;
	frame->GetWindowRect(rctFrame);
	vsliders[0]->GetWindowRect(rctSlider0);
	int height = rctSlider0.Height();

	rctSlider.right = rctFrame.right - rctFrame.left;
	rctSlider.left = rctSlider.right - rctSlider0.Width();

	double h = ((double)rctFrame.Height() - 1.5 * height) / (cnt - 1);
	for(size_t j = 0; j < cnt; j++){
		int shift = height / 2;
		rctSlider.top = (LONG)(j * h) + shift;
		rctSlider.bottom = rctSlider.top + height;
		vsliders[j]->MoveWindow(rctSlider);
		//_RPT5(0, "%d\t %d * %d   %d * %d\n", j, rctSlider.left, rctSlider.top, rctSlider.right, rctSlider.bottom);
		int i = cfg->intKF(j);
		vsliders[j]->SetRange(fmin, fmax, FALSE);
		vsliders[j]->SetPos(i);
		vsliders[j]->SetTicFreq(100);
		vedits[j]->SetWindowTextA(std::to_string(i).c_str());
		vsliders[j]->ShowWindow(SW_SHOWNORMAL);
		vedits[j]->ShowWindow(SW_SHOWNORMAL);
		vsliders[j]->SetBuddy(vedits[j]);
	}
	for(size_t j = cnt; j < vsliders.size(); j++){
		vsliders[j]->ShowWindow(SW_HIDE);
		vedits[j]->ShowWindow(SW_HIDE);
	}
} // /////////////////////////////////////////////////////////////////////////
void FSliders::saveVK(){
	for(size_t j = 0; j < cnt; j++)
		cfg->setIntKF(j, vsliders[j]->GetPos());
	draw();
} // /////////////////////////////////////////////////////////////////////////
void FSliders::rescale(size_t new_cnt_sliders){
	cnt = new_cnt_sliders;
	cfg->resize(new_cnt_sliders + 1);
	draw();
	//struct xy{ double x, y; };

	//size_t oldsize = cfg.koefsF.size();
	//std::vector<xy> vold(oldsize);
	//std::vector<xy> vnew(new_cnt_sliders);

	//for(size_t j = 0; j < oldsize; j++){
	//	vold[j].x = j / (oldsize - 1.0);
	//	vold[j].y = vsliders[j]->GetPos();
	//}
	//for(size_t j = 0; j < new_cnt_sliders; j++)
	//	vnew[j].x = j / (new_cnt_sliders - 1.0);

	//for(size_t j = 1; j < new_cnt_sliders - 1; j++){
	//	for(size_t i = 0; i < oldsize; i++){
	//		if(vnew[j].x >= vold[i].x){
	//			xy& oldleft = vold[i];
	//			xy& oldright = vold[i >= oldsize - 1 ? oldsize - 1 : i + 1];
	//			double k = (vnew[j].x - oldleft.x) / (oldright.x - oldleft.x);
	//			vnew[j].y = oldleft.y + k * (oldright.y - oldleft.y);
	//		}
	//	}
	//}
	//vnew[0].y = vold[0].y;
	//vnew[new_cnt_sliders - 1].y = vold[oldsize - 1].y;

	//vkoefs.resize(new_cnt_sliders);
	//for(size_t j = 0; j < vkoefs.size(); j++)
	//	vkoefs.at(j) = lround(vnew[j].y);
} // ////////////////////////////////////////////////////////////////////////
bool FSliders::hscroll(HWND hwnd){
	for(size_t j = 0; j < cnt; j++){
		if(vsliders[j]->m_hWnd == hwnd){
			vedits[j]->SetWindowTextA(std::to_string(vsliders[j]->GetPos()).c_str());
			return true;
		}
	}
	return false;
} // /////////////////////////////////////////////////////////////////////////
void FSliders::chngEdit(size_t idx){
	int oldSlider = vsliders[idx]->GetPos();
	int newSlider = iEdit(idx, 100, 3);
	if(oldSlider != newSlider)
		vsliders[idx]->SetPos(newSlider);
} // /////////////////////////////////////////////////////////////////////////
int FSliders::iEdit(size_t idx, const int def, const int digits){
	BOOL bSuccess = FALSE;
	int out = dlg->GetDlgItemInt(idxEdit0 + idx, &bSuccess, TRUE);
	if(bSuccess == FALSE)
		return def;
	if(out < vsliders[idx]->GetRangeMin() || out > vsliders[idx]->GetRangeMax())
		out = 100;
	return out;
} // ///////////////////////////////////////////////////////////////////////////////////////////
