// F:\vs2010\ADIO\10.25\AOID20151023\AOID\AOID\uisource\ToolViewAll.cpp : 实现文件
//

#include "stdafx.h"
#include "AOID.h"
#include "ToolViewAll.h"


// CToolViewAll

IMPLEMENT_DYNCREATE(CToolViewAll, CFormView)

CToolViewAll::CToolViewAll()
	: CFormView(CToolViewAll::IDD)
{

}

CToolViewAll::~CToolViewAll()
{
}

void CToolViewAll::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CToolViewAll, CFormView)
END_MESSAGE_MAP()


// CToolViewAll 诊断

#ifdef _DEBUG
void CToolViewAll::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CToolViewAll::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CToolViewAll 消息处理程序
