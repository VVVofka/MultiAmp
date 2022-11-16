#pragma once
#include <string>
#include "DlgMaskA.h"
#include "DlgMaskF.h"
#include "..\OptsTinyLib\InPort.h"
#include "../OptsTinyLib/structAll.h"


class CMultiAmpDlg : public CDialogEx{
	const int ID_TIMER_1 = 197;
	// Construction
public:
	CMultiAmpDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_MULTIAMP_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	char json_in[255] = {0};
	char json_out[255] = {0};
	UINT_PTR timer = NULL;

	// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR  nIDEvent);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	std::string dllName();
	structAll cfg_all;
public:
	afx_msg void OnBnClickedBtMaskA();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtMaskF();
	afx_msg void OnBnClickedBtLays();
	afx_msg void OnBnClickedBtData();
	afx_msg void OnBnClickedBtDataMisc();
	afx_msg void OnBnClickedBtMainRun();
	afx_msg void OnBnClickedBtMainRun2();
};
