// DlgMisc.cpp : implementation file
//

#include "pch.h"
#include "MultiAmp.h"
#include "DlgMisc.h"
#include "afxdialogex.h"


// DlgMisc dialog

IMPLEMENT_DYNAMIC(DlgMisc, CDialog)

DlgMisc::DlgMisc(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DLG_MISC, pParent)
{

}

DlgMisc::~DlgMisc()
{
}

void DlgMisc::DoDataExchange(CDataExchange* pDX)
{
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
	DDX_Control(pDX, IDC_ED_MISC_DTSTOP_YEAR, m_tear_stop);
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
