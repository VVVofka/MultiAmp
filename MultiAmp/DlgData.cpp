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
	size_t szall = szAreaX * szAreaY;
	float proc = (100.0f * curPointsCount) / szall;
	std::string sproc = float_to_str(proc);
	m_count_proc.SetWindowTextA(sproc.c_str());
	m_count_proc.UpdateWindow();
} // ///////////////////////////////////////////////////////////////////////////
BOOL DlgData::OnInitDialog(){
	CDialog::OnInitDialog();
	m_cnt_proc_type.SetCheck(BST_CHECKED);
	m_size_x.SetWindowTextA(razd(szAreaX).c_str());
	m_size_y.SetWindowTextA(razd(szAreaY).c_str());
	m_size.SetWindowTextA(razd(szAreaX * szAreaY).c_str());

	m_sigma.SetWindowTextA(sigma.c_str());
	m_seed.SetWindowTextA(seed.c_str());

	curPointsCount = voffset.size();
	std::string scnt = razd(curPointsCount);
	m_count_proc.SetWindowTextA(scnt.c_str());

	if(curPointsCount == 0){
		auto btCnt = (CButton*)GetDlgItem(IDC_FLG_DATA_COUNT);
		btCnt->SetCheck(0);

		auto btProc = (CButton*)GetDlgItem(IDC_FLG_DATA_PROC);
		btProc->SetCheck(1);
		m_count_proc.SetWindowTextA("1.5");

		auto btOK = (CButton*)GetDlgItem(IDOK);
		btOK->EnableWindow(0);
		btOK->UpdateWindow();
	}
	return TRUE;
} // ///////////////////////////////////////////////////////////////////////////
void DlgData::OnBnClickedOk(){
	CDialog::OnOK();
}  // ///////////////////////////////////////////////////////////////////////////
INT_PTR DlgData::DoModal(){
	return CDialog::DoModal();
}  // ///////////////////////////////////////////////////////////////////////////
INT_PTR DlgData::doModal(DlgDataData* in_data){
	szAreaX = in_data->szX;
	szAreaY = in_data->szY;

	sigma = *in_data->sigma;
	if(sigma.length() == 0)
		sigma = "0";

	seed = *in_data->seed;
	if(seed.length() == 0)
		seed = "012345";

	voffset = *in_data->voffset;

	INT_PTR ret = DoModal();
	if(ret == IDOK){
		*in_data->sigma = sigma;
		*in_data->seed = seed;
		*in_data->voffset = voffset;
	}
	return ret;
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
	SetDlgItemTextA(IDC_ST_DATA_STATUS, "WORK ...");
	GetDlgItem(IDC_BT_DATA_GENER)->EnableWindow(0);
	UpdateWindow();
	float fsigma = ForMfsControls::getFloatFromCEdit(m_sigma, &sigma);
	UINT32 useed = ForMfsControls::getUINT32FromCEdit(m_seed, &seed);
	curPointsCount = getNewPointsCount();
	bool suc = false;
	DlgDataData tmpdata;
	tmpdata.create(szAreaX, szAreaY, &voffset, &sigma, &seed);
	if(fsigma > 3.f || fsigma < 0.0001f)
		suc = tmpdata.generRndFlat(curPointsCount);
	else	//Normal dist
		suc = tmpdata.generRndNorm(curPointsCount, fsigma);
	if(suc){
		newdata = true;
		CWnd::FromHandle(m_screen.m_hWnd)->Invalidate();
		GetDlgItem(IDOK)->EnableWindow(1);
		SetDlgItemTextA(IDC_ST_DATA_STATUS, "SUCCESS");
	} else
		SetDlgItemTextA(IDC_ST_DATA_STATUS, "ERROR ! ! !");
	GetDlgItem(IDC_BT_DATA_GENER)->EnableWindow(1);
	UpdateWindow();
} // /////////////////////////////////////////////////////////////////////////////
size_t DlgData::getNewPointsCount(){
	auto btCnt = (CButton*)GetDlgItem(IDC_FLG_DATA_COUNT);
	auto btProc = (CButton*)GetDlgItem(IDC_FLG_DATA_PROC);
	if(btCnt->GetCheck() && !btProc->GetCheck()){	// count
		UINT32 value = ForMfsControls::getUINT32FromCEdit(m_count_proc);
		return size_t(value);
	} else if(!btCnt->GetCheck() && btProc->GetCheck()){
		float value = ForMfsControls::getFloatFromCEdit(m_count_proc);
		double ret = value * 0.01 * szAreaX * szAreaY + 0.5;
		return size_t(ret);	// %
	}return 0;
} // /////////////////////////////////////////////////////////////////////////////
std::string DlgData::float_to_str(float val){
	char buf[33];
	sprintf_s(buf, "%f", val);
	return std::string(buf);
} // //////////////////////////////////////////////////////////////////////////////
void DlgData::OnPaint(){
	if(newdata == false)
		return;
	newdata = false;
	CWnd* wnd = CWnd::FromHandle(m_screen.m_hWnd);
	CPaintDC dc(wnd);

	CRect r_CL;	// прямоугольник клиентской области
	m_screen.GetClientRect(&r_CL);

	const COLORREF colorPixel = RGB(96, 80, 0);
	const COLORREF colorBack = RGB(0, 0, 64);

	double maxSizePoint = (double)max(szAreaX, szAreaY);
	int pixelwidth = r_CL.Width();
	int pixelheigh = r_CL.Height();
	double kx = pixelwidth / maxSizePoint;
	double ky = pixelheigh / maxSizePoint;
	CRect r = r_CL;
	if(szAreaX > szAreaY){
		double k = (double)szAreaY / (double)szAreaX;
		r.top = LONG(pixelheigh * (1. - k) * 0.5);
		r.bottom = LONG(pixelheigh * (1. + k) * 0.5);
	} else 	if(szAreaY > szAreaX){
		double k = (double)szAreaX / (double)szAreaY;
		r.left = LONG(pixelwidth * (1. - k) * 0.5);
		r.right = LONG(pixelwidth * (1. + k) * 0.5);
	}
	dc.FillSolidRect(r, colorBack);		// fill background

	typedef std::map<size_t, COLORREF> MyMap;
	MyMap mymap;
	std::vector<size_t> vsort;
	vsort.reserve(pixelwidth * pixelheigh);

	for(size_t j = 0; j < voffset.size(); j++){
		size_t pixelx = size_t(kx * (voffset[j] % szAreaX));		//size_t pixelx = size_t(kx * tmpdata->getPosXid(j));
		size_t pixely = size_t(ky * (voffset[j] / szAreaX));
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
		dc.SetPixel(r.left + pixelx, r.top + pixely, mymap.find(i)->second);
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
