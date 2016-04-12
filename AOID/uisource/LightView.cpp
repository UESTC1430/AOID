// LightView.cpp : 实现文件
//

#include "stdafx.h"
#include "AOID.h"
#include "LightView.h"


// CLightView

IMPLEMENT_DYNCREATE(CLightView, CFormView)

CLightView::CLightView()
	: CFormView(CLightView::IDD)
{

}

CLightView::~CLightView()
{
}

void CLightView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLightView, CFormView)
END_MESSAGE_MAP()


// CLightView 诊断

#ifdef _DEBUG
void CLightView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CLightView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CLightView 消息处理程序
