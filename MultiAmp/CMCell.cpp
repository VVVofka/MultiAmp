#include "pch.h"
#include "CMCell.h"
BEGIN_MESSAGE_MAP(CMCell, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()


void CMCell::OnPaint(){
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CStatic::OnPaint() for painting messages
}
