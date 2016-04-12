// FocusView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AOID.h"
#include "FocusView.h"


// CFocusView

IMPLEMENT_DYNCREATE(CFocusView, CFormView)

CFocusView::CFocusView()
	: CFormView(CFocusView::IDD)
{

	focuslocation = 0;
	camscale = 0.0f;
	maxvalue = 0.0f;
}

CFocusView::~CFocusView()
{
}

void CFocusView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FOCUSLOCATION, m_focuslocation);
	DDX_Control(pDX, IDC_Z, m_z);
	DDX_Control(pDX, IDC_PICTUREVALUE, m_picturevalue);
}

BEGIN_MESSAGE_MAP(CFocusView, CFormView)
	ON_BN_CLICKED(IDC_GETVALUE, &CFocusView::OnBnClickedGetvalue)
	ON_BN_CLICKED(IDC_AUTOFOCUS, &CFocusView::OnBnClickedAutofocus)
	ON_BN_CLICKED(IDC_Z_UP, &CFocusView::OnBnClickedZUp)
	ON_BN_CLICKED(IDC_Z_DOWN, &CFocusView::OnBnClickedZDown)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CFocusView ���

#ifdef _DEBUG
void CFocusView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFocusView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFocusView ��Ϣ�������


void CFocusView::OnBnClickedGetvalue()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CFocusView::OnBnClickedAutofocus()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CFocusView::OnBnClickedZUp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CFocusView::OnBnClickedZDown()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CFocusView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CFormView::OnPaint()
}
