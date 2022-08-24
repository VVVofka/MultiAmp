#pragma once
#include "CMCell16.h"
#include <array>
#include <vector>
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
	virtual BOOL OnInitDialog();

	std::string sxmlInp;
	std::string sxmlOut;

	std::string doModal(const std::string& s_xml);

private:
	std::array<std::unique_ptr<CMCell16>, 16> vcells;
	void setSymmetry();
	void setNonSymmetry();
	std::vector<std::vector<size_t>> vsym{
		{0, 0,1,3},
		{1, 0,1,3,4,5,6,7,12,13,15},
		{3, 0,1,2,3,8,9,10,11},
		{6, 0,1,3,4,5,6},
		{7, 0,1,3,4,5,6,7,12,13,15},
		//{9, 0,1,3,4,5,6},
		{15, 0,1,3}
	};

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedSymetryF();
	CButton m_chSymmetry;
};
