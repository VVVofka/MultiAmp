#include "pch.h"
#include "MaskA.h"
BEGIN_MESSAGE_MAP(MaskA, CDialog)
	ON_BN_CLICKED(1009, &MaskA::OnBnClickedMaskaBtOk)
END_MESSAGE_MAP()


void MaskA::OnBnClickedMaskaBtOk(){
	// TODO: �������� ���� ��� ����������� �����������
	ASSERT(0);
}


BOOL MaskA::OnInitDialog(){
	CDialog::OnInitDialog();

	// TODO:  �������� �������������� �������������

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����������: �������� ������� OCX ������ ���������� �������� FALSE
}
