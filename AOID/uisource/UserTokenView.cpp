// UserTokenView.cpp : 实现文件
//

#include "stdafx.h"
#include "AOID.h"
#include "UserTokenView.h"


// CUserTokenView

IMPLEMENT_DYNCREATE(CUserTokenView, CFormView)

CUserTokenView::CUserTokenView()
	: CFormView(CUserTokenView::IDD)
{

}

CUserTokenView::~CUserTokenView()
{
}

void CUserTokenView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CUserTokenView, CFormView)
END_MESSAGE_MAP()


// CUserTokenView 诊断

#ifdef _DEBUG
void CUserTokenView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CUserTokenView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void CUserTokenView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
}
