#include "pch.h"
#include "MultiAmp.h"
#include "DlgData.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(DlgData, CDialog)

DlgData::DlgData(CWnd* pParent /*=nullptr*/) : CDialog(IDD_DATA, pParent), m_size_type(FALSE){} // ///////////////////////////////////////////////////////////////////////////
DlgData::~DlgData(){}

void DlgData::DoDataExchange(CDataExchange* pDX){
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_FLG_DATA_COUNT, m_size_type);
	DDX_Control(pDX, IDC_TXT_DATA_SIZE_X, m_size_x);
	DDX_Control(pDX, IDC_TXT_DATA_SIZE_Y, m_size_y);
	DDX_Control(pDX, IDC_TXT_DATA_SIZE_ALL, m_size);
} // ///////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(DlgData, CDialog)
	ON_BN_CLICKED(IDC_FLG_DATA_COUNT, &DlgData::OnBnClickedFlgDataCount)
	ON_BN_CLICKED(IDC_FLG_DATA_PROC, &DlgData::OnBnClickedFlgDataProc)
	ON_BN_CLICKED(IDOK, &DlgData::OnBnClickedOk)
END_MESSAGE_MAP()

// DlgData message handlers
void DlgData::OnBnClickedFlgDataCount(){} // ///////////////////////////////////////////////////////////////////////////
void DlgData::OnBnClickedFlgDataProc(){
	// TODO: Add your control notification handler code here
} // ///////////////////////////////////////////////////////////////////////////
BOOL DlgData::OnInitDialog(){
	CDialog::OnInitDialog();
	m_size_x.SetWindowTextA(razd(data->szX).c_str());
	m_size_y.SetWindowTextA(razd(data->szY).c_str());
	m_size.SetWindowTextA(razd(data->szAll()).c_str());
	return TRUE;
} // ///////////////////////////////////////////////////////////////////////////
void DlgData::OnBnClickedOk(){
	// TODO: Add your control notification handler code here
	_RPT1(0, "%d\n", m_size_type);
	CDialog::OnOK();
}  // ///////////////////////////////////////////////////////////////////////////
INT_PTR DlgData::DoModal(){
	return CDialog::DoModal();
}  // ///////////////////////////////////////////////////////////////////////////
INT_PTR DlgData::doModal(DlgDataData* in_data){
	data = in_data;
	return DoModal();
}  // ///////////////////////////////////////////////////////////////////////////
std::string DlgData::razd(size_t u){
	size_t j = 0;
	std::string s = std::to_string(u % 10);
	while(u /= 10){
		if((++j % 3) == 0)
			s += ' ';
		s += std::to_string(u % 10);
	}
	size_t len = s.length();
	for(size_t j = 0; j < len / 2; j++)
		std::swap(s[j], s[len - j - 1]);
	return s;
} // /////////////////////////////////////////////////////////////////////////////