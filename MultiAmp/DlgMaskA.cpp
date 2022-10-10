// DlgMaskA.cpp : implementation file
#include "pch.h"
#include "DlgMaskA.h"
#include "afxdialogex.h"
IMPLEMENT_DYNAMIC(DlgMaskA, CDialog)

DlgMaskA::DlgMaskA(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MASK_A, pParent){
} // ////////////////////////////////////////////////////////////////

DlgMaskA::~DlgMaskA(){}

void DlgMaskA::DoDataExchange(CDataExchange* pDX){
	CDialog::DoDataExchange(pDX);
} // ////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(DlgMaskA, CDialog)
	ON_BN_CLICKED(IDC_CHECK09, &DlgMaskA::OnBnClickedCheck09)
	ON_BN_CLICKED(IDC_CHECK01, &DlgMaskA::OnBnClickedCheck01)
	ON_BN_CLICKED(IDC_CHECK03, &DlgMaskA::OnBnClickedCheck03)
	ON_BN_CLICKED(IDC_CHECK07, &DlgMaskA::OnBnClickedCheck07)
	ON_BN_CLICKED(IDOK, &DlgMaskA::OnBnClickedOk)
	ON_BN_CLICKED(IDC_SYMETRY, &DlgMaskA::OnBnClickedSymetry)
//	ON_WM_PAINT()
END_MESSAGE_MAP()

BOOL DlgMaskA::OnInitDialog(){
	CDialog::OnInitDialog();
	((CButton*)GetDlgItem(IDC_SYMETRY))->SetCheck(BST_CHECKED);
	OnBnClickedSymetry();
	set(sxmlInp.c_str());
	return TRUE;
} // //////////////////////////////////////////////////////////////////////////////////
std::string DlgMaskA::doModal(const std::string& s_xml){
	sxmlOut = sxmlInp = s_xml;
	INT_PTR retDlg = CDialog::DoModal();
	if(retDlg == IDOK)
		return sxmlOut;
	return sxmlInp;
} // ////////////////////////////////////////////////////////////////
void DlgMaskA::OnBnClickedCheck09(){
	SymmetryChange(IDC_CHECK09, IDC_CHECK06);
} // /////////////////////////////////////////////////////////////////////
void DlgMaskA::OnBnClickedCheck01(){
	SymmetryChange(IDC_CHECK01, IDC_CHECK02, IDC_CHECK04, IDC_CHECK08);
} // //////////////////////////////////////////////////////////////////////////////////
void DlgMaskA::OnBnClickedCheck03(){
	SymmetryChange(IDC_CHECK03, IDC_CHECK05, IDC_CHECK10, IDC_CHECK12);
} // //////////////////////////////////////////////////////////////////////////////////
void DlgMaskA::OnBnClickedCheck07(){
	SymmetryChange(IDC_CHECK07, IDC_CHECK11, IDC_CHECK13, IDC_CHECK14);
} // //////////////////////////////////////////////////////////////////////////////////
void DlgMaskA::OnBnClickedOk(){
	sxmlOut = getString();
	CDialog::OnOK();
} // //////////////////////////////////////////////////////////////////////////////////
void DlgMaskA::OnBnClickedSymetry(){
	int stateSymmetry = ((CButton*)GetDlgItem(IDC_SYMETRY))->GetCheck();
	BOOL stateNew = stateSymmetry == BST_CHECKED ? FALSE : TRUE;
	for(size_t j = 0; j < vsymmetry.size(); j++)
		((CButton*)GetDlgItem(vsymmetry[j]))->EnableWindow(stateNew);
} // ////////////////////////////////////////////////////////////////

std::string DlgMaskA::getString(){
	std::string ret("0000000000000000");
	for(int j = 0; j < 16; j++){
		int state = ((CButton*)GetDlgItem(vc[j]))->GetCheck();
		if(state == BST_CHECKED)
			ret[j] = '1';
	}
	return ret;
} // /////////////////////////////////////////////////////////////////
void DlgMaskA::set(const char* s){
	for(int j = 0; j < 16; j++){
		int state = ((CButton*)GetDlgItem(vc[j]))->GetCheck();
		if(s[j] == '0')
			((CButton*)GetDlgItem(vc[j]))->SetCheck(BST_UNCHECKED);
		else if(s[j] == '1')
			((CButton*)GetDlgItem(vc[j]))->SetCheck(BST_CHECKED);
		else
			((CButton*)GetDlgItem(vc[j]))->SetCheck(BST_INDETERMINATE);
	}
} // /////////////////////////////////////////////////////////////////
void DlgMaskA::SymmetryChange(int src, int dst1, int dst2, int dst3){
	if(((CButton*)GetDlgItem(IDC_SYMETRY))->GetCheck() == BST_CHECKED){
		int state = ((CButton*)GetDlgItem(src))->GetCheck();
		((CButton*)GetDlgItem(dst1))->SetCheck(state);
		((CButton*)GetDlgItem(dst2))->SetCheck(state);
		((CButton*)GetDlgItem(dst3))->SetCheck(state);
	}
} // //////////////////////////////////////////////////////////////////////
void DlgMaskA::SymmetryChange(int src, int dst1){
	if(((CButton*)GetDlgItem(IDC_SYMETRY))->GetCheck() == BST_CHECKED){
		int state = ((CButton*)GetDlgItem(src))->GetCheck();
		((CButton*)GetDlgItem(dst1))->SetCheck(state);
	}
} // //////////////////////////////////////////////////////////////////////
