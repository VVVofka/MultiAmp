#pragma once
#include "resource.h"
#include <array>
#include <string>

// DlgMaskA dialog
class DlgMaskA : public CDialog{
	DECLARE_DYNAMIC(DlgMaskA)

public:
	DlgMaskA(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DlgMaskA();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_MASK_A };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	std::array<int, 16> vb = {
		IDB_000, IDB_010, IDB_020, IDB_030,
		IDB_040, IDB_050, IDB_060, IDB_070,
		IDB_080, IDB_090, IDB_100, IDB_110,
		IDB_120, IDB_130, IDB_140, IDB_150};
	std::array<int, 16> vc = {
		IDC_CHECK00, IDC_CHECK01, IDC_CHECK02, IDC_CHECK03,
		IDC_CHECK04, IDC_CHECK05, IDC_CHECK06, IDC_CHECK07,
		IDC_CHECK08, IDC_CHECK09, IDC_CHECK10, IDC_CHECK11,
		IDC_CHECK12, IDC_CHECK13, IDC_CHECK14, IDC_CHECK15};
	std::array<int, 16 - 4 - 2> vsymmetry = {
		IDC_CHECK06, //IDC_CHECK00, IDC_CHECK15,
		IDC_CHECK02, IDC_CHECK04, IDC_CHECK08,
		IDC_CHECK05, IDC_CHECK10, IDC_CHECK12,
		IDC_CHECK11, IDC_CHECK13, IDC_CHECK14};
	void set(const char* s);
	std::string getString();
	void SymmetryChange(int src, int dst1, int dst2, int dst3);
	void SymmetryChange(int src, int dst1);
public:
	std::string sxmlInp;
	std::string sxmlOut;
	std::string doModal(const std::string& s_xml);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedCheck09();
	afx_msg void OnBnClickedCheck01();
	afx_msg void OnBnClickedCheck03();
	afx_msg void OnBnClickedCheck07();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedSymetry();
};
 