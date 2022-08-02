// Диалоговое окно DlgMaskAFull
#include "pch.h"
#include "MultiAmp.h"
#include "DlgMaskAFull.h"
#include "afxdialogex.h"
namespace options::maska{

	IMPLEMENT_DYNAMIC(DlgMaskAFull, CDialogEx)

		DlgMaskAFull::DlgMaskAFull(CWnd* pParent /*=nullptr*/)
		: CDialogEx(IDD_OPTIONS_MASK_A_FULL, pParent){

	}

	DlgMaskAFull::~DlgMaskAFull(){}

	void DlgMaskAFull::DoDataExchange(CDataExchange* pDX){
		CDialogEx::DoDataExchange(pDX);
	}


	BEGIN_MESSAGE_MAP(DlgMaskAFull, CDialogEx)
	END_MESSAGE_MAP()


	// Обработчики сообщений DlgMaskAFull
}