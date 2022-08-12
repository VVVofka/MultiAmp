// Dlg.cpp : implementation file

#include "pch.h"
#include "DlgMaskA.h"
#include "Dlg.h"
#include "afxdialogex.h"
// Dlg dialog
IMPLEMENT_DYNAMIC(Dlg, CDialog)

Dlg::Dlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_Dlg, pParent){
	//this->GetDlgItem()
} // ////////////////////////////////////////////////////////////////

Dlg::~Dlg(){}

void Dlg::DoDataExchange(CDataExchange* pDX){
	CDialog::DoDataExchange(pDX);
} // ////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(Dlg, CDialog)
	ON_BN_CLICKED(IDAPPLY, &Dlg::OnBnClickedApply)
	ON_BN_CLICKED(IDC_SYMETRY, &Dlg::OnBnClickedSymmetry)
END_MESSAGE_MAP()

// Dlg message handlers
void Dlg::OnBnClickedApply(){
	for(int j = 0; j < 16; j++){
		int state = ((CButton*)GetDlgItem(vc[j]))->GetCheck();
		sxml[j] = (state == BST_CHECKED) ? '1' : '0';
	}
} // ////////////////////////////////////////////////////////////////
INT_PTR Dlg::doModal(std::string& sxml){
	return CDialog::DoModal();
} // ////////////////////////////////////////////////////////////////
void Dlg::get(char* s){
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
void Dlg::set(const char* s){
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
void Dlg::OnBnClickedSymmetry(){
	int stateSymmetry = ((CButton*)GetDlgItem(IDC_SYMETRY))->GetCheck();
	BOOL stateNew = stateSymmetry == BST_CHECKED ? FALSE : TRUE;
	for(int j = 0; j < 16 - 4; j++)
		((CButton*)GetDlgItem(vsymmetry[j]))->EnableWindow(stateNew);
} // ///////////////////////////////////////////////////////////////////
