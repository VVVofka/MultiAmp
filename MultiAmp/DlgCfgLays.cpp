#include "pch.h"
#include "MultiAmp.h"
#include "DlgCfgLays.h"
#include "afxdialogex.h"
#include <string>

// DlgCfgLays dialog
IMPLEMENT_DYNAMIC(DlgCfgLays, CDialog)

DlgCfgLays::DlgCfgLays(CWnd* pParent) : CDialog(IDD_CFG_LAYS, pParent){} // //////////////////////////////////////////////////////////////////////////////

DlgCfgLays::~DlgCfgLays(){}

void DlgCfgLays::DoDataExchange(CDataExchange* pDX){
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CNT_LAYS_X_MIN, m_topX);
	DDX_Control(pDX, IDC_CNT_LAYS_Y_MIN, m_topY);
	DDX_Control(pDX, IDC_ED_LAYS_CNT, m_cnt);
	DDX_Control(pDX, IDC_CNT_LAYS_X_MAX, m_lay0X);
	DDX_Control(pDX, IDC_CNT_LAYS_Y_MAX, m_lay0Y);
	DDX_Control(pDX, IDC_SPIN_TOPX, m_spinTopX);
	DDX_Control(pDX, IDC_SPIN_TOPY, m_spinTopY);
	DDX_Control(pDX, IDC_SPIN_CNT, m_spinCnt);
	DDX_Control(pDX, IDC_ST_LAYSCFG_POINTS_ALL, m_pointsAll);
	DDX_Control(pDX, IDOK, m_btOK);
} // //////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(DlgCfgLays, CDialog)
	ON_BN_CLICKED(IDOK, &DlgCfgLays::OnBnClickedOk)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_TOPX, &DlgCfgLays::OnDeltaposSpinTopx)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_TOPY, &DlgCfgLays::OnDeltaposSpinTopy)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_CNT, &DlgCfgLays::OnDeltaposSpinCnt)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_ED_LAYS_CNT, &DlgCfgLays::OnEnChangeEdLaysCnt)
	ON_EN_CHANGE(IDC_LAYSCFG_EDIT00, &DlgCfgLays::OnEnChangeLayscfgEdit00)
	ON_EN_CHANGE(IDC_LAYSCFG_EDIT01, &DlgCfgLays::OnEnChangeLayscfgEdit01)
	ON_EN_CHANGE(IDC_LAYSCFG_EDIT02, &DlgCfgLays::OnEnChangeLayscfgEdit02)
	ON_EN_CHANGE(IDC_LAYSCFG_EDIT03, &DlgCfgLays::OnEnChangeLayscfgEdit03)
	ON_EN_CHANGE(IDC_LAYSCFG_EDIT04, &DlgCfgLays::OnEnChangeLayscfgEdit04)
	ON_EN_CHANGE(IDC_LAYSCFG_EDIT05, &DlgCfgLays::OnEnChangeLayscfgEdit05)
	ON_EN_CHANGE(IDC_LAYSCFG_EDIT06, &DlgCfgLays::OnEnChangeLayscfgEdit06)
	ON_EN_CHANGE(IDC_LAYSCFG_EDIT07, &DlgCfgLays::OnEnChangeLayscfgEdit07)
	ON_EN_CHANGE(IDC_LAYSCFG_EDIT08, &DlgCfgLays::OnEnChangeLayscfgEdit08)
	ON_EN_CHANGE(IDC_LAYSCFG_EDIT09, &DlgCfgLays::OnEnChangeLayscfgEdit09)
	ON_EN_CHANGE(IDC_LAYSCFG_EDIT10, &DlgCfgLays::OnEnChangeLayscfgEdit10)
	ON_EN_CHANGE(IDC_LAYSCFG_EDIT11, &DlgCfgLays::OnEnChangeLayscfgEdit11)
	ON_EN_CHANGE(IDC_LAYSCFG_EDIT12, &DlgCfgLays::OnEnChangeLayscfgEdit12)
	ON_EN_CHANGE(IDC_LAYSCFG_EDIT13, &DlgCfgLays::OnEnChangeLayscfgEdit13)
	ON_EN_CHANGE(IDC_LAYSCFG_EDIT14, &DlgCfgLays::OnEnChangeLayscfgEdit14)
	ON_EN_CHANGE(IDC_LAYSCFG_EDIT15, &DlgCfgLays::OnEnChangeLayscfgEdit15)
	ON_EN_CHANGE(IDC_LAYSCFG_EDIT16, &DlgCfgLays::OnEnChangeLayscfgEdit16)
	ON_EN_CHANGE(IDC_LAYSCFG_EDIT17, &DlgCfgLays::OnEnChangeLayscfgEdit17)
	ON_EN_CHANGE(IDC_LAYSCFG_EDIT18, &DlgCfgLays::OnEnChangeLayscfgEdit18)
	ON_EN_CHANGE(IDC_LAYSCFG_EDIT19, &DlgCfgLays::OnEnChangeLayscfgEdit19)
