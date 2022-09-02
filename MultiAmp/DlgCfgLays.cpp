#include "pch.h"
#include "MultiAmp.h"
#include "DlgCfgLays.h"
#include "afxdialogex.h"
#include <string>

// DlgCfgLays dialog
IMPLEMENT_DYNAMIC(DlgCfgLays, CDialog)

DlgCfgLays::DlgCfgLays(CWnd* pParent) : CDialog(IDD_CFG_LAYS, pParent){
	CWnd* frame = (CWnd*)this->GetDlgItem(IDC_LAYSCFG_SLIDERS_GROUP);
	fsliders.create(frame, &slTop, &edTop, &slBottom, &edBottom, &cfgOut.vkf);
} // //////////////////////////////////////////////////////////////////////////////

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
	DDX_Control(pDX, IDC_LAYSCFG_SLIDER_TOP, slTop);
	DDX_Control(pDX, IDC_LAYSCFG_EDIT_TOP, edTop);
	DDX_Control(pDX, IDC_LAYSCFG_SLIDER_BOTTOM, slBottom);
	DDX_Control(pDX, IDC_LAYSCFG_EDIT_BOTTOM, edBottom);
} // //////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(DlgCfgLays, CDialog)
	ON_BN_CLICKED(IDOK, &DlgCfgLays::OnBnClickedOk)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_TOPX, &DlgCfgLays::OnDeltaposSpinTopx)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_TOPY, &DlgCfgLays::OnDeltaposSpinTopy)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_CNT, &DlgCfgLays::OnDeltaposSpinCnt)
ON_WM_HSCROLL()
END_MESSAGE_MAP()

structLaysCfg DlgCfgLays::doModal(structLaysCfg& cfg_lays){
	cfgOut = cfgInp = cfg_lays;
	INT_PTR retDlg = CDialog::DoModal();
	if(retDlg == IDOK)
		return cfgOut;
	return cfgInp;
} // //////////////////////////////////////////////////////////////////////////////
// DlgCfgLays message handlers

void DlgCfgLays::OnBnClickedOk(){
	//cfgOut.topX = std::to_integer()
	fsliders.saveVK(cfgOut.laysCnt);
	CDialog::OnOK();
} // ///////////////////////////////////////////////////////////////////////////////////////////
BOOL DlgCfgLays::OnInitDialog(){
	CDialog::OnInitDialog();
	m_spinTopX.SetBuddy(&m_topX);	// подружить окно
	m_spinTopX.SetRange(1, 20);		// диапазон
	m_spinTopX.SetPos(1);		    // позиция

	m_spinTopY.SetBuddy(&m_topY);	// подружить окно
	m_spinTopY.SetRange(1, 20);		// диапазон
	m_spinTopY.SetPos(1);		    // позиция

	m_spinCnt.SetBuddy(&m_cnt);		// подружить окно
	m_spinCnt.SetRange(2, 20);		// диапазон
	m_spinCnt.SetPos(5);		    // позиция


	if(cfgInp.laysCnt == 0)
		cfgInp.laysCnt = 1;
	m_topX.SetWindowTextA(std::to_string(cfgInp.topX).c_str());
	m_topY.SetWindowTextA(std::to_string(cfgInp.topY).c_str());
	m_cnt.SetWindowTextA(std::to_string(cfgInp.laysCnt).c_str());
	m_lay0X.SetWindowTextA(std::to_string(cfgInp.bottomX()).c_str());
	m_lay0Y.SetWindowTextA(std::to_string(cfgInp.bottomY()).c_str());

	fsliders.activate();
	return TRUE;  // return TRUE unless you set the focus to a control
} // ///////////////////////////////////////////////////////////////////////////////////////////
void DlgCfgLays::OnDeltaposSpinTopx(NMHDR* pNMHDR, LRESULT* pResult){
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	cfgOut.topX = pNMUpDown->iPos + pNMUpDown->iDelta;
	if(cfgOut.topX <= 0)		cfgOut.topX = 1;
	m_lay0X.SetWindowTextA(std::to_string(cfgOut.bottomX()).c_str());
	*pResult = 0;
} // ///////////////////////////////////////////////////////////////////////////////////////////
void DlgCfgLays::OnDeltaposSpinTopy(NMHDR* pNMHDR, LRESULT* pResult){
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	cfgOut.topY = pNMUpDown->iPos + pNMUpDown->iDelta;
	if(cfgOut.topY <= 0)		cfgOut.topY = 1;
	m_lay0Y.SetWindowTextA(std::to_string(cfgOut.bottomY()).c_str());
	*pResult = 0;
} // ///////////////////////////////////////////////////////////////////////////////////////////
void DlgCfgLays::OnDeltaposSpinCnt(NMHDR* pNMHDR, LRESULT* pResult){
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	cfgOut.laysCnt = pNMUpDown->iPos + pNMUpDown->iDelta;
	if(cfgOut.laysCnt < 2)		cfgOut.laysCnt = 2;
	m_lay0X.SetWindowTextA(std::to_string(cfgOut.bottomX()).c_str());
	m_lay0Y.SetWindowTextA(std::to_string(cfgOut.bottomY()).c_str());
	fsliders.saveVK(cfgOut.laysCnt);
	Invalidate();
	*pResult = 0;
} // ///////////////////////////////////////////////////////////////////////////////////////////
void DlgCfgLays::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar){
	if(pScrollBar->m_hWnd == slTop.m_hWnd){
		auto pos = slTop.GetPos();
		this->Invalidate(FALSE);
	}else if(pScrollBar->m_hWnd == slBottom.m_hWnd){

		this->Invalidate(FALSE);
	}
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
} // ///////////////////////////////////////////////////////////////////////////////////////////
