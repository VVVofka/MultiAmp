#pragma once


// Диалоговое окно DlgMaskAFull

class DlgMaskAFull : public CDialogEx
{
	DECLARE_DYNAMIC(DlgMaskAFull)

public:
	DlgMaskAFull(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~DlgMaskAFull();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPTIONS_MASK_A_FULL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
};
