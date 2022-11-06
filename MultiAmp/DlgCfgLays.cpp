#include "pch.h"
#include "MultiAmp.h"
#include "DlgCfgLays.h"
#include "afxdialogex.h"
#include <string>

// DlgCfgLays dialog
IMPLEMENT_DYNAMIC(DlgCfgLays, CDialog)

DlgCfgLays::DlgCfgLays(CWnd* pParent) : CDialog(IDD_CFG_LAYS, pParent){}
DlgCfgLays::~DlgCfgLays(){}
// //////////////////////////////////////////////////////////////////////////////
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
	DDX_Control(pDX, IDC_ED_LAYS_CPU_SINGLE, m_cpu_single);
	DDX_Control(pDX, IDC_ED_LAYS_CPU_MULTI, m_cpu_multi);
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
	ON_EN_KILLFOCUS(IDC_LAYSCFG_EDIT00, &DlgCfgLays::OnEnKillfocusLayscfgEdit00)
	ON_EN_KILLFOCUS(IDC_LAYSCFG_EDIT01, &DlgCfgLays::OnEnKillfocusLayscfgEdit01)
	ON_EN_KILLFOCUS(IDC_LAYSCFG_EDIT02, &DlgCfgLays::OnEnKillfocusLayscfgEdit02)
	ON_EN_KILLFOCUS(IDC_LAYSCFG_EDIT03, &DlgCfgLays::OnEnKillfocusLayscfgEdit03)
	ON_EN_KILLFOCUS(IDC_LAYSCFG_EDIT04, &DlgCfgLays::OnEnKillfocusLayscfgEdit04)
	ON_EN_KILLFOCUS(IDC_LAYSCFG_EDIT05, &DlgCfgLays::OnEnKillfocusLayscfgEdit05)
	ON_EN_KILLFOCUS(IDC_LAYSCFG_EDIT06, &DlgCfgLays::OnEnKillfocusLayscfgEdit06)
	ON_EN_KILLFOCUS(IDC_LAYSCFG_EDIT07, &DlgCfgLays::OnEnKillfocusLayscfgEdit07)
	ON_EN_KILLFOCUS(IDC_LAYSCFG_EDIT08, &DlgCfgLays::OnEnKillfocusLayscfgEdit08)
	ON_EN_KILLFOCUS(IDC_LAYSCFG_EDIT09, &DlgCfgLays::OnEnKillfocusLayscfgEdit09)
	ON_EN_KILLFOCUS(IDC_LAYSCFG_EDIT10, &DlgCfgLays::OnEnKillfocusLayscfgEdit10)
	ON_EN_KILLFOCUS(IDC_LAYSCFG_EDIT11, &DlgCfgLays::OnEnKillfocusLayscfgEdit11)
	ON_EN_KILLFOCUS(IDC_LAYSCFG_EDIT12, &DlgCfgLays::OnEnKillfocusLayscfgEdit12)
	ON_EN_KILLFOCUS(IDC_LAYSCFG_EDIT13, &DlgCfgLays::OnEnKillfocusLayscfgEdit13)
	ON_EN_KILLFOCUS(IDC_LAYSCFG_EDIT14, &DlgCfgLays::OnEnKillfocusLayscfgEdit14)
	ON_EN_KILLFOCUS(IDC_LAYSCFG_EDIT15, &DlgCfgLays::OnEnKillfocusLayscfgEdit15)
	ON_EN_KILLFOCUS(IDC_LAYSCFG_EDIT16, &DlgCfgLays::OnEnKillfocusLayscfgEdit16)
	ON_EN_KILLFOCUS(IDC_LAYSCFG_EDIT17, &DlgCfgLays::OnEnKillfocusLayscfgEdit17)
	ON_EN_KILLFOCUS(IDC_LAYSCFG_EDIT18, &DlgCfgLays::OnEnKillfocusLayscfgEdit18)
	ON_EN_KILLFOCUS(IDC_LAYSCFG_EDIT19, &DlgCfgLays::OnEnKillfocusLayscfgEdit19)
END_MESSAGE_MAP()

