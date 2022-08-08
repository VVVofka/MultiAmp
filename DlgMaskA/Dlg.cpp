// Dlg.cpp : implementation file
//

#include "pch.h"
#include "DlgMaskA.h"
#include "Dlg.h"
#include "afxdialogex.h"
#include "resource.h"

// Dlg dialog

IMPLEMENT_DYNAMIC(Dlg, CDialog)

Dlg::Dlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_Dlg, pParent){

}

Dlg::~Dlg(){}

void Dlg::DoDataExchange(CDataExchange* pDX){
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Dlg, CDialog)
	ON_BN_CLICKED(IDAPPLY, &Dlg::OnBnClickedApply)
END_MESSAGE_MAP()

// Dlg message handlers
void Dlg::OnBnClickedApply(){
	// TODO: Add your control notification handler code here
}
