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
	DDX_Control(pDX, IDC_STCELL000, m_CELL_000);
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
		m_CELL_000.GetWindowRect(&currRect);

		// ���������� contRect �� ���������� ����������
		// ����� CRect � ������������ ������� CPoint[2]
		newRect = contRect;
		::MapWindowPoints(m_hWnd, 0, (CPoint*)&newRect, 2);
	}

	if(currRect != newRect){
		// ����� ����� ������ � ���������
		m_CELL_000.MoveWindow(&contRect, 0);
		_RPT4(0, "%d x %d    %d x %d\n", contRect.left, contRect.top, contRect.right, contRect.bottom);
		m_CELL_000.Invalidate();
		Invalidate();   	// ����������� ����� �������
	}
} // ////////////////////////////////////////////////////////////////////////
void DlgMaskF::OnBnClickedButton2(){
	m_CELL_000.nextIdx();
} // ////////////////////////////////////////////////////////////////////////
void DlgMaskF::OnBnClickedButton3(){
	m_CELL_000.nextIdx(-1);
} // ////////////////////////////////////////////////////////////////////////
