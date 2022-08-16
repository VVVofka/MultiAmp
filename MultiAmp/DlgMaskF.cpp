#include "pch.h"
#include "MultiAmp.h"
#include "DlgMaskF.h"
#include "afxdialogex.h"
#include "CMCell4.h"
// DlgMaskF dialog

IMPLEMENT_DYNAMIC(DlgMaskF, CDialogEx)

DlgMaskF::DlgMaskF(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_MASK_F, pParent){}

DlgMaskF::~DlgMaskF(){}

void DlgMaskF::DoDataExchange(CDataExchange* pDX){
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ST_CELL4, c4);
}


BEGIN_MESSAGE_MAP(DlgMaskF, CDialogEx)
	ON_WM_WINDOWPOSCHANGED()
	ON_BN_CLICKED(IDC_BUTTON2, &DlgMaskF::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &DlgMaskF::OnBnClickedButton3)
END_MESSAGE_MAP()

void DlgMaskF::OnBnClickedButton2(){
	//m_CELL_000.rotate();
} // ////////////////////////////////////////////////////////////////////////
void DlgMaskF::OnBnClickedButton3(){
	//m_CELL_000.rotate(-1);
} // ////////////////////////////////////////////////////////////////////////
BOOL DlgMaskF::OnInitDialog(){
	CDialogEx::OnInitDialog();
	// TODO:  Add extra initialization here
	c4.create();
	c4.setIdMaskF(6);
	c4.setRotates("4530400840080718");
	return TRUE;  // return TRUE unless you set the focus to a control
} // //////////////////////////////////////////////////////////////////////////////////////
