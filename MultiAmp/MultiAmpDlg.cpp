#include "pch.h"
#include "framework.h"
#include "MultiAmp.h"
#include "MultiAmpDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "DlgCfgLays.h"
#include "DlgData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

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
	ON_BN_CLICKED(IDC_BUTTON1, &CMultiAmpDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BT_JSON, &CMultiAmpDlg::OnBnClickedBtJson)
	ON_BN_CLICKED(IDC_BT_MASK_A, &CMultiAmpDlg::OnBnClickedBtMaskA)
	ON_BN_CLICKED(IDOK, &CMultiAmpDlg::OnBnClickedOk)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BT_MASK_F, &CMultiAmpDlg::OnBnClickedBtMaskF)
	ON_BN_CLICKED(IDC_BT_LAYS, &CMultiAmpDlg::OnBnClickedBtLays)
	ON_BN_CLICKED(IDC_BT_DATA, &CMultiAmpDlg::OnBnClickedBtData)
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
void CMultiAmpDlg::OnBnClickedButton1(){
	HMODULE hLib;
	auto dllname = dllName();
	auto spath = TEXT(dllname.c_str());
	hLib = LoadLibrary(spath);
	if(hLib != NULL){
		int (*pFunction)(HINSTANCE hInstance, int nCmdShow, char* json_out, char* json_in) = NULL;
		(FARPROC&)pFunction = GetProcAddress(hLib, "openWindow1json");   // tstdll
		if(pFunction != NULL){
			int ret = pFunction(AfxGetApp()->m_hInstance, SW_SHOWDEFAULT, json_out, json_in);
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
void CMultiAmpDlg::OnBnClickedBtJson(){
	const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
	Document d;
	d.Parse(json);

	// 2. Modify it by DOM.
	Value& s = d["stars"];
	s.SetInt(s.GetInt() + 1);

	// 3. Stringify the DOM
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	d.Accept(writer);

	// Output {"project":"rapidjson","stars":11}
	_RPT0(0, buffer.GetString());
	//std::cout << buffer.GetString() << std::endl;
} // ///////////////////////////////////////////////////////////////////////////////////////////////////////////
void CMultiAmpDlg::OnTimer(UINT_PTR nIDEvent){
	if(json_in[0] == (char)255){
		_RPT1(0, "%s\n", json_in + 1);
		SetWindowTextA(json_in + 1);
		json_in[0] = (char)0;
	}
	CDialogEx::OnTimer(nIDEvent);
} // /////////////////////////////////////////////////////////
void CMultiAmpDlg::OnBnClickedOk(){
	CDialogEx::OnOK(); 
}  // /////////////////////////////////////////////////////////
void CMultiAmpDlg::OnBnClickedBtMaskA(){
	auto maskA = getMaskA("tstDlg.xml");
	DlgMaskA dlgmaska;
	auto newmask = dlgmaska.doModal(maskA);
	GetDlgItem(IDC_MAINDLG_INFO)->SetWindowTextA(newmask.c_str());
	setMaskA("tstDlg.xml", newmask.c_str());
} // /////////////////////////////////////////////////////////
void CMultiAmpDlg::OnBnClickedBtMaskF(){
	auto maskF = getMaskF("tstDlg.xml");
	DlgMaskF dlgmaskf;
	std::string newmask = dlgmaskf.doModal(maskF);
	std::string newmaskall;
	for(size_t j = 0; j < 16; j++){
		newmaskall += (j ? "\n" : "") + std::to_string(j) + (j <= 9 ? ":  " : ":");
		for(size_t i = 0; i < 4; i++)
			newmaskall += ' ' + newmask.substr(j * 16 + i * 4, 4);
	}
	GetDlgItem(IDC_MAINDLG_INFO)->SetWindowTextA(newmaskall.c_str());

	setMaskF("tstDlg.xml", newmask.c_str());
}  // /////////////////////////////////////////////////////////
void CMultiAmpDlg::OnBnClickedBtLays(){
	structLaysCfg layscfg = getLaysCfg("tstDlg.xml");
	DlgCfgLays dlgcfgLays;
	structLaysCfg ret = dlgcfgLays.doModal(layscfg);
	setLaysCfg("tstDlg.xml", ret);
}  // /////////////////////////////////////////////////////////
void CMultiAmpDlg::OnBnClickedBtData(){
	structLaysCfg layscfg = getLaysCfg("tstDlg.xml");
	structDataCfg datacfg = getDataCfg("tstDlg.xml");
	DlgData dlgdata;
	DlgDataData data;
	datacfg.v
	data.create(layscfg.bottomX(), layscfg.bottomY(), datacfg.v.size(), datacfg.sigma);
	dlgdata.doModal(&data);
} // /////////////////////////////////////////////////////////////////////////////////
