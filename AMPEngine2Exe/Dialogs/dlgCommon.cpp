#include "..\framework.h"
#include "dlgCommon.h"
#include "afxdialogex.h"
#include "..\resource.h"
#include "DlgCfgLays.h"
#include "DlgData.h"
#include "DlgMisc.h"

// CMultiAmpDlg dialog
CMultiAmpDlg::CMultiAmpDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MULTIAMP_DIALOG, pParent){
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
} // /////////////////////////////////////////////////////////
void CMultiAmpDlg::DoDataExchange(CDataExchange* pDX){
	CDialogEx::DoDataExchange(pDX);
} // /////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CMultiAmpDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BT_MASK_A, &CMultiAmpDlg::OnBnClickedBtMaskA)
	ON_BN_CLICKED(IDOK, &CMultiAmpDlg::OnBnClickedOk)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BT_MASK_F, &CMultiAmpDlg::OnBnClickedBtMaskF)
	ON_BN_CLICKED(IDC_BT_LAYS, &CMultiAmpDlg::OnBnClickedBtLays)
	ON_BN_CLICKED(IDC_BT_DATA, &CMultiAmpDlg::OnBnClickedBtData)
	ON_BN_CLICKED(IDC_BT_DATA_MISC, &CMultiAmpDlg::OnBnClickedBtDataMisc)
	ON_BN_CLICKED(IDC_BT_MAIN_RUN, &CMultiAmpDlg::OnBnClickedBtMainRun)
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
	SetTimer(ID_TIMER_1, 1000, NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
} // /////////////////////////////////////////////////////////
void CMultiAmpDlg::OnSysCommand(UINT nID, LPARAM lParam){
	CDialogEx::OnSysCommand(nID, lParam);
} // /////////////////////////////////////////////////////////
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
}  // /////////////////////////////////////////////////////////
// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMultiAmpDlg::OnQueryDragIcon(){
	return static_cast<HCURSOR>(m_hIcon);
} // /////////////////////////////////////////////////////////////////////////////////////
std::string CMultiAmpDlg::dllName(){
	std::string fHelpPathName(AfxGetApp()->m_pszHelpFilePath);
	auto lenPath = fHelpPathName.length();
	std::string fName("WinDxDLL.dll");	// Lenght WinDxDLL.dll == MultiAmp.HLP
	auto lenName = fName.length();

	auto start = lenPath - lenName;
	return fHelpPathName.replace(start, lenName, fName);
} // ///////////////////////////////////////////////////////////////////////////////////////////////////////////
void CMultiAmpDlg::OnTimer(UINT_PTR nIDEvent){
	if(json_in[0] == (char)255){
		_RPT1(0, "%s\n", json_in + 1);
		SetWindowTextA(json_in + 1);
		json_in[0] = (char)0;
	}
	CDialogEx::OnTimer(nIDEvent);
} // ///////////////////////////////////////////////////////////////////////////////////////
void CMultiAmpDlg::OnBnClickedOk(){
	CDialogEx::OnOK();
}  // ///////////////////////////////////////////////////////////////////////////////////////
void CMultiAmpDlg::OnBnClickedBtMaskA(){
	std::string maskA = getxml::getMaskA("tstDlg.xml");		// InPort.cpp
	DlgMaskA dlgmaska;
	auto newmask = dlgmaska.doModal(maskA);
	GetDlgItem(IDC_MAINDLG_INFO)->SetWindowTextA(newmask.c_str());
	getxml::setMaskA("tstDlg.xml", newmask.c_str());
} // ///////////////////////////////////////////////////////////////////////////////////////
void CMultiAmpDlg::OnBnClickedBtMaskF(){
	auto maskF = getxml::getMaskF("tstDlg.xml");		// InPort.cpp
	DlgMaskF dlgmaskf;
	std::string newmask = dlgmaskf.doModal(maskF);
	std::string newmaskall;
	for(size_t j = 0; j < 16; j++){
		newmaskall += (j ? "\n" : "") + std::to_string(j) + (j <= 9 ? ":  " : ":");
		for(size_t i = 0; i < 4; i++)
			newmaskall += ' ' + newmask.substr(j * 16 + i * 4, 4);
	}
	GetDlgItem(IDC_MAINDLG_INFO)->SetWindowTextA(newmaskall.c_str());

	getxml::setMaskF("tstDlg.xml", newmask.c_str());		// InPort.cpp
}  // ///////////////////////////////////////////////////////////////////////////////////////
void CMultiAmpDlg::OnBnClickedBtLays(){
	cfg_all.lays = getxml::getLaysCfg("tstDlg.xml");		// InPort.cpp
	DlgCfgLays dlgcfgLays;
	structLaysCfg ret = dlgcfgLays.doModal(cfg_all.lays);
	if(cfg_all.lays.laysCnt() != ret.laysCnt() ||
		cfg_all.lays.topX != ret.topX ||
		cfg_all.lays.topY != ret.topY)
		getxml::clearDataCfg("tstDlg.xml");		// InPort.cpp
	getxml::setLaysCfg("tstDlg.xml", ret);		// InPort.cpp
}  // /////////////////////////////////////////////////////////
void CMultiAmpDlg::OnBnClickedBtData(){
	cfg_all.lays = getxml::getLaysCfg("tstDlg.xml");
	cfg_all.data = getxml::getDataCfg("tstDlg.xml");
	DlgData dlgdata;
	DlgDataData data;
	auto szx = cfg_all.lays.bottomX();
	auto szy = cfg_all.lays.bottomY();
	data.create(szx, szy, &cfg_all.data.v, &cfg_all.data.sigma, &cfg_all.data.seed);
	INT_PTR ret = dlgdata.doModal(&data);
	if(ret == IDOK)
		getxml::setDataCfg("tstDlg.xml", cfg_all.data);			// InPort.cpp
} // /////////////////////////////////////////////////////////////////////////////////
void CMultiAmpDlg::OnBnClickedBtDataMisc(){
	DlgMisc dlgmisc;
	cfg_all.misc = getxml::getMiscCfg("tstDlg.xml");
	//_tzset();	_time64(&misccfg.dtCreate);

	INT_PTR ret = dlgmisc.doModal(&cfg_all.misc);
	if(ret == IDOK)
		getxml::setMiscCfg("tstDlg.xml", cfg_all.misc);
} // /////////////////////////////////////////////////////////////////////////////////

void CMultiAmpDlg::OnBnClickedBtMainRun(){
	cfg_all.load("tstDlg.xml");
	HMODULE hLib;
	auto dllname = dllName();
	auto spath = TEXT(dllname.c_str());
	hLib = LoadLibrary(spath);
	if(hLib != NULL){
		int (*pFunction)(HINSTANCE hInstance, int nCmdShow, structAll * cfg_all) = NULL;
		(FARPROC&)pFunction = GetProcAddress(hLib, "openWindow1json");   // tstdll
		if(pFunction != NULL){
			int ret = pFunction(AfxGetApp()->m_hInstance, SW_SHOWDEFAULT, &cfg_all);
			//_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
			//_RPT1(_CRT_WARN, "%d\n", ret);
		} else{
			MessageBox(spath, TEXT("openWindow1 from WinDxDLL.dll not loaded!"), MB_ICONERROR);
		}
	} else{
		MessageBox(spath, TEXT("WinDxDLL.dll not loaded!"), MB_ICONERROR);
	}
} // /////////////////////////////////////////////////////////////////////////////////