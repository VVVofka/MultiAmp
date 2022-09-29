#pragma once

class DlgData : public CDialog{
	DECLARE_DYNAMIC(DlgData)

public:
	DlgData(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DlgData();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_DATA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_size_type;
	afx_msg void OnBnClickedFlgDataCount();
	afx_msg void OnBnClickedFlgDataProc();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
