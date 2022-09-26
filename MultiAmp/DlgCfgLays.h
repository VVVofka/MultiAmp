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
	structLaysCfg doModal(structLaysCfg cfg_lays);

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
	CStatic m_pointsAll;

private:
	void chngCnt(size_t cnt);
	//bool iEdit(const int id, int& out, const int digits = 2);
	int iEdit(const int id, const int def, const int digits = 2);
public:
	CButton m_btOK;

	int iTopX(){ return  iEdit(IDC_CNT_LAYS_X_MIN, 1, 2); };
	int iTopY(){ return iEdit(IDC_CNT_LAYS_Y_MIN, 1, 2); };
	int iLaysCnt(const int def = 5){ return iEdit(IDC_ED_LAYS_CNT, def, 2); };
	int iKoefF(int idx){ return iEdit(IDC_LAYSCFG_EDIT00 + idx, 1, 3); };

	afx_msg void OnDeltaposSpinTopx(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinTopy(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinCnt(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeEdLaysCnt();
	afx_msg void OnEnChangeLayscfgEdit00();
	afx_msg void OnEnChangeLayscfgEdit01();
	afx_msg void OnEnChangeLayscfgEdit02();
	afx_msg void OnEnChangeLayscfgEdit03();
	afx_msg void OnEnChangeLayscfgEdit04();
	afx_msg void OnEnChangeLayscfgEdit05();
	afx_msg void OnEnChangeLayscfgEdit06();
	afx_msg void OnEnChangeLayscfgEdit07();
	afx_msg void OnEnChangeLayscfgEdit08();
	afx_msg void OnEnChangeLayscfgEdit09();
	afx_msg void OnEnChangeLayscfgEdit10();
	afx_msg void OnEnChangeLayscfgEdit11();
	afx_msg void OnEnChangeLayscfgEdit12();
	afx_msg void OnEnChangeLayscfgEdit13();
	afx_msg void OnEnChangeLayscfgEdit14();
	afx_msg void OnEnChangeLayscfgEdit15();
	afx_msg void OnEnChangeLayscfgEdit16();
	afx_msg void OnEnChangeLayscfgEdit17();
	afx_msg void OnEnChangeLayscfgEdit18();
	afx_msg void OnEnChangeLayscfgEdit19();
};
