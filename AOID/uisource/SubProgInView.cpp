// SubProgInView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AOID.h"
#include "SubProgInView.h"


// CSubProgInView

IMPLEMENT_DYNCREATE(CSubProgInView, CFormView)

CSubProgInView::CSubProgInView()
	: CFormView(CSubProgInView::IDD)
{

}

CSubProgInView::~CSubProgInView()
{
}

void CSubProgInView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSubProgInView, CFormView)
END_MESSAGE_MAP()


// CSubProgInView ���

#ifdef _DEBUG
void CSubProgInView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSubProgInView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSubProgInView ��Ϣ�������
