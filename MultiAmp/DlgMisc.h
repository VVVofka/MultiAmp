#pragma once
class DlgMisc : public CDialog{
	DECLARE_DYNAMIC(DlgMisc)

public:
	DlgMisc(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DlgMisc();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_DLG_MISC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
}; // ######################################################################################
