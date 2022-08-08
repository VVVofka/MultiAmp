#pragma once


// Dlg dialog

class Dlg : public CDialog
{
	DECLARE_DYNAMIC(Dlg)

public:
	Dlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~Dlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Dlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedApply();
};
