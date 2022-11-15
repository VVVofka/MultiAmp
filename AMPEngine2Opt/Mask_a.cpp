#include "pch.h"
#include "AMPEngine2Opt.h"
#include "Mask_a.h"
#include "afxdialogex.h"
#pragma warning(disable : 26495)
// Mask_a dialog
IMPLEMENT_DYNAMIC(Mask_a, CDialog)
Mask_a::Mask_a(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MASK_A1, pParent){}

Mask_a::~Mask_a(){}

void Mask_a::DoDataExchange(CDataExchange* pDX){
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Mask_a, CDialog)
END_MESSAGE_MAP()

// Mask_a message handlers


bool Mask_a::domodal(adat::maskA& old_mask){
	oldmask = &old_mask;
	INT_PTR retModal = CDialog::DoModal();
	bool ret = *oldmask != newmask && retModal == IDOK;
	if(ret)
		old_mask = newmask;
	return ret;
} // /////////////////////////////////////////////////////////////
