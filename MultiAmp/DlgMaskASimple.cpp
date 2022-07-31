#include "pch.h"
#include "framework.h"
#include "MultiAmp.h"
#include "DlgMaskASimple.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
namespace options::maska{
	IMPLEMENT_DYNAMIC(DlgMaskASimple, CDialogEx)

		DlgMaskASimple::DlgMaskASimple(CWnd* pParent /*=nullptr*/)
		: CDialogEx(IDD_OPTIONS_MASK_A, pParent){}

	DlgMaskASimple::~DlgMaskASimple(){}

	void DlgMaskASimple::DoDataExchange(CDataExchange* pDX){
		CDialogEx::DoDataExchange(pDX);
	}

	BEGIN_MESSAGE_MAP(DlgMaskASimple, CDialogEx)
		ON_BN_CLICKED(IDC_BUTTON1, &DlgMaskASimple::OnBnClickedButton1)
	END_MESSAGE_MAP()

	// Обработчики сообщений DlgMaskASimple
	void DlgMaskASimple::OnBnClickedButton1(){
		// TODO: добавьте свой код обработчика уведомлений
		_RPT0(0, "He-he");
	}
	void DlgMaskASimple::OnCancel(){
		// TODO: добавьте специализированный код или вызов базового класса

		CDialogEx::OnCancel();
	}
	INT_PTR DlgMaskASimple::myDoModal(std::string& json){
		sin = json;
		CDialogEx::DoModal();
		std::string cout(sin); //TODO: fill from ctrls

		if(cout.size() <= 0) return -1;
		char* buf = cout.data();
		Document document;  // Default template parameter uses UTF8 and MemoryPoolAllocator.
		if(document.ParseInsitu(buf).HasParseError())
			return -1;

		const Value& a = document["MaskA"]; // Using a reference for consecutive access is handy and faster.
		assert(a.IsArray());
		for(SizeType i = 0; i < a.Size(); i++) // rapidjson uses SizeType instead of size_t.
			_RPT2(0, "a[%d] = %d\n", i, a[i].GetInt());

		return sin != cout ? IDOK : IDCANCEL;
	} // ////////////////////////////////////////////////////////////////////////////
}	//	namespace options::maska{
