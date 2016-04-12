// SoftWareInfoView.cpp : 实现文件
//

#include "stdafx.h"
#include "AOID.h"
#include "SoftWareInfoView.h"


// CSoftWareInfoView

IMPLEMENT_DYNCREATE(CSoftWareInfoView, CFormView)

CSoftWareInfoView::CSoftWareInfoView()
	: CFormView(CSoftWareInfoView::IDD)
{

}

CSoftWareInfoView::~CSoftWareInfoView()
{
}

void CSoftWareInfoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit_version);
	DDX_Control(pDX, IDC_BUTTON2, m_btn_clear);
	DDX_Control(pDX, IDC_BUTTON3, m_btn_reload);
	DDX_Control(pDX, IDC_BUTTON1, m_btn_close);
}

BEGIN_MESSAGE_MAP(CSoftWareInfoView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CSoftWareInfoView::OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSoftWareInfoView::OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CSoftWareInfoView::OnButton3)
END_MESSAGE_MAP()


// CSoftWareInfoView 诊断

#ifdef _DEBUG
void CSoftWareInfoView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSoftWareInfoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSoftWareInfoView 消息处理程序
void CSoftWareInfoView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	//m_edit_version.SetWindowText("version 1.0");
	// TODO: Add your specialized code here and/or call the base class
}

void CSoftWareInfoView::OnButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CSoftWareInfoView::OnButton2()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CSoftWareInfoView::OnButton3()
{
	// TODO: 在此添加控件通知处理程序代码
}


