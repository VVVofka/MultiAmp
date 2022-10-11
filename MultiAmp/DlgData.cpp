#include "pch.h"
#include <map>
#include "MultiAmp.h"
#include "DlgData.h"
#include "afxdialogex.h"
#include "EasyBMP.h"
//#include "myRnd.h"
#include "Utils.h"
IMPLEMENT_DYNAMIC(DlgData, CDialog)

DlgData::DlgData(CWnd* pParent /*=nullptr*/) : CDialog(IDD_DATA, pParent){} // ///////////////////////////////////////////////////////////////////////////
DlgData::~DlgData(){}

void DlgData::DoDataExchange(CDataExchange* pDX){
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TXT_DATA_SIZE_X, m_size_x);
	DDX_Control(pDX, IDC_TXT_DATA_SIZE_Y, m_size_y);
	DDX_Control(pDX, IDC_TXT_DATA_SIZE_ALL, m_size);
	DDX_Control(pDX, IDC_TXT_DATA_COUNT_PROC, m_count_proc);
	DDX_Control(pDX, IDC_FLG_DATA_COUNT, m_cnt_proc_type);
	DDX_Control(pDX, IDC_TXT_DATA_SIGMA, m_sigma);
	DDX_Control(pDX, IDC_PCT_DATA_SCREEN, m_screen);
	DDX_Control(pDX, IDC_TXT_DATA_RNDSEED, m_seed);
} // ///////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(DlgData, CDialog)
	ON_BN_CLICKED(IDC_FLG_DATA_COUNT, &DlgData::OnBnClickedFlgDataCount)
	ON_BN_CLICKED(IDC_FLG_DATA_PROC, &DlgData::OnBnClickedFlgDataProc)
	ON_BN_CLICKED(IDOK, &DlgData::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BT_DATA_GENER, &DlgData::OnBnClickedBtDataGener)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BT_DADA_GEN_RNDSEED, &DlgData::OnBnClickedBtDadaGenRndseed)
END_MESSAGE_MAP()

