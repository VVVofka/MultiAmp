#pragma once
#include <vector>
#include <algorithm>
class FSliders{
public:
	~FSliders();

	void create(CDialog* dlg, int id_grp, int id_slider_top, int id_edit_top, std::vector<int>* v_k);
	void makeSliders();
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

private:
	void rescale(size_t newsize);
	CDialog* dlg = NULL;
	CWnd* frame = NULL;
	CSliderCtrl* sliderTop = NULL;
	CSliderCtrl* sliderBottom = NULL;
	CEdit* editTop = NULL;

	void vslClear(int new_size);
}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

