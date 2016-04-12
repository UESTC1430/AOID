// InchFunctionView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AOID.h"
#include "InchFunctionView.h"


// CInchFunctionView

IMPLEMENT_DYNCREATE(CInchFunctionView, CFormView)

CInchFunctionView::CInchFunctionView()
	: CFormView(CInchFunctionView::IDD)
{

}

CInchFunctionView::~CInchFunctionView()
{
}

void CInchFunctionView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_XLOCATION, m_xpos);
	DDX_Control(pDX, IDC_YLOCATION, m_ypos);
	DDX_Control(pDX, IDC_ZLOCATION, m_zpos);
	DDX_Control(pDX, IDC_PICTUREVALUE, m_picvalue);
}

BEGIN_MESSAGE_MAP(CInchFunctionView, CFormView)
	ON_BN_CLICKED(IDC_GETVALUE, &CInchFunctionView::OnBnClickedGetvalue)
	ON_BN_CLICKED(IDC_BUTTON1, &CInchFunctionView::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CInchFunctionView::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CInchFunctionView::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BTN_UP, &CInchFunctionView::OnBtnUp)
	ON_BN_CLICKED(IDC_BTN_DOWN, &CInchFunctionView::OnBtnDwon)
	ON_BN_CLICKED(IDC_BUTTON_UP, &CInchFunctionView::OnButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, &CInchFunctionView::OnButtonRight)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, &CInchFunctionView::OnButtonDown)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, &CInchFunctionView::OnButtonLeft)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CInchFunctionView ���

#ifdef _DEBUG
void CInchFunctionView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CInchFunctionView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CInchFunctionView ��Ϣ�������


void CInchFunctionView::OnBnClickedGetvalue()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CInchFunctionView::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CInchFunctionView::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CInchFunctionView::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CInchFunctionView::OnBtnUp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CInchFunctionView::OnBtnDwon()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CInchFunctionView::OnButtonUp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CInchFunctionView::OnButtonRight()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CInchFunctionView::OnButtonDown()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CInchFunctionView::OnButtonLeft()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


HBRUSH CInchFunctionView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	if(IDC_BUTTON_RIGHT==pWnd->GetDlgCtrlID())
	{
		pDC->SetBkColor(RGB(255,255,0));      //���ñ�����ɫ  
		pDC->SetTextColor(RGB(0,0,0));     //����������ɫ---��ע1
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

