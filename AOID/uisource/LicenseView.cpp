// LicenseView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AOID.h"
#include "LicenseView.h"


// CLicenseView

IMPLEMENT_DYNCREATE(CLicenseView, CFormView)

CLicenseView::CLicenseView()
	: CFormView(CLicenseView::IDD)
{

}

CLicenseView::~CLicenseView()
{
}

void CLicenseView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLicenseView, CFormView)
	ON_BN_CLICKED(IDC_BUTTONOK, &CLicenseView::OnBtnOK)
END_MESSAGE_MAP()


// CLicenseView ���

#ifdef _DEBUG
void CLicenseView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CLicenseView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CLicenseView ��Ϣ�������


void CLicenseView::OnBtnOK()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
