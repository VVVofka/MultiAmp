#pragma once
class DlgMisc : public CDialog{
	DECLARE_DYNAMIC(DlgMisc)

public:
	DlgMisc(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DlgMisc();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_DLG_MISC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_seed;
	CEdit m_iteration;
	CEdit m_tick_create;
	CEdit m_year_create;
	CEdit m_month_create;
	CEdit m_day_create;
	CEdit m_hour_create;
	CEdit m_min_create;
	CEdit m_sec_create;
	CEdit m_tick_stop;
	CEdit m_tear_stop;
	CEdit m_month_stop;
	CEdit m_day_stop;
	CEdit m_hour_stop;
	CEdit m_min_stop;
	CEdit m_sec_stop;
	CEdit m_comment;
}; // ######################################################################################
