// InputPortView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AOID.h"
#include "InputPortView.h"


// CInputPortView

IMPLEMENT_DYNCREATE(CInputPortView, CFormView)

CInputPortView::CInputPortView()
	: CFormView(CInputPortView::IDD)
{

}

CInputPortView::~CInputPortView()
{
}

void CInputPortView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CInputPortView, CFormView)
END_MESSAGE_MAP()


// CInputPortView ���

#ifdef _DEBUG
void CInputPortView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CInputPortView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CInputPortView ��Ϣ�������
