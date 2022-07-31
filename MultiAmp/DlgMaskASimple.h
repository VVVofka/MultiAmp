#pragma once
#include <string>

// https://rapidjson.org/
#include "../Common/include/rapidjson/document.h"
#include "../Common/include/rapidjson/writer.h"
#include "../Common/include/rapidjson/stringbuffer.h"
namespace options::maska{
	using namespace rapidjson;

	class DlgMaskASimple : public CDialogEx{
		DECLARE_DYNAMIC(DlgMaskASimple)
		std::string sin;

	public:
		DlgMaskASimple(CWnd* pParent = nullptr);   // стандартный конструктор
		virtual ~DlgMaskASimple();

		// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
		enum{ IDD = IDD_OPTIONS_MASK_A };
#endif

		INT_PTR myDoModal(std::string& sjson);

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV
		DECLARE_MESSAGE_MAP()
	public:
		afx_msg void OnBnClickedButton1();
		virtual void OnCancel();
	};
}
