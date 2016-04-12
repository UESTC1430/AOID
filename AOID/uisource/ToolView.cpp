// ToolView.cpp : 实现文件
//

#include "stdafx.h"
#include "AOID.h"
#include "ToolView.h"


// CToolView

IMPLEMENT_DYNCREATE(CToolView, CFormView)

CToolView::CToolView()
	: CFormView(CToolView::IDD)
{

}

CToolView::~CToolView()
{
}

void CToolView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CToolView, CFormView)
	ON_STN_CLICKED(IDC_LOCK, &CToolView::OnStnClickedLock)
END_MESSAGE_MAP()


// CToolView 诊断

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CToolView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CToolView 消息处理程序


void CToolView::OnStnClickedLock()
{
	// TODO: 在此添加控件通知处理程序代码
}
