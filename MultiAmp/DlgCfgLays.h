#pragma once
#include "..\OptsTinyLib\structLaysCfg.h"
#include "FSliders.h"
#include <array>

class DlgCfgLays : public CDialog{
	DECLARE_DYNAMIC(DlgCfgLays)
public:
	DlgCfgLays(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DlgCfgLays();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_CFG_LAYS };
#endif

	structLaysCfg cfgOut, cfgInp;
	structLaysCfg doModal(structLaysCfg& cfg_lays);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	FSliders fsliders;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CEdit m_topX;
	CEdit m_topY;
	CEdit m_cnt;
	CEdit m_lay0X;
	CEdit m_lay0Y;
	CSpinButtonCtrl m_spinTopX;
	CSpinButtonCtrl m_spinTopY;
	CSpinButtonCtrl m_spinCnt;
	afx_msg void OnDeltaposSpinTopx(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinTopy(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinCnt(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CStatic m_pointsAll;

private:
	void chngCnt(size_t cnt);
public:
	afx_msg void OnEnChangeEdLaysCnt();
	CButton m_btOK;
};
