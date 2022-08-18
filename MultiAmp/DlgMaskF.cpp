#include "pch.h"
#include "MultiAmp.h"
#include "DlgMaskF.h"
#include "afxdialogex.h"
#include "CMCell4.h"
// DlgMaskF dialog

IMPLEMENT_DYNAMIC(DlgMaskF, CDialogEx)

DlgMaskF::DlgMaskF(CWnd* pParent /*=nullptr*/): CDialogEx(IDD_DLG_MASK_F, pParent){
	for(size_t j = 0; j < vcells.size(); j++)
		vcells[j] = std::make_unique<CMCell4>();
} // ///////////////////////////////////////////////////////////////////////////////

DlgMaskF::~DlgMaskF(){}

void DlgMaskF::DoDataExchange(CDataExchange* pDX){
	CDialogEx::DoDataExchange(pDX);
	for(int j = 0; j < 16; j++)
		DDX_Control(pDX, IDC_ST_CELL0000 + j, *(vcells[j]));
	//DDX_Control(pDX, IDC_ST_CELL0000, *(vcells[0]));
} // ///////////////////////////////////////////////////////////////////////////////


BEGIN_MESSAGE_MAP(DlgMaskF, CDialogEx)
	ON_WM_WINDOWPOSCHANGED()
	ON_BN_CLICKED(IDC_BUTTON2, &DlgMaskF::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &DlgMaskF::OnBnClickedButton3)
END_MESSAGE_MAP()

std::string DlgMaskF::doModal(const std::string& s_xml){
	sxmlOut = sxmlInp = s_xml;
	INT_PTR retDlg = CDialog::DoModal();
	if(retDlg == IDOK)
		return sxmlOut;
	return sxmlInp;
} // ////////////////////////////////////////////////////////////////
void DlgMaskF::OnBnClickedButton2(){
	//m_CELL_000.rotate();
} // ////////////////////////////////////////////////////////////////////////
void DlgMaskF::OnBnClickedButton3(){
	//m_CELL_000.rotate(-1);
} // ////////////////////////////////////////////////////////////////////////
BOOL DlgMaskF::OnInitDialog(){
	CDialogEx::OnInitDialog();
	
	// Add extra initialization here
	for(size_t j = 0; j < vcells.size(); j++){
		vcells[j]->create(j);
		std::string s = sxmlInp.substr(j * 16, 16);
		vcells[j]->setRotates(s.c_str());
	}
	return TRUE;  // return TRUE unless you set the focus to a control
} // //////////////////////////////////////////////////////////////////////////////////////
