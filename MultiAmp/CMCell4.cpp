#include "pch.h"
#include "MultiAmp.h"
#include "CMCell4.h"

BEGIN_MESSAGE_MAP(CMCell4, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()

IMPLEMENT_DYNAMIC(CMCell4, CStatic)

CMCell4::CMCell4(){
} // //////////////////////////////////////////////////////////////////////////////////
CMCell4::~CMCell4(){
} // //////////////////////////////////////////////////////////////////////////////////

// CMCell4 message handlers

void CMCell4::OnPaint(){
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CStatic::OnPaint() for painting messages
	CRect rctClient;
	GetClientRect(&rctClient);

	v[0].SetWindowPos(this, rctClient.left, rctClient.top, rctClient.Width() / 2, rctClient.Height() / 2, SWP_SHOWWINDOW);
} // //////////////////////////////////////////////////////////////////////////////////
