#include "pch.h"
#include "MultiAmp.h"
#include "DlgMaskF.h"
#include "afxdialogex.h"
#include "CMCell4.h"
// DlgMaskF dialog

IMPLEMENT_DYNAMIC(DlgMaskF, CDialogEx)

DlgMaskF::DlgMaskF(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_MASK_F, pParent){}

DlgMaskF::~DlgMaskF(){}

void DlgMaskF::DoDataExchange(CDataExchange* pDX){
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ST_CELL4, c4);
}


BEGIN_MESSAGE_MAP(DlgMaskF, CDialogEx)
	ON_WM_WINDOWPOSCHANGED()
	ON_BN_CLICKED(IDC_BUTTON2, &DlgMaskF::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &DlgMaskF::OnBnClickedButton3)
END_MESSAGE_MAP()

// DlgMaskF message handlers

void DlgMaskF::OnWindowPosChanged(WINDOWPOS* lpwndpos){
	CDialogEx::OnWindowPosChanged(lpwndpos);
	// TODO: Add your message handler code here
	//c4.create();
	ResizeControl();
} // //////////////////////////////////////////////////////////////////////////////
void DlgMaskF::ResizeControl(){
	return;
	// �������� �������� � ������� �������
	CRect mainRect; // ������������� �������
	GetClientRect(&mainRect); // ������������� ���������� �� �������

	int n = 23; // ������ �� ����
	CRect contRect; // ������������� ��������
	contRect.left = mainRect.left + n;
	contRect.top = mainRect.top + n;
	contRect.right = mainRect.right - n;
	contRect.bottom = mainRect.bottom - n;

	// ���� ���� "�������������" � ������������
	if(contRect.left > contRect.right)contRect.left = contRect.right;
	if(contRect.top > contRect.bottom)contRect.top = contRect.bottom;

	// ������� �� ������������������: ����� ��������������� �������� ��������,
	// ��� ��������� �� ����� ���� ����������. � ������ ������ ��� �����������,
	// ��������� ������� ����, �� � ������ ��� �������� � ������������ � ��������.
	// �� ��� ���������� ��-���� ��� �������:)
	CRect currRect; // ������� ������������� �������� � ���������� �����������
	CRect newRect; // ��������������� ������������� � ���������� �����������
	{
		// �������� ���������� ���������� ��������
		c4.GetWindowRect(&currRect);

		// ���������� contRect �� ���������� ����������
		// ����� CRect � ������������ ������� CPoint[2]
		newRect = contRect;
		::MapWindowPoints(m_hWnd, 0, (CPoint*)&newRect, 2);
	}

	if(currRect != newRect){
		// ����� ����� ������ � ���������
		c4.MoveWindow(&contRect, 0);
		_RPT4(0, "%d x %d    %d x %d\n", contRect.left, contRect.top, contRect.right, contRect.bottom);
		c4.Invalidate();
		Invalidate();   	// ����������� ����� �������
	}
} // ////////////////////////////////////////////////////////////////////////
void DlgMaskF::OnBnClickedButton2(){
	//m_CELL_000.rotate();
} // ////////////////////////////////////////////////////////////////////////
void DlgMaskF::OnBnClickedButton3(){
	//m_CELL_000.rotate(-1);
} // ////////////////////////////////////////////////////////////////////////


void DlgMaskF::PreInitDialog(){
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::PreInitDialog();
}


BOOL DlgMaskF::OnInitDialog(){
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	c4.create();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
