#pragma once
#include "CMCell4.h"
#include <array>
#include <string>
#include <memory>
// DlgMaskF dialog

class DlgMaskF : public CDialogEx{
	DECLARE_DYNAMIC(DlgMaskF)

public:
	DlgMaskF(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DlgMaskF();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_DLG_MASK_F };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	virtual BOOL OnInitDialog();

	std::string sxmlInp;
	std::string sxmlOut;

	std::string doModal(const std::string& s_xml);

private:
	std::array<std::unique_ptr<CMCell4>, 16> vcells;
};
