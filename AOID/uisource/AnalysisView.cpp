// AnalysisView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AOID.h"
#include "AnalysisView.h"


// CAnalysisView

IMPLEMENT_DYNCREATE(CAnalysisView, CFormView)

CAnalysisView::CAnalysisView()
	: CFormView(CAnalysisView::IDD)
{

}

CAnalysisView::~CAnalysisView()
{
}

void CAnalysisView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAnalysisView, CFormView)
END_MESSAGE_MAP()


// CAnalysisView ���

#ifdef _DEBUG
void CAnalysisView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAnalysisView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAnalysisView ��Ϣ�������
