#pragma once
#include <string>
#include "DlgMaskA.h"
#include "..\OptsTinyLib\InPort.h"
//#include "..\OptsTinyLib\tinyxml2.h"

// https://rapidjson.org/
#include "../Common/include/rapidjson/document.h"
#include "../Common/include/rapidjson/writer.h"
#include "../Common/include/rapidjson/stringbuffer.h"
using namespace rapidjson;

namespace options{
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
	public:
		afx_msg void OnBnClickedButton1();
		afx_msg void OnBnClickedBtJson();
		afx_msg void OnBnClickedBtMaskA();
		afx_msg void OnBnClickedOk();
	};
}