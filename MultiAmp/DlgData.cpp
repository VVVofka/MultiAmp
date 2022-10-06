#include "pch.h"
#include "MultiAmp.h"
#include "DlgData.h"
#include "afxdialogex.h"

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
} // ///////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(DlgData, CDialog)
	ON_BN_CLICKED(IDC_FLG_DATA_COUNT, &DlgData::OnBnClickedFlgDataCount)
	ON_BN_CLICKED(IDC_FLG_DATA_PROC, &DlgData::OnBnClickedFlgDataProc)
	ON_BN_CLICKED(IDOK, &DlgData::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BT_DATA_GENER, &DlgData::OnBnClickedBtDataGener)
END_MESSAGE_MAP()

// DlgData message handlers
void DlgData::OnBnClickedFlgDataCount(){
	size_t cnt = (size_t)data->cnt();
	m_count_proc.SetWindowTextA(razd(cnt).c_str());
} // ///////////////////////////////////////////////////////////////////////////
void DlgData::OnBnClickedFlgDataProc(){
	int cntproc = (100 * data->cnt()) / data->szAll();
	m_count_proc.SetWindowTextA(std::to_string(cntproc).c_str());
} // ///////////////////////////////////////////////////////////////////////////
BOOL DlgData::OnInitDialog(){
	CDialog::OnInitDialog();
	m_cnt_proc_type.SetState(1);
	m_size_x.SetWindowTextA(razd(data->szX).c_str());
	m_size_y.SetWindowTextA(razd(data->szY).c_str());
	m_size.SetWindowTextA(razd(data->szAll()).c_str());
	std::string ssigma = float_to_str(data->sigma, 3);
	m_sigma.SetWindowTextA(ssigma.c_str());
	OnBnClickedFlgDataCount();
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
	float sigma = getSigma();
	size_t val = getVal();
	float proc = (float)(0.5 + (double)val / data->szAll());
	data->create(data->szX, data->szY, proc, sigma);
	drawScr(std::vector<DlgDataDataItem>);
} // /////////////////////////////////////////////////////////////////////////////
size_t DlgData::getVal(){
	UINT z = m_cnt_proc_type.GetState();
	BOOL* lpTrans = FALSE;
	UINT val = GetDlgItemInt(IDC_TXT_DATA_COUNT_PROC, lpTrans, FALSE);
	if(z == 0)	// %
		return val * 0.01 * data->szAll();
	return val;
} // /////////////////////////////////////////////////////////////////////////////
float DlgData::getSigma(){
	CString sb;
	m_sigma.GetWindowTextA(sb);
	sb.Replace(" ", "");
	sb.Replace(',', '.');
	std::string s(sb);
	char* stopstring;
	float sigma = std::strtof(s.c_str(), &stopstring);
	return sigma;
} // /////////////////////////////////////////////////////////////////////////////
std::string DlgData::float_to_str(float val, int digits){
	char buf[_CVTBUFSIZE];
	int err = _gcvt_s(buf, _CVTBUFSIZE, val, digits);
	if(err != 0){
		printf("_gcvt_s failed with error code %d\n", err);
		return "";
	}
	return buf;
} // //////////////////////////////////////////////////////////////////////////////
void DlgData::drawScr(std::vector<DlgDataDataItem>, size_t sz_x, size_t sz_y, UINT id_control){

} // //////////////////////////////////////////////////////////////////////////////
