// FileAndContentsView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AOID.h"
#include "FileAndContentsView.h"


// CFileAndContentsView

IMPLEMENT_DYNCREATE(CFileAndContentsView, CFormView)

CFileAndContentsView::CFileAndContentsView()
	: CFormView(CFileAndContentsView::IDD)
{

}

CFileAndContentsView::~CFileAndContentsView()
{
}

void CFileAndContentsView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFileAndContentsView, CFormView)
	ON_BN_CLICKED(IDC_MASTPATHBTN, &CFileAndContentsView::OnMastpathChange)
	ON_BN_CLICKED(IDC_SUBPATHBTN, &CFileAndContentsView::OnSubpathChange)
END_MESSAGE_MAP()


// CFileAndContentsView ���

#ifdef _DEBUG
void CFileAndContentsView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFileAndContentsView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFileAndContentsView ��Ϣ�������


void CFileAndContentsView::OnMastpathChange()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CFileAndContentsView::OnSubpathChange()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