structLaysCfg DlgCfgLays::doModal(structLaysCfg cfg_lays){
	cfgOut = cfg_lays;
	auto cfgInp = cfgOut;
	INT_PTR retDlg = CDialog::DoModal();
	if(retDlg == IDOK)
		return cfgOut;
	return cfgInp;
} // //////////////////////////////////////////////////////////////////////////////
// DlgCfgLays message handlers
BOOL DlgCfgLays::OnInitDialog(){
	CDialog::OnInitDialog();

	fsliders.create(this, IDC_LAYSCFG_SLIDERS_GROUP, IDC_LAYSCFG_SLIDER_00, IDC_LAYSCFG_EDIT00, &cfgOut.vkf, 20);
	fsliders.draw();

	m_spinTopX.SetBuddy(&m_topX);	// подружить окно
	m_spinTopX.SetRange(1, 20);		// диапазон
	m_spinTopX.SetPos((int)cfgOut.topX);		    // позиция

	m_spinTopY.SetBuddy(&m_topY);	// подружить окно
	m_spinTopY.SetRange(1, 20);		// диапазон
	m_spinTopY.SetPos((int)cfgOut.topY);		    // позиция

	m_spinCnt.SetBuddy(&m_cnt);		// подружить окно
	m_spinCnt.SetRange(2, 20);		// диапазон
	m_spinCnt.SetPos((int)cfgOut.vkf.size());		    // позиция

	m_topX.SetWindowTextA(std::to_string(m_spinTopX.GetPos()).c_str());
	m_topY.SetWindowTextA(std::to_string(m_spinTopY.GetPos()).c_str());
	m_cnt.SetWindowTextA(std::to_string(m_spinCnt.GetPos()).c_str());
	m_lay0X.SetWindowTextA(razd(cfgOut.bottomX()).c_str());
	m_lay0Y.SetWindowTextA(razd(cfgOut.bottomY()).c_str());

	m_cpu_single.SetWindowTextA(std::to_string(cfgOut.cpuSingle).c_str());
	m_cpu_multi.SetWindowTextA(std::to_string(cfgOut.cpuMultiThreaded).c_str());

	return TRUE;  // return TRUE unless you set the focus to a control
} // ///////////////////////////////////////////////////////////////////////////////////////////
void DlgCfgLays::OnDeltaposSpinTopx(NMHDR* pNMHDR, LRESULT* pResult){
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	cfgOut.topX = pNMUpDown->iPos + pNMUpDown->iDelta;
	if(cfgOut.topX <= 0)
		cfgOut.topX = 1;
	m_lay0X.SetWindowTextA(razd(cfgOut.bottomX()).c_str());
	*pResult = 0;
} // ///////////////////////////////////////////////////////////////////////////////////////////
void DlgCfgLays::OnDeltaposSpinTopy(NMHDR* pNMHDR, LRESULT* pResult){
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	cfgOut.topY = pNMUpDown->iPos + pNMUpDown->iDelta;
	if(cfgOut.topY <= 0)
		cfgOut.topY = 1;
	m_lay0Y.SetWindowTextA(razd(cfgOut.bottomY()).c_str());
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

	m_lay0X.SetWindowTextA(razd(cfgOut.bottomX()).c_str());
	m_lay0Y.SetWindowTextA(razd(cfgOut.bottomY()).c_str());
	m_pointsAll.SetWindowTextA(razd(cfgOut.bottomX() * cfgOut.bottomY()).c_str());
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
int DlgCfgLays::iEdit(const int id, const int def){
	BOOL bSuccess = FALSE;
	int out = GetDlgItemInt(id, &bSuccess, FALSE);
	return bSuccess ? out : def;
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

void DlgCfgLays::OnEnKillfocusLayscfgEdit00(){ slid2ed(0); }
void DlgCfgLays::OnEnKillfocusLayscfgEdit01(){ slid2ed(1); }
void DlgCfgLays::OnEnKillfocusLayscfgEdit02(){ slid2ed(2); }
void DlgCfgLays::OnEnKillfocusLayscfgEdit03(){ slid2ed(3); }
void DlgCfgLays::OnEnKillfocusLayscfgEdit04(){ slid2ed(4); }
void DlgCfgLays::OnEnKillfocusLayscfgEdit05(){ slid2ed(5); }
void DlgCfgLays::OnEnKillfocusLayscfgEdit06(){ slid2ed(6); }
void DlgCfgLays::OnEnKillfocusLayscfgEdit07(){ slid2ed(7); }
void DlgCfgLays::OnEnKillfocusLayscfgEdit08(){ slid2ed(8); }
void DlgCfgLays::OnEnKillfocusLayscfgEdit09(){ slid2ed(9); }
void DlgCfgLays::OnEnKillfocusLayscfgEdit10(){ slid2ed(10); }
void DlgCfgLays::OnEnKillfocusLayscfgEdit11(){ slid2ed(11); }
void DlgCfgLays::OnEnKillfocusLayscfgEdit12(){ slid2ed(12); }
void DlgCfgLays::OnEnKillfocusLayscfgEdit13(){ slid2ed(13); }
void DlgCfgLays::OnEnKillfocusLayscfgEdit14(){ slid2ed(14); }
void DlgCfgLays::OnEnKillfocusLayscfgEdit15(){ slid2ed(15); }
void DlgCfgLays::OnEnKillfocusLayscfgEdit16(){ slid2ed(16); }
void DlgCfgLays::OnEnKillfocusLayscfgEdit17(){ slid2ed(17); }
void DlgCfgLays::OnEnKillfocusLayscfgEdit18(){ slid2ed(18); }
void DlgCfgLays::OnEnKillfocusLayscfgEdit19(){ slid2ed(19); }


void DlgCfgLays::slid2ed(size_t idx){
	BOOL bSuccess = FALSE;
	char buf1[5] = "", buf2[5] = "";
	GetDlgItemText(IDC_LAYSCFG_EDIT00 + idx, buf1, 5);
	int out = GetDlgItemInt(IDC_LAYSCFG_EDIT00 + idx, &bSuccess, TRUE);
	if(!bSuccess)
		out = 100;
	else if(out < fsliders.vsliders[idx]->GetRangeMin())
		out = fsliders.vsliders[idx]->GetRangeMin();
	else if(out > fsliders.vsliders[idx]->GetRangeMax())
		out = fsliders.vsliders[idx]->GetRangeMax();
	_itoa_s(out, buf2, 10);
	if(strcmp(buf1, buf2) != 0)
		SetDlgItemText(IDC_LAYSCFG_EDIT00 + idx, buf2);
} // /////////////////////////////////////////////////////////////////
std::string DlgCfgLays::razd(size_t u){
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
void DlgCfgLays::OnBnClickedOk(){
	fsliders.saveVK(cfgOut.laysCnt());
	cfgOut.cpuSingle = iEdit(m_cpu_single.GetDlgCtrlID(), 0);
	cfgOut.cpuMultiThreaded= iEdit(m_cpu_multi.GetDlgCtrlID(), 0);
	CDialog::OnOK();
} // ///////////////////////////////////////////////////////////////////////////////////////////
