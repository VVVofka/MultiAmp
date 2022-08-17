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
	//DDX_Control(pDX, IDC_ST_CELL0000, m_0000);
	//DDX_Control(pDX, IDC_ST_CELL0001, m_0001);
	DDX_Control(pDX, IDC_ST_CELL0000, *(vcells[0]));
	DDX_Control(pDX, IDC_ST_CELL0001, *(vcells[1]));
	DDX_Control(pDX, IDC_ST_CELL0002, *(vcells[2]));
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
	// TODO:  Add extra initialization here
	for(size_t j = 0; j < vcells.size(); j++)
		vcells[j]->create(j);
	vcells[0]->setRotates("7617430840080718");
	vcells[1]->setRotates("3424532453280718");
	vcells[2]->setRotates("2530400882842711");
	return TRUE;  // return TRUE unless you set the focus to a control
} // //////////////////////////////////////////////////////////////////////////////////////
