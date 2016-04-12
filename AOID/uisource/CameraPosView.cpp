// CameraPosView.cpp : 实现文件
//

#include "stdafx.h"
#include "AOID.h"
#include "CameraPosView.h"


// CCameraPosView

IMPLEMENT_DYNCREATE(CCameraPosView, CFormView)

CCameraPosView::CCameraPosView()
	: CFormView(CCameraPosView::IDD)
{

}

CCameraPosView::~CCameraPosView()
{
}

void CCameraPosView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INPUTXAERA, m_xAera);
	DDX_Control(pDX, IDC_INPUTYAERA, m_yAera);
}

BEGIN_MESSAGE_MAP(CCameraPosView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CCameraPosView::OnCameraConnect)
	ON_BN_CLICKED(IDC_BUTTON2, &CCameraPosView::OnCameraClose)
	ON_BN_CLICKED(IDC_BUTTON3, &CCameraPosView::OnBnClickedMoving)
	ON_BN_CLICKED(IDC_BUTTON4, &CCameraPosView::OnClickedCamera)
END_MESSAGE_MAP()


// CCameraPosView 诊断

#ifdef _DEBUG
void CCameraPosView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCameraPosView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCameraPosView 消息处理程序


void CCameraPosView::OnCameraConnect()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CCameraPosView::OnCameraClose()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CCameraPosView::OnBnClickedMoving()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CCameraPosView::OnClickedCamera()
{
	// TODO: 在此添加控件通知处理程序代码
}
