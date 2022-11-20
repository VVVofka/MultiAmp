#pragma once
#include <vector>
#include <algorithm>
#include "..\OptsTinyLib\structLaysCfg.h"

class FSliders{
	CDialog* dlg = NULL;	// TODO: del?
	CWnd* frame = NULL;
	structLaysCfg* cfg = NULL;
	size_t cnt = 0;	// active sliders count
	int idxSlider0 = 0, idxEdit0 = 0;

	int iEdit(size_t idx, const int def, const int digits = 3);

public:
	void create(CDialog* dlg, int id_grp, int id_slider_top, int id_edit_top, structLaysCfg& cfg, size_t cnt_sliders);
	void draw();
	bool hscroll(HWND hwnd);
	void chngEdit(size_t idx);
	void saveVK();
	void rescale(size_t newsize);

	std::vector<CSliderCtrl*> vsliders;
	std::vector<CEdit*> vedits;
	//std::vector<int> vkoefs;	// = { 0.1, 0.2, 0.45, 0.85, 1.25, 1.5 };

	double shifthtop = 0.1;
	double shifthbottom = 0.1;
	double kgaph = 0.1f;
	double kgapw = 0.02;

	int fmin = -100;
	int fmax = 200;
}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

