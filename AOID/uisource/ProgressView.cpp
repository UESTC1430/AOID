// ProgressView.cpp : 实现文件
//

#include "stdafx.h"
#include "AOID.h"
#include "ProgressView.h"


// CProgressView

IMPLEMENT_DYNCREATE(CProgressView, CFormView)

CProgressView::CProgressView()
	: CFormView(CProgressView::IDD)
{

}

CProgressView::~CProgressView()
{
}

void CProgressView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CProgressView, CFormView)
END_MESSAGE_MAP()


// CProgressView 诊断

#ifdef _DEBUG
void CProgressView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CProgressView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CProgressView 消息处理程序
