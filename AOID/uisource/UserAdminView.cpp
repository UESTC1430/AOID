// UserAdminView.cpp : 实现文件
//

#include "stdafx.h"
#include "AOID.h"
#include "UserAdminView.h"


// CUserAdminView

IMPLEMENT_DYNCREATE(CUserAdminView, CFormView)

CUserAdminView::CUserAdminView()
	: CFormView(CUserAdminView::IDD)
{

}

CUserAdminView::~CUserAdminView()
{
}

void CUserAdminView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CUserAdminView, CFormView)
END_MESSAGE_MAP()


// CUserAdminView 诊断

#ifdef _DEBUG
void CUserAdminView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CUserAdminView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CUserAdminView 消息处理程序
