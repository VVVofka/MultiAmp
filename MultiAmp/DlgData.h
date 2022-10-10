#pragma once
#include "DlgDataData.h"

class DlgData : public CDialog{
	DECLARE_DYNAMIC(DlgData)
	DlgDataData* data = NULL;
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
	INT_PTR doModal(DlgDataData* in_data);
	afx_msg void OnBnClickedFlgDataCount();
	afx_msg void OnBnClickedFlgDataProc();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	virtual INT_PTR DoModal();
	CStatic m_size_x;
	CStatic m_size_y;
	CStatic m_size;
	CEdit m_count_proc;
	CButton m_cnt_proc_type;
	CEdit m_sigma;
	CWnd m_screen;
	
	afx_msg void OnBnClickedBtDataGener();
	afx_msg void OnPaint();
private:
	std::string razd(size_t u);
	size_t getVal();
	float getFloatFromCEdit(CEdit& edit);
	BYTE incColor(BYTE clr);
	std::string float_to_str(float val, int digits);

	bool newdata = true;
	size_t curPointsCount = 0;
};
