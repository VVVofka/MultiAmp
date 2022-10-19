#include "pch.h"
#include "MultiAmp.h"
#include "DlgMisc.h"
#include "afxdialogex.h"
#include <string>
#include "Utils.h"


IMPLEMENT_DYNAMIC(DlgMisc, CDialog)
DlgMisc::DlgMisc(CWnd* pParent /*=nullptr*/) : CDialog(IDD_DLG_MISC, pParent){}

DlgMisc::~DlgMisc(){}

void DlgMisc::DoDataExchange(CDataExchange* pDX){
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ED_MISC_CURSEED, m_seed);
	DDX_Control(pDX, IDC_ED_MISC_CURITERATION, m_iteration);

	DDX_Control(pDX, IDC_ED_MISC_DTCREATE_TICK, m_tick_create);
	DDX_Control(pDX, IDC_ED_MISC_DTCREATE_YEAR, m_year_create);
	DDX_Control(pDX, IDC_ED_MISC_DTCREATE_MONTH, m_month_create);
	DDX_Control(pDX, IDC_ED_MISC_DTCREATE_DAY, m_day_create);
	DDX_Control(pDX, IDC_ED_MISC_DTCREATE_HOUR, m_hour_create);
	DDX_Control(pDX, IDC_ED_MISC_DTCREATE_MINUTE, m_min_create);
	DDX_Control(pDX, IDC_ED_MISC_DTCREATE_SEC, m_sec_create);
	
	DDX_Control(pDX, IDC_ED_MISC_DTSTOP_TICK, m_tick_stop);
	DDX_Control(pDX, IDC_ED_MISC_DTSTOP_YEAR, m_year_stop);
	DDX_Control(pDX, IDC_ED_MISC_DTSTOP_MONTH, m_month_stop);
	DDX_Control(pDX, IDC_ED_MISC_DTSTOP_DAY, m_day_stop);
	DDX_Control(pDX, IDC_ED_MISC_DTSTOP_HOUR, m_hour_stop);
	DDX_Control(pDX, IDC_ED_MISC_DTSTOP_MINUTE, m_min_stop);
	DDX_Control(pDX, IDC_ED_MISC_DTSTOP_SEC, m_sec_stop);
	
	DDX_Control(pDX, IDC_ED_MISC_COMMENT, m_comment);
}
BEGIN_MESSAGE_MAP(DlgMisc, CDialog)
END_MESSAGE_MAP()
// DlgMisc message handlers


BOOL DlgMisc::OnInitDialog(){
	CDialog::OnInitDialog();

	m_seed.SetWindowTextA(std::to_string(data->curRndSeed).c_str());
	m_iteration.SetWindowTextA(std::to_string(data->curIteration).c_str());

	auto dtstart = data->dtCreate;
	m_tick_create.SetWindowTextA(std::to_string(dtstart).c_str());

	auto dtstop = data->dtLastStop;
	m_tick_stop.SetWindowTextA(std::to_string(dtstop).c_str());

	// _tzset();
	struct tm tmcreate, tmstop;
	_localtime64_s(&tmcreate, &dtstart);
	_localtime64_s(&tmstop, &dtstop);

	m_year_create.SetWindowTextA(std::to_string(tmcreate.tm_year).c_str());
	m_month_create.SetWindowTextA(std::to_string(tmcreate.tm_mon).c_str());
	m_day_create.SetWindowTextA(std::to_string(tmcreate.tm_mday).c_str());
	m_hour_create.SetWindowTextA(std::to_string(tmcreate.tm_hour).c_str());
	m_min_create.SetWindowTextA(std::to_string(tmcreate.tm_min).c_str());
	m_sec_create.SetWindowTextA(std::to_string(tmcreate.tm_sec).c_str());

	m_year_stop.SetWindowTextA(std::to_string(tmstop.tm_year).c_str());
	m_month_stop.SetWindowTextA(std::to_string(tmstop.tm_mon).c_str());
	m_day_stop.SetWindowTextA(std::to_string(tmstop.tm_mday).c_str());
	m_hour_stop.SetWindowTextA(std::to_string(tmstop.tm_hour).c_str());
	m_min_stop.SetWindowTextA(std::to_string(tmstop.tm_min).c_str());
	m_sec_stop.SetWindowTextA(std::to_string(tmstop.tm_sec).c_str());

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
} // ///////////////////////////////////////////////////////////////////////////////////////
INT_PTR DlgMisc::doModal(structMiscCfg* in_data){
	data = in_data;
	INT_PTR ret = DoModal();
	if(ret == IDOK){
		in_data->curRndSeed = ForMfsControls::getUINT32FromCEdit(m_seed);
		in_data->curIteration = ForMfsControls::getUINT64FromCEdit(m_iteration);

		struct tm tmcreate, tmstop;

		tmcreate.tm_year = 1900 + ForMfsControls::getIntFromCEdit(m_year_create);
		tmcreate.tm_mon = 1 + ForMfsControls::getIntFromCEdit(m_month_create);
		tmcreate.tm_mday = ForMfsControls::getIntFromCEdit(m_day_create);
		tmcreate.tm_hour = ForMfsControls::getIntFromCEdit(m_hour_create);
		tmcreate.tm_min = ForMfsControls::getIntFromCEdit(m_min_create);
		tmcreate.tm_sec = ForMfsControls::getIntFromCEdit(m_sec_create);

		tmstop.tm_year = 1900 + ForMfsControls::getIntFromCEdit(m_year_stop);
		tmstop.tm_mon = 1 + ForMfsControls::getIntFromCEdit(m_month_stop);
		tmstop.tm_mday = ForMfsControls::getIntFromCEdit(m_day_stop);
		tmstop.tm_hour = ForMfsControls::getIntFromCEdit(m_hour_stop);
		tmstop.tm_min = ForMfsControls::getIntFromCEdit(m_min_stop);
		tmstop.tm_sec = ForMfsControls::getIntFromCEdit(m_sec_stop);

		in_data->dtCreate = _mktime64(&tmcreate);
		in_data->dtLastStop = _mktime64(&tmstop);
		in_data->sComments = ForMfsControls::getStrFromCEdit(m_comment);
	}
	return ret;
} // ///////////////////////////////////////////////////////////////////////////////////////
INT_PTR DlgMisc::DoModal(){
	return CDialog::DoModal();
} // ///////////////////////////////////////////////////////////////////////////////////////

