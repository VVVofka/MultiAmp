#pragma once


// DlgCfgLays dialog

class DlgCfgLays : public CDialog{
	DECLARE_DYNAMIC(DlgCfgLays)

public:
	DlgCfgLays(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DlgCfgLays();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_CFG_LAYS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
