// MultiAmpDlg.cpp : implementation file
#include "pch.h"
#include "framework.h"
#include "MultiAmp.h"
#include "MultiAmpDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX){
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX){
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CMultiAmpDlg dialog


CMultiAmpDlg::CMultiAmpDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MULTIAMP_DIALOG, pParent){
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMultiAmpDlg::DoDataExchange(CDataExchange* pDX){
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMultiAmpDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMultiAmpDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMultiAmpDlg message handlers

BOOL CMultiAmpDlg::OnInitDialog(){
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if(pSysMenu != nullptr){
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if(!strAboutMenu.IsEmpty()){
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMultiAmpDlg::OnSysCommand(UINT nID, LPARAM lParam){
	if((nID & 0xFFF0) == IDM_ABOUTBOX){
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	} else{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMultiAmpDlg::OnPaint(){
	if(IsIconic()){
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	} else{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMultiAmpDlg::OnQueryDragIcon(){
	return static_cast<HCURSOR>(m_hIcon);
} // /////////////////////////////////////////////////////////////////////////////////////

void CMultiAmpDlg::OnBnClickedButton1(){
	HMODULE hLib;
/*
#ifdef DEBUG
#ifdef _WIN64
	auto spath = TEXT("c:\\Prog\\CPP\\MultiAmp\\x64\\Debug\\WinDxDLL.dll");
#else // _WIN64
	auto spath = TEXT("c:\\Prog\\CPP\\MultiAmp\\Win32\\Debug\\WinDxDLL.dll");
#endif // _WIN64
#else // DEBUG
#ifdef _WIN64
	auto spath = TEXT("c:\\Prog\\CPP\\MultiAmp\\x64\\Release\\WinDxDLL.dll");
	// c:\Prog\CPP\MultiAmp\x64\Release\WinDxDLL.dll 
#else // _WIN64
	auto spath = TEXT("c:\\Prog\\CPP\\MultiAmp\\Win32\\Release\\WinDxDLL.dll");
#endif // _WIN64 
#endif // DEBUG
	*/
	auto dllname = dllName();
	auto spath = TEXT(dllname.c_str());
	hLib = LoadLibrary(spath);
	if(hLib != NULL){
		int (*pFunction)(HINSTANCE hInstance, int nCmdShow, int a, int b) = NULL;
		(FARPROC&)pFunction = GetProcAddress(hLib, "openWindow1");   // tstdll
		if(pFunction != NULL){
			int ret = pFunction(AfxGetApp()->m_hInstance, SW_SHOWDEFAULT, 3, 5);
			//_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
			//_RPT1(_CRT_WARN, "%d\n", ret);
		} else{
			MessageBox(spath, TEXT("openWindow1 from WinDxDLL.dll not loaded!"), MB_ICONERROR);
		}
	} else{
		MessageBox(spath, TEXT("WinDxDLL.dll not loaded!"), MB_ICONERROR);
	}
} // ////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string CMultiAmpDlg::dllName(){
	std::string fHelpPathName(AfxGetApp()->m_pszHelpFilePath);
	auto lenPath = fHelpPathName.length();

	std::string fName("WinDxDLL.dll");	// Lenght WinDxDLL.dll == MultiAmp.HLP
	auto lenName = fName.length();

	auto start = lenPath - lenName;
	return fHelpPathName.replace(start, lenName, fName);
} // ///////////////////////////////////////////////////////////////////////////////////////////////////////////
