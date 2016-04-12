// CameraPosView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AOID.h"
#include "CameraPosView.h"


// CCameraPosView

IMPLEMENT_DYNCREATE(CCameraPosView, CFormView)

CCameraPosView::CCameraPosView()
	: CFormView(CCameraPosView::IDD)
{

}

CCameraPosView::~CCameraPosView()
{
}

void CCameraPosView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INPUTXAERA, m_xAera);
	DDX_Control(pDX, IDC_INPUTYAERA, m_yAera);
}

BEGIN_MESSAGE_MAP(CCameraPosView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CCameraPosView::OnCameraConnect)
	ON_BN_CLICKED(IDC_BUTTON2, &CCameraPosView::OnCameraClose)
	ON_BN_CLICKED(IDC_BUTTON3, &CCameraPosView::OnBnClickedMoving)
	ON_BN_CLICKED(IDC_BUTTON4, &CCameraPosView::OnClickedCamera)
END_MESSAGE_MAP()


// CCameraPosView ���

#ifdef _DEBUG
void CCameraPosView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCameraPosView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCameraPosView ��Ϣ�������


void CCameraPosView::OnCameraConnect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CCameraPosView::OnCameraClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CCameraPosView::OnBnClickedMoving()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CCameraPosView::OnClickedCamera()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
