// ServeView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AOID.h"
#include "ServeView.h"


// CServeView

IMPLEMENT_DYNCREATE(CServeView, CFormView)

CServeView::CServeView()
	: CFormView(CServeView::IDD)
{

}

CServeView::~CServeView()
{
}

void CServeView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CServeView, CFormView)
END_MESSAGE_MAP()


// CServeView ���

#ifdef _DEBUG
void CServeView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CServeView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CServeView ��Ϣ�������
