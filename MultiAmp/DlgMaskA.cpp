// DlgMaskA.cpp : implementation file
#include "pch.h"
#include "DlgMaskA.h"
#include "afxdialogex.h"
// DlgMaskA dialog
IMPLEMENT_DYNAMIC(DlgMaskA, CDialog)

DlgMaskA::DlgMaskA(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MASK_A, pParent){
	//this->GetDlgItem()
} // ////////////////////////////////////////////////////////////////

DlgMaskA::~DlgMaskA(){}

void DlgMaskA::DoDataExchange(CDataExchange* pDX){
	CDialog::DoDataExchange(pDX);
} // ////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(DlgMaskA, CDialog)
	ON_BN_CLICKED(IDAPPLY, &DlgMaskA::OnBnClickedApply)
	ON_BN_CLICKED(IDC_SYMETRY, &DlgMaskA::OnBnClickedSymmetry)
END_MESSAGE_MAP()

// DlgMaskA message handlers
void DlgMaskA::OnBnClickedApply(){
	for(int j = 0; j < 16; j++){
		int state = ((CButton*)GetDlgItem(vc[j]))->GetCheck();
		sxml[j] = (state == BST_CHECKED) ? '1' : '0';
	}
} // ////////////////////////////////////////////////////////////////
INT_PTR DlgMaskA::doModal(std::string& sxml){
	return CDialog::DoModal();
} // ////////////////////////////////////////////////////////////////
void DlgMaskA::get(char* s){
	for(int j = 0; j < 16; j++){
		int state = ((CButton*)GetDlgItem(vc[j]))->GetCheck();
		if(state == BST_CHECKED)
			s[j] = '1';
		else if(state == BST_UNCHECKED)
			s[j] = '0';
		else if(state == BST_INDETERMINATE)
			s[j] = '0';
	}
	s[16] = '\0';
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
void DlgMaskA::OnBnClickedSymmetry(){
	int stateSymmetry = ((CButton*)GetDlgItem(IDC_SYMETRY))->GetCheck();
	BOOL stateNew = stateSymmetry == BST_CHECKED ? FALSE : TRUE;
	for(int j = 0; j < 16 - 4; j++)
		((CButton*)GetDlgItem(vsymmetry[j]))->EnableWindow(stateNew);
} // ///////////////////////////////////////////////////////////////////