END_MESSAGE_MAP()

structLaysCfg DlgCfgLays::doModal(structLaysCfg cfg_lays){
	cfgOut = cfgInp = cfg_lays;
	INT_PTR retDlg = CDialog::DoModal();
	if(retDlg == IDOK)
		return cfgOut;
	return cfgInp;
} // //////////////////////////////////////////////////////////////////////////////
// DlgCfgLays message handlers

void DlgCfgLays::OnBnClickedOk(){
	fsliders.saveVK(cfgOut.laysCnt());

	CDialog::OnOK();
} // ///////////////////////////////////////////////////////////////////////////////////////////
BOOL DlgCfgLays::OnInitDialog(){
	CDialog::OnInitDialog();

	fsliders.create(this, IDC_LAYSCFG_SLIDERS_GROUP, IDC_LAYSCFG_SLIDER_00, IDC_LAYSCFG_EDIT00, &cfgOut.vkf, 20);

	m_spinTopX.SetBuddy(&m_topX);	// ��������� ����
	m_spinTopX.SetRange(1, 20);		// ��������
	m_spinTopX.SetPos(1);		    // �������

	m_spinTopY.SetBuddy(&m_topY);	// ��������� ����
	m_spinTopY.SetRange(1, 20);		// ��������
	m_spinTopY.SetPos(1);		    // �������

	m_spinCnt.SetBuddy(&m_cnt);		// ��������� ����
	m_spinCnt.SetRange(2, 20);		// ��������
	m_spinCnt.SetPos(5);		    // �������

	if(cfgInp.laysCnt() == 0)
		cfgInp.vkf.resize(2, 1);
	m_topX.SetWindowTextA(std::to_string(cfgInp.topX).c_str());
	m_topY.SetWindowTextA(std::to_string(cfgInp.topY).c_str());
	m_cnt.SetWindowTextA(std::to_string(cfgInp.laysCnt()).c_str());
	m_lay0X.SetWindowTextA(std::to_string(cfgInp.bottomX()).c_str());
	m_lay0Y.SetWindowTextA(std::to_string(cfgInp.bottomY()).c_str());

	fsliders.draw();
	return TRUE;  // return TRUE unless you set the focus to a control
} // ///////////////////////////////////////////////////////////////////////////////////////////
void DlgCfgLays::OnDeltaposSpinTopx(NMHDR* pNMHDR, LRESULT* pResult){
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	cfgOut.topX = pNMUpDown->iPos + pNMUpDown->iDelta;
	if(cfgOut.topX <= 0)
		cfgOut.topX = 1;
	m_lay0X.SetWindowTextA(std::to_string(cfgOut.bottomX()).c_str());
	*pResult = 0;
} // ///////////////////////////////////////////////////////////////////////////////////////////
void DlgCfgLays::OnDeltaposSpinTopy(NMHDR* pNMHDR, LRESULT* pResult){
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	cfgOut.topY = pNMUpDown->iPos + pNMUpDown->iDelta;
	if(cfgOut.topY <= 0)
		cfgOut.topY = 1;
	m_lay0Y.SetWindowTextA(std::to_string(cfgOut.bottomY()).c_str());
	*pResult = 0;
} // ///////////////////////////////////////////////////////////////////////////////////////////
void DlgCfgLays::OnDeltaposSpinCnt(NMHDR* pNMHDR, LRESULT* pResult){
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	chngCnt(pNMUpDown->iPos + pNMUpDown->iDelta);
	*pResult = 0;
} // ///////////////////////////////////////////////////////////////////////////////////////////
void DlgCfgLays::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar){
	fsliders.hscroll(pScrollBar->m_hWnd);
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
} // ///////////////////////////////////////////////////////////////////////////////////////////
void DlgCfgLays::chngCnt(size_t cnt){
	static int prev = -1;
	if(prev == (int)cnt)
		return;
	if(cnt < 2 || cnt > fsliders.vsliders.size()){
		m_btOK.EnableWindow(FALSE);
		prev = (int)cnt;
		return;
	}
	prev = (int)cnt;
	cfgOut.vkf.resize(cnt, 1);

	m_lay0X.SetWindowTextA(std::to_string(cfgOut.bottomX()).c_str());
	m_lay0Y.SetWindowTextA(std::to_string(cfgOut.bottomY()).c_str());
	m_pointsAll.SetWindowTextA(std::to_string(cfgOut.bottomX() * cfgOut.bottomY()).c_str());
	fsliders.saveVK(cfgOut.laysCnt());
	m_btOK.EnableWindow(TRUE);
	Invalidate();
} // ///////////////////////////////////////////////////////////////////////////////////////////
void DlgCfgLays::OnEnChangeEdLaysCnt(){
	char buf[3] = "";
	m_cnt.GetWindowTextA(buf, 2);
	int len = strlen(buf);
	if(len > 0 && len <= 2){
		int cnt = atoi(buf);
		chngCnt((size_t)cnt);
	}
} // ///////////////////////////////////////////////////////////////////////////////////////////
//bool DlgCfgLays::iEdit(const int id, int& out, const int digits){
//	BOOL* no_err;
//	out = GetDlgItemInt(id, no_err, FALSE);
//	return no_err != 0;
//} // ///////////////////////////////////////////////////////////////////////////////////////////
int DlgCfgLays::iEdit(const int id, const int def, const int digits){
	BOOL bSuccess = FALSE;
	int out = GetDlgItemInt(id, &bSuccess, FALSE);
	return bSuccess? out : def;
} // ///////////////////////////////////////////////////////////////////////////////////////////
void DlgCfgLays::OnEnChangeLayscfgEdit00(){ fsliders.chngEdit(0); }
void DlgCfgLays::OnEnChangeLayscfgEdit01(){ fsliders.chngEdit(1); }
void DlgCfgLays::OnEnChangeLayscfgEdit02(){ fsliders.chngEdit(2); }
void DlgCfgLays::OnEnChangeLayscfgEdit03(){ fsliders.chngEdit(3); }
void DlgCfgLays::OnEnChangeLayscfgEdit04(){ fsliders.chngEdit(4); }
void DlgCfgLays::OnEnChangeLayscfgEdit05(){ fsliders.chngEdit(5); }
void DlgCfgLays::OnEnChangeLayscfgEdit06(){ fsliders.chngEdit(6); }
void DlgCfgLays::OnEnChangeLayscfgEdit07(){ fsliders.chngEdit(7); }
void DlgCfgLays::OnEnChangeLayscfgEdit08(){ fsliders.chngEdit(8); }
void DlgCfgLays::OnEnChangeLayscfgEdit09(){ fsliders.chngEdit(9); }
void DlgCfgLays::OnEnChangeLayscfgEdit10(){ fsliders.chngEdit(10); }
void DlgCfgLays::OnEnChangeLayscfgEdit11(){ fsliders.chngEdit(11); }
void DlgCfgLays::OnEnChangeLayscfgEdit12(){ fsliders.chngEdit(12); }
void DlgCfgLays::OnEnChangeLayscfgEdit13(){ fsliders.chngEdit(13); }
void DlgCfgLays::OnEnChangeLayscfgEdit14(){ fsliders.chngEdit(14); }
void DlgCfgLays::OnEnChangeLayscfgEdit15(){ fsliders.chngEdit(15); }
void DlgCfgLays::OnEnChangeLayscfgEdit16(){ fsliders.chngEdit(16); }
void DlgCfgLays::OnEnChangeLayscfgEdit17(){ fsliders.chngEdit(17); }
void DlgCfgLays::OnEnChangeLayscfgEdit18(){ fsliders.chngEdit(18); }
void DlgCfgLays::OnEnChangeLayscfgEdit19(){ fsliders.chngEdit(19); }
