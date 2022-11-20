#pragma once
#include <vector>
#include <algorithm>
class FSliders{
	CDialog* dlg = NULL;	// TODO: del?
	CWnd* frame = NULL;
	int idxSlider0 = 0, idxEdit0 = 0;

	void rescale(size_t newsize);
	int iEdit(size_t idx, const int def, const int digits = 3);

public:
	void create(CDialog* dlg, int id_grp, int id_slider_top, int id_edit_top, std::vector<int> v_koefs, size_t size_capacity);
	void draw();
	void saveVK(size_t newsize);
	bool hscroll(HWND hwnd);
	void chngEdit(size_t idx);

	std::vector<CSliderCtrl*> vsliders;
	std::vector<CEdit*> vedits;
	std::vector<int> vkoefs;	// = { 0.1, 0.2, 0.45, 0.85, 1.25, 1.5 };

	double shifthtop = 0.1;
	double shifthbottom = 0.1;
	double kgaph = 0.1f;
	double kgapw = 0.02;

	int fmin = -100;
	int fmax = 200;
}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

