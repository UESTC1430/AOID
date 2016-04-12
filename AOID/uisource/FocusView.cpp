// FocusView.cpp : 实现文件
//

#include "stdafx.h"
#include "AOID.h"
#include "FocusView.h"


// CFocusView

IMPLEMENT_DYNCREATE(CFocusView, CFormView)

CFocusView::CFocusView()
	: CFormView(CFocusView::IDD)
{

	focuslocation = 0;
	camscale = 0.0f;
	maxvalue = 0.0f;
}

CFocusView::~CFocusView()
{
}

void CFocusView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FOCUSLOCATION, m_focuslocation);
	DDX_Control(pDX, IDC_Z, m_z);
	DDX_Control(pDX, IDC_PICTUREVALUE, m_picturevalue);
}

BEGIN_MESSAGE_MAP(CFocusView, CFormView)
	ON_BN_CLICKED(IDC_GETVALUE, &CFocusView::OnBnClickedGetvalue)
	ON_BN_CLICKED(IDC_AUTOFOCUS, &CFocusView::OnBnClickedAutofocus)
	ON_BN_CLICKED(IDC_Z_UP, &CFocusView::OnBnClickedZUp)
	ON_BN_CLICKED(IDC_Z_DOWN, &CFocusView::OnBnClickedZDown)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CFocusView 诊断

#ifdef _DEBUG
void CFocusView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFocusView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFocusView 消息处理程序


void CFocusView::OnBnClickedGetvalue()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CFocusView::OnBnClickedAutofocus()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CFocusView::OnBnClickedZUp()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CFocusView::OnBnClickedZDown()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CFocusView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CFormView::OnPaint()
}
