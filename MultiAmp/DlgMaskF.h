#pragma once
#include "CMCell16.h"

// DlgMaskF dialog

class DlgMaskF : public CDialogEx{
	DECLARE_DYNAMIC(DlgMaskF)

public:
	DlgMaskF(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DlgMaskF();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_DLG_MASK_F };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CMCell4 c4;
	CMCell16 m_CELL_000;
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);

private:
	void ResizeControl();
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
