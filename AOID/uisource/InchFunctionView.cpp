// InchFunctionView.cpp : 实现文件
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


// CInchFunctionView 诊断

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


// CInchFunctionView 消息处理程序


void CInchFunctionView::OnBnClickedGetvalue()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CInchFunctionView::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CInchFunctionView::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CInchFunctionView::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CInchFunctionView::OnBtnUp()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CInchFunctionView::OnBtnDwon()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CInchFunctionView::OnButtonUp()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CInchFunctionView::OnButtonRight()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CInchFunctionView::OnButtonDown()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CInchFunctionView::OnButtonLeft()
{
	// TODO: 在此添加控件通知处理程序代码
}


HBRUSH CInchFunctionView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	if(IDC_BUTTON_RIGHT==pWnd->GetDlgCtrlID())
	{
		pDC->SetBkColor(RGB(255,255,0));      //设置背景颜色  
		pDC->SetTextColor(RGB(0,0,0));     //设置字体颜色---备注1
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

