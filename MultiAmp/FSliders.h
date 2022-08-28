#pragma once
#include <vector>
#include <algorithm>
	class SliderEdit{
	public:
		~SliderEdit(){
			if(slider != NULL) delete slider;
			if(edit != NULL) delete edit;
		}
		CSliderCtrl* slider;
		CEdit* edit;
	}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

class FSliders{
public:
	~FSliders();
	std::vector<SliderEdit> vsl;
	std::vector<float>* vk;	// = { 0.1, 0.2, 0.45, 0.85, 1.25, 1.5 };

	void activate(CWnd* grp, CSliderCtrl* example_slider, CEdit* example_edit, std::vector<float>* v_k);
	void saveVK(size_t newsize);

	double kslayer = 100;
	double shifthtop = 0.1;
	double shifthbottom = 0.1;
	double kgaph = 0.1f;
	double kgapw = 0.05;

	double fmin = 0;
	double fmax = 2;

private:
	void activate();
	void rescale(size_t newsize);
	CSliderCtrl* exampleSlider = NULL;
	CEdit* exampleEdit = NULL;
	CWnd* frame = NULL;
}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

