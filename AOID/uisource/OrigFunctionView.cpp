// OrigFunctionView.cpp : 实现文件
//

#include "stdafx.h"
#include "AOID.h"
#include "OrigFunctionView.h"


// COrigFunctionView

IMPLEMENT_DYNCREATE(COrigFunctionView, CFormView)

COrigFunctionView::COrigFunctionView()
	: CFormView(COrigFunctionView::IDD)
{

}

COrigFunctionView::~COrigFunctionView()
{
}

void COrigFunctionView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COrigFunctionView, CFormView)
END_MESSAGE_MAP()


// COrigFunctionView 诊断

#ifdef _DEBUG
void COrigFunctionView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void COrigFunctionView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// COrigFunctionView 消息处理程序
