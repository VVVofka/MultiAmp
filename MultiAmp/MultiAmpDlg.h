// MultiAmpDlg.h : header file

#pragma once
#include <string>

// https://rapidjson.org/
#include "../Common/include/rapidjson/document.h"
#include "../Common/include/rapidjson/writer.h"
#include "../Common/include/rapidjson/stringbuffer.h"
using namespace rapidjson;

namespace options{

	// CMultiAmpDlg dialog
	class CMultiAmpDlg : public CDialogEx{
		// Construction
	public:
		CMultiAmpDlg(CWnd* pParent = nullptr);	// standard constructor

	// Dialog Data
#ifdef AFX_DESIGN_TIME
		enum{ IDD = IDD_MULTIAMP_DIALOG };
#endif

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
		char json[255];
		UINT_PTR timer;

	// Implementation
	protected:
		HICON m_hIcon;

		// Generated message map functions
		virtual BOOL OnInitDialog();
		afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
		afx_msg void OnPaint();
		afx_msg HCURSOR OnQueryDragIcon();
		DECLARE_MESSAGE_MAP()
	public:
		afx_msg void OnBnClickedButton1();
	private:
		std::string dllName();
	public:
		afx_msg void OnBnClickedBtJson();
		afx_msg void OnBnClickedBtMaskA();
		afx_msg void OnBnClickedOk();
//		virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
//		virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
//		virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
//		afx_msg void OnTimer(UINT_PTR nIDEvent);
	};
}