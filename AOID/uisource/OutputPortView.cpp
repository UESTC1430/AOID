// OutputPortView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AOID.h"
#include "OutputPortView.h"


// COutputPortView

IMPLEMENT_DYNCREATE(COutputPortView, CFormView)

COutputPortView::COutputPortView()
	: CFormView(COutputPortView::IDD)
{

}

COutputPortView::~COutputPortView()
{
}

void COutputPortView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COutputPortView, CFormView)
END_MESSAGE_MAP()


// COutputPortView ���

#ifdef _DEBUG
void COutputPortView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void COutputPortView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// COutputPortView ��Ϣ�������
