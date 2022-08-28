#pragma once
#include <vector>
#include <algorithm>

class FSliders{
public:
	~FSliders();
	std::vector<CSliderCtrl*> vsl;
	std::vector<float>* vk;	// = { 0.1, 0.2, 0.45, 0.85, 1.25, 1.5 };

	void activate(CWnd* frame, CSliderCtrl* example, std::vector<float>* v_k);
	void activate();
	void saveVK(size_t newsize);

	double kslayer = 100;
	double shifthtop = 0.1;
	double shifthbottom = 0.1;
	double kgaph = 0.1f;
	double kgapw = 0.05;

	double fmin = 0;
	double fmax = 2;

private:
	void rescale(size_t newsize);
	CSliderCtrl* example = NULL;
	CWnd* frame = NULL;
}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

