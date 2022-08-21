#include "pch.h"
#include "MultiAmp.h"
#include "DlgMaskF.h"
#include "afxdialogex.h"
#include "CMCell4.h"

IMPLEMENT_DYNAMIC(DlgMaskF, CDialogEx)

DlgMaskF::DlgMaskF(CWnd* pParent /*=nullptr*/): CDialogEx(IDD_DLG_MASK_F, pParent){
	for(size_t j = 0; j < vcells.size(); j++)	//	16
		vcells[j] = std::make_unique<CMCell4>();

} // ///////////////////////////////////////////////////////////////////////////////

DlgMaskF::~DlgMaskF(){}

void DlgMaskF::DoDataExchange(CDataExchange* pDX){
	CDialogEx::DoDataExchange(pDX);
	for(int j = 0; j < 16; j++)
		DDX_Control(pDX, IDC_ST_CELL0000 + j, *(vcells[j]));
	DDX_Control(pDX, IDC_SYMETRY_F, m_chSymmetry);
} // ///////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(DlgMaskF, CDialogEx)
	ON_WM_WINDOWPOSCHANGED()
	ON_BN_CLICKED(IDOK, &DlgMaskF::OnBnClickedOk)
	ON_BN_CLICKED(IDC_SYMETRY_F, &DlgMaskF::OnBnClickedSymetryF)
END_MESSAGE_MAP()

std::string DlgMaskF::doModal(const std::string& s_xml){
	sxmlOut = sxmlInp = s_xml;
	INT_PTR retDlg = CDialog::DoModal();
	if(retDlg == IDOK)
		return sxmlOut;
	return sxmlInp;
} // ////////////////////////////////////////////////////////////////
BOOL DlgMaskF::OnInitDialog(){
	CDialogEx::OnInitDialog();
	
	// Add extra initialization here
	for(size_t j = 0; j < vcells.size(); j++){
		std::string s = sxmlInp.substr(j * 16, 16);
		vcells[j]->create(j, s.c_str());
	}
	return TRUE;  // return TRUE unless you set the focus to a control
}// //////////////////////////////////////////////////////////////////////////////////////
void DlgMaskF::OnBnClickedOk(){
	// Add your control notification handler code here
	int poss = 0;
	sxmlOut.resize(16 * 16, '\0');
	for(size_t j = 0; j < vcells.size(); j++){	//	16
		CMCell4& cell4 = *(vcells[j]);
		for(size_t c = 0; c < cell4.v.size(); c++){	// 16
			CMCell& cell = cell4.v[c];
			size_t idRotate = cell.idRotate;
			sxmlOut[poss++] = std::to_string(idRotate)[0];
		}
	}
	CDialogEx::OnOK();
} // //////////////////////////////////////////////////////////////////////////////////////
void DlgMaskF::OnBnClickedSymetryF(){
	auto state = m_chSymmetry.GetState() & 1;
	if(state == BST_CHECKED){
		setEnabledAll(false);
	} else{
		setEnabledAll(true);
	}
} // //////////////////////////////////////////////////////////////////////////////////////
void DlgMaskF::setEnabledAll(bool is_enable){
	int stateSymmetry = ((CButton*)GetDlgItem(IDC_SYMETRY_F))->GetCheck();
	BOOL stateNew = stateSymmetry == BST_CHECKED ? FALSE : TRUE;
//	_RPT1(0, "%d\n", stateNew);
	for(size_t j = 0; j < vcells.size(); j++){	//	16
		CMCell4& cell4 = *(vcells[j]);
		for(size_t c = 0; c < cell4.v.size() / 2; c++){	// 16
			CMCell& cell = cell4.v[c];
//			cell.invalidate();
		}
	}
} // //////////////////////////////////////////////////////////////////////////////////////
