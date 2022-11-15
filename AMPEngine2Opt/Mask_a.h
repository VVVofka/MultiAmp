#pragma once
#include "..\Common\adat.h"

// Mask_a dialog

class Mask_a : public CDialog{
	DECLARE_DYNAMIC(Mask_a)

public:
	Mask_a(CWnd* pParent = nullptr);   // standard constructor
	virtual ~Mask_a();
	bool domodal(adat::maskA& old_mask);

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_MASK_A1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	adat::maskA* oldmask = NULL;
	adat::maskA newmask;
}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
