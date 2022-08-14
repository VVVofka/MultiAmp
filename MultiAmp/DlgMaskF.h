#pragma once


// DlgMaskF dialog

class DlgMaskF : public CDialogEx
{
	DECLARE_DYNAMIC(DlgMaskF)

public:
	DlgMaskF(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DlgMaskF();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_MASK_F };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
