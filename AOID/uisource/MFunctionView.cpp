// MFunctionView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AOID.h"
#include "MFunctionView.h"


// CMFunctionView

IMPLEMENT_DYNCREATE(CMFunctionView, CFormView)

CMFunctionView::CMFunctionView()
	: CFormView(CMFunctionView::IDD)
{

}

CMFunctionView::~CMFunctionView()
{
}

void CMFunctionView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFunctionView, CFormView)
//	ON_BN_CLICKED(IDC_BTN_M1, &CMFunctionView::OnBtnM1)
	ON_CBN_SELCHANGE(IDC_COMBOM1, &CMFunctionView::OnSelchangeComboM1)
//	ON_CBN_SELCHANGE(IDC_COMBOM2, &CMFunctionView::OnSelchangeCombom2)
	ON_CBN_SELCHANGE(IDC_COMBOM3, &CMFunctionView::OnSelchangeComboM3)
	ON_CBN_SELCHANGE(IDC_COMBOM2, &CMFunctionView::OnSelchangeComboM2)
	ON_CBN_SELCHANGE(IDC_COMBOM10, &CMFunctionView::OnSelchangeComboM10)
	ON_CBN_SELCHANGE(IDC_COMBOM11, &CMFunctionView::OnSelchangeComboM11)
	ON_CBN_SELCHANGE(IDC_COMBOM12, &CMFunctionView::OnSelchangeComboM12)
	ON_CBN_SELCHANGE(IDC_COMBOM13, &CMFunctionView::OnSelchangeComboM13)
	ON_CBN_SELCHANGE(IDC_COMBOM14, &CMFunctionView::OnSelchangeComboM14)
	ON_CBN_SELCHANGE(IDC_COMBOM4, &CMFunctionView::OnSelchangeComboM4)
	ON_CBN_SELCHANGE(IDC_COMBOM5, &CMFunctionView::OnSelchangeComboM5)
	ON_CBN_SELCHANGE(IDC_COMBOM6, &CMFunctionView::OnSelchangeComboM6)
	ON_CBN_SELCHANGE(IDC_COMBOM7, &CMFunctionView::OnSelchangeComboM7)
	ON_CBN_SELCHANGE(IDC_COMBOM8, &CMFunctionView::OnSelchangeComboM8)
	ON_CBN_SELCHANGE(IDC_COMBOM9, &CMFunctionView::OnSelchangeComboM9)
	ON_BN_CLICKED(IDC_BTN_M10, &CMFunctionView::OnClickedBtnM10)
	ON_BN_CLICKED(IDC_BTN_M11, &CMFunctionView::OnClickedBtnM11)
	ON_BN_CLICKED(IDC_BTN_M12, &CMFunctionView::OnClickedBtnM12)
	ON_BN_CLICKED(IDC_BTN_M13, &CMFunctionView::OnClickedBtnM13)
	ON_BN_CLICKED(IDC_BTN_M14, &CMFunctionView::OnClickedBtnM14)
	ON_BN_CLICKED(IDC_BTN_M2, &CMFunctionView::OnClickedBtnM2)
	ON_BN_CLICKED(IDC_BTN_M3, &CMFunctionView::OnClickedBtnM3)
	ON_BN_CLICKED(IDC_BTN_M4, &CMFunctionView::OnClickedBtnM4)
	ON_BN_CLICKED(IDC_BTN_M5, &CMFunctionView::OnClickedBtnM5)
	ON_BN_CLICKED(IDC_BTN_M6, &CMFunctionView::OnClickedBtnM6)
	ON_BN_CLICKED(IDC_BTN_M7, &CMFunctionView::OnClickedBtnM7)
	ON_BN_CLICKED(IDC_BTN_M8, &CMFunctionView::OnClickedBtnM8)
	ON_BN_CLICKED(IDC_BTN_M9, &CMFunctionView::OnClickedBtnM9)
	ON_BN_CLICKED(IDC_BTN_M1, &CMFunctionView::OnClickedBtnM1)
END_MESSAGE_MAP()


// CMFunctionView ���

#ifdef _DEBUG
void CMFunctionView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMFunctionView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMFunctionView ��Ϣ�������



void CMFunctionView::OnSelchangeComboM1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMFunctionView::OnSelchangeComboM2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMFunctionView::OnSelchangeComboM3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}




void CMFunctionView::OnSelchangeComboM4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMFunctionView::OnSelchangeComboM5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMFunctionView::OnSelchangeComboM6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMFunctionView::OnSelchangeComboM7()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMFunctionView::OnSelchangeComboM8()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMFunctionView::OnSelchangeComboM9()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMFunctionView::OnSelchangeComboM10()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMFunctionView::OnSelchangeComboM11()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMFunctionView::OnSelchangeComboM12()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMFunctionView::OnSelchangeComboM13()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMFunctionView::OnSelchangeComboM14()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CMFunctionView::OnClickedBtnM1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMFunctionView::OnClickedBtnM2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMFunctionView::OnClickedBtnM3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMFunctionView::OnClickedBtnM4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMFunctionView::OnClickedBtnM5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMFunctionView::OnClickedBtnM6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMFunctionView::OnClickedBtnM7()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMFunctionView::OnClickedBtnM8()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMFunctionView::OnClickedBtnM9()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMFunctionView::OnClickedBtnM10()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMFunctionView::OnClickedBtnM11()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMFunctionView::OnClickedBtnM12()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMFunctionView::OnClickedBtnM13()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMFunctionView::OnClickedBtnM14()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
