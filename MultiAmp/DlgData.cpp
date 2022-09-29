#include "pch.h"
#include "MultiAmp.h"
#include "DlgData.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(DlgData, CDialog)

DlgData::DlgData(CWnd* pParent /*=nullptr*/)	: CDialog(IDD_DATA, pParent), m_size_type(FALSE){
} // ///////////////////////////////////////////////////////////////////////////
DlgData::~DlgData(){}

void DlgData::DoDataExchange(CDataExchange* pDX){
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_FLG_DATA_COUNT, m_size_type);
} // ///////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(DlgData, CDialog)
	ON_BN_CLICKED(IDC_FLG_DATA_COUNT, &DlgData::OnBnClickedFlgDataCount)
	ON_BN_CLICKED(IDC_FLG_DATA_PROC, &DlgData::OnBnClickedFlgDataProc)
	ON_BN_CLICKED(IDOK, &DlgData::OnBnClickedOk)
END_MESSAGE_MAP()

// DlgData message handlers
void DlgData::OnBnClickedFlgDataCount(){
} // ///////////////////////////////////////////////////////////////////////////
void DlgData::OnBnClickedFlgDataProc(){
	// TODO: Add your control notification handler code here
} // ///////////////////////////////////////////////////////////////////////////
BOOL DlgData::OnInitDialog(){
	CDialog::OnInitDialog();
	// TODO:  Add extra initialization here
	return TRUE;
} // ///////////////////////////////////////////////////////////////////////////
void DlgData::OnBnClickedOk(){
	// TODO: Add your control notification handler code here
	_RPT1(0, "%d\n", m_size_type);
	CDialog::OnOK();
}  // ///////////////////////////////////////////////////////////////////////////
