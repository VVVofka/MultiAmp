#include "pch.h"
#include "MultiAmp.h"
#include "DlgMaskF.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(DlgMaskF, CDialogEx)

DlgMaskF::DlgMaskF(CWnd* pParent /*=nullptr*/) : CDialogEx(IDD_DLG_MASK_F, pParent){
	for(size_t j = 0; j < vcells.size(); j++)	//	16
		vcells[j] = std::make_unique<CMCell16>();
	for(size_t j = 0; j < vsymOther.size(); j++){	//	4
		std::vector<size_t>& curv = vsymOther[j];
		size_t srcid = curv[0];
		for(size_t i = 1; i < curv.size(); i++){
			size_t dstid = curv[i];
			CMCell16* dstcur = vcells[dstid].get();
			vcells[srcid]->vretsym.push_back(dstcur);
		}
	}
} // ///////////////////////////////////////////////////////////////////////////////
DlgMaskF::~DlgMaskF(){} // ///////////////////////////////////////////////////////////////////////////////
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
	sxmlOut = sxmlInp = convs(s_xml);
	//std::string sdbg(256, '0');
	//sdbg[16] = '1';
	//sdbg[38] = '8';
	//sxmlOut = sxmlInp = convs(sdbg);
	INT_PTR retDlg = CDialog::DoModal();
	if(retDlg == IDOK)
		return convs(sxmlOut);
	return convs(sxmlInp);
} // ////////////////////////////////////////////////////////////////
BOOL DlgMaskF::OnInitDialog(){
	CDialogEx::OnInitDialog();
	// Add extra initialization here
	for(size_t j = 0; j < vcells.size(); j++){
		std::string s = sxmlInp.substr(j * 16, 16);
		vcells[j]->create(j, s.c_str());
	}
	m_chSymmetry.SetCheck(1);
	setSymmetry();
	return TRUE;  // return TRUE unless you set the focus to a control
} // //////////////////////////////////////////////////////////////////////////////////////
size_t DlgMaskF::convertNCell(size_t idx){
	// 0  1  4  5    10  4 14 15
	// 2  3  6  7 ->  8  9 12 13
	// 8  9 12 13     2  3  6  7
	//10 11 14 15     0  1  4  5
	const size_t v[16] = {10,11,8,9,14,15,12,13,2,3,0,1,6,7,4,5};
	return v[idx];
} // //////////////////////////////////////////////////////////////////////////////////////
std::string DlgMaskF::convs(const std::string s_in){
	_ASSERTE(s_in.size() == 16 * 16);
	const size_t vidmask[16] = {0,4,8,12,1,5,9,13,2,6,10,14,3,7,11,15};
//	const std::string cnvrotate = "054321876";
	std::string ret(256, '\0');
	for(size_t idmask = 0; idmask < 16; idmask++){
		const size_t conv_idmask = vidmask[idmask] * 16;
		size_t ofs = idmask * 16;
		for(size_t j = 0; j < 16; j++){
			const size_t conv_j = convertNCell(j);
			//int i = int(s_in[ofs + j]) - int('0');
			//ret[conv_idmask * 16 + conv_j] = cnvrotate[i];
			ret[conv_idmask + conv_j] = s_in[ofs + j];
		}
	}
	return ret;
} // ///////////////////////////////////////////////////////////////////////////////////////
void DlgMaskF::OnBnClickedOk(){
	int poss = 0;
	sxmlOut.resize(16 * 16, '\0');
	for(size_t j = 0; j < vcells.size(); j++){	//	16
		//const size_t conv_j = convertNCell(j);
		const CMCell16& cell4 = *(vcells[j]);
		for(size_t c = 0; c < cell4.v.size(); c++){	// 16
			//const size_t conv_c = convertNCell(c);
			const CMCell& cell = cell4.v[c];
			const size_t idRotate = cell.idRotate;
			sxmlOut[poss++] = std::to_string(idRotate)[0];
		}
	}
	CDialogEx::OnOK();
} // //////////////////////////////////////////////////////////////////////////////////////
void DlgMaskF::OnBnClickedSymetryF(){
	auto state = m_chSymmetry.GetState() & 1;
	if(state == BST_CHECKED){
		setSymmetry();
	} else{
		setNonSymmetry();
	}
} // //////////////////////////////////////////////////////////////////////////////////////
void DlgMaskF::setSymmetry(){
	for(size_t j = 0; j < vcells.size(); j++){	//	16
		vcells[j].get()->setEnabled(false);
		vcells[j].get()->isSymmetryMode = true;
	}
	for(size_t j = 0; j < vsym.size(); j++){	//	16
		std::vector<size_t>& curv = vsym[j];
		size_t idx16 = curv[0];
		CMCell16* cell16 = vcells[idx16].get();	//	std::unique_ptr<CMCell16>
		for(size_t c = 1; c < curv.size(); c++){
			size_t idx_cell = curv[c];
			cell16->setEnabled(idx_cell, true);
		}
	}
} // //////////////////////////////////////////////////////////////////////////////////////
void DlgMaskF::setNonSymmetry(){
	for(size_t j = 0; j < vcells.size(); j++){	//	16
		vcells[j].get()->setEnabled(true);
		vcells[j].get()->isSymmetryMode = false;
	}
} // //////////////////////////////////////////////////////////////////////////////////////
