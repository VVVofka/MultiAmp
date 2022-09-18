#pragma once
#include <vector>
#include <algorithm>
class FSliders{
	CDialog* dlg = NULL;	// TODO: del?
	CWnd* frame = NULL;
	CSliderCtrl* sliderTop = NULL;
	CEdit* editTop = NULL;
	size_t szVisible = 0;

	void rescale(size_t newsize);

public:
	void create(CDialog* dlg, int id_grp, int id_slider_top, int id_edit_top, size_t size_visible, size_t size_capacity);
	void draw();
	void setElements();	// TODO: del
	void saveVK(size_t newsize);
	bool hscroll(HWND hwnd);

	std::vector<CSliderCtrl*> vsliders;
	std::vector<CEdit*> vedits;
	std::vector<int>* vkoefs = NULL;	// = { 0.1, 0.2, 0.45, 0.85, 1.25, 1.5 };

	double shifthtop = 0.1;
	double shifthbottom = 0.1;
	double kgaph = 0.1f;
	double kgapw = 0.02;

	int fmin = -100;
	int fmax = 200;
}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