// DlgData message handlers
void DlgData::OnBnClickedFlgDataCount(){
	std::string scnt = razd(curPointsCount);
	m_count_proc.SetWindowTextA(scnt.c_str());
	m_count_proc.UpdateWindow();
} // ///////////////////////////////////////////////////////////////////////////
void DlgData::OnBnClickedFlgDataProc(){
	size_t szall = data->szAll();
	float proc = (100.0f * curPointsCount) / szall;
	std::string sproc = float_to_str(proc, 3);
	m_count_proc.SetWindowTextA(sproc.c_str());
	m_count_proc.UpdateWindow();
} // ///////////////////////////////////////////////////////////////////////////
BOOL DlgData::OnInitDialog(){
	CDialog::OnInitDialog();
	m_cnt_proc_type.SetCheck(BST_CHECKED);
	m_size_x.SetWindowTextA(razd(data->szX).c_str());
	m_size_y.SetWindowTextA(razd(data->szY).c_str());
	m_size.SetWindowTextA(razd(data->szAll()).c_str());

	std::string ssigma = float_to_str(*data->sigma, 3);
	m_sigma.SetWindowTextA(ssigma.c_str());

	curPointsCount = data->cnt();
	std::string scnt = razd(curPointsCount);
	m_count_proc.SetWindowTextA(scnt.c_str());

	return TRUE;
} // ///////////////////////////////////////////////////////////////////////////
void DlgData::OnBnClickedOk(){
	CDialog::OnOK();
}  // ///////////////////////////////////////////////////////////////////////////
INT_PTR DlgData::DoModal(){
	return CDialog::DoModal();
}  // ///////////////////////////////////////////////////////////////////////////
INT_PTR DlgData::doModal(DlgDataData* in_data){
	data = in_data;
	return DoModal();
}  // ///////////////////////////////////////////////////////////////////////////
std::string DlgData::razd(size_t u){
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
void DlgData::OnBnClickedBtDataGener(){
	*data->sigma = ForMfsControls::getFloatFromCEdit(m_sigma);
	curPointsCount = getNewPointsCount();
	bool suc = false;
	if(*data->sigma < 0.1f)
		suc = data->generRndFlat(curPointsCount);
//	float proc = (float)curPointsCount / data->szAll();
//	data->create(data->szX, data->szY, proc, sigma);	//data.create(1024, 1024, 0.01f, 0.4f);
	newdata = true;
	CWnd::FromHandle(m_screen.m_hWnd)->Invalidate();
} // /////////////////////////////////////////////////////////////////////////////
size_t DlgData::getNewPointsCount(){
	int z = m_cnt_proc_type.GetCheck();
	float value = ForMfsControls::getFloatFromCEdit(m_count_proc);
	if(z == BST_CHECKED)
		return size_t(value);	// count
	return size_t(value * 0.01 * data->szAll() + 0.5);	// %
} // /////////////////////////////////////////////////////////////////////////////
//float DlgData::getFloatFromCEdit(CEdit& edit){
//	CString sb;
//	edit.GetWindowTextA(sb);
//	sb.Replace(" ", "");
//	sb.Replace(',', '.');
//	return std::strtof((LPCSTR)sb, NULL);
//} // //////////////////////////////////////////////////////////////////////////////
//float DlgData::getFloatFromCEdit(CEdit& edit){
//	CString sb;
//	edit.GetWindowTextA(sb);
//	sb.Replace(" ", "");
//	sb.Replace(',', '.');
//	return std::strtof((LPCSTR)sb, NULL);
//} // //////////////////////////////////////////////////////////////////////////////
std::string DlgData::float_to_str(float val, int digits){
	char buf[_CVTBUFSIZE];
	int err = _gcvt_s(buf, _CVTBUFSIZE, val, digits);
	if(err != 0){
		printf("_gcvt_s failed with error code %d\n", err);
		return "";
	}
	return buf;
} // //////////////////////////////////////////////////////////////////////////////
void DlgData::OnPaint(){
	if(newdata == false)
		return;
	newdata = false;
	CWnd* wnd = CWnd::FromHandle(m_screen.m_hWnd);
	CPaintDC dc(wnd);

	CRect r_CL;	// прямоугольник клиентской области
	m_screen.GetClientRect(&r_CL);

	const COLORREF colorPixel = RGB(70, 64, 0);
	const COLORREF colorBack = RGB(0, 0, 48);

	dc.FillSolidRect(r_CL, colorBack);		// fill background

	double maxSizePoint = (double)max(data->szX, data->szY);
	int pixelwidth = r_CL.Width();
	int pixelheigh = r_CL.Height();
	double kx = pixelwidth / maxSizePoint;
	double ky = pixelheigh / maxSizePoint;

	typedef std::map<size_t, COLORREF> MyMap;
	MyMap mymap;
	std::vector<size_t> vsort;
	vsort.reserve(pixelwidth * pixelheigh);

	for(size_t j = 0; j < data->voffset->size(); j++){
		size_t pixelx = size_t(kx * data->getPosXid(j));
		size_t pixely = size_t(ky * data->getPosYid(j));
		size_t key = pixelx + pixely * pixelwidth;
		MyMap::iterator it = mymap.find(key);
		if(it == mymap.end()){
			mymap.insert(MyMap::value_type(key, colorPixel));
			vsort.push_back(key);
		} else{
			BYTE r = incColor(GetRValue(it->second));
			BYTE g = incColor(GetGValue(it->second));
			it->second = RGB(r, g, 0);
		}
	}
	for(const size_t i : vsort){
		int pixelx = i % pixelwidth;
		int pixely = i / pixelwidth;
		dc.SetPixel(pixelx, pixely, mymap.find(i)->second);
	}
} // //////////////////////////////////////////////////////////////////////////////
BYTE DlgData::incColor(BYTE clr){
	const unsigned step = 64;
	unsigned c = clr + step;
	if(c > 255)
		return BYTE(clr + (255 - clr) * 0.5);
	return BYTE(c);
} // //////////////////////////////////////////////////////////////////////////////
void DlgData::OnBnClickedBtDadaGenRndseed(){
	srand((unsigned)time(NULL));
	auto rnd = rand();
	m_seed.SetWindowTextA(std::to_string(rnd).c_str());
	m_seed.UpdateWindow();
} // //////////////////////////////////////////////////////////////////////////////
