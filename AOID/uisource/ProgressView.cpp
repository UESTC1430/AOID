// ProgressView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AOID.h"
#include "ProgressView.h"


// CProgressView

IMPLEMENT_DYNCREATE(CProgressView, CFormView)

CProgressView::CProgressView()
	: CFormView(CProgressView::IDD)
{

}

CProgressView::~CProgressView()
{
}

void CProgressView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CProgressView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_SPACE, &CProgressView::OnButtonSpace)
END_MESSAGE_MAP()


// CProgressView ���

#ifdef _DEBUG
void CProgressView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CProgressView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


void CProgressView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	//m_pro.SetWindowText(progressstr);
	m_pro.SetBkColour(progresscol);
	m_pro.SetShowText(TRUE);}

// CProgressView ��Ϣ�������


void CProgressView::OnButtonSpace()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	pwnd->SPACEKEYDOWN();
}

bool CProgressView::WarnMessage(CString str,COLORREF col)
{
	if(m_pro)//���ڽ���ǰ�Ѿ�����������Ϣ����ͨ���˺�������
	{
		m_pro.SetBkColour(col);
		//m_pro.SetWindowText(str);
		m_pro.SetShowText(TRUE);
	}
	else
	{
		progressstr=str;
		progresscol=col;
	}
	return true;
}


void CProgressView::DrillProgress(int currentnum,int totalnum)//��׽�����ʾ������ currentnum:��ǰ���ڴ�ڼ����ף�totalnumҪִ�д�ײ������ܿ���
{
/*	int currentpos;
   	CString text;
	if(currentnum<totalnum)
	{
		currentpos=(currentnum*100)/totalnum;//��ǰ������Ӧ�ڵ�λ��
		m_pro.SetPos(currentpos);
		text.Format("%d",currentpos);
		text="�����"+text+"%";
	}
	else if(currentnum==totalnum)
	{
		currentpos=(currentnum*100)/totalnum;//��ǰ������Ӧ�ڵ�λ��
		m_pro.SetPos(currentpos);
		text="��׽���";
	}
	else
		TRACE("�Ѵ���������ܿ���\n");*/ //su

  	CString text;
    text.Format("��ǰ����%d����",currentnum);
	m_pro.SetWindowText(text);	
	m_pro.SetShowText(TRUE);	
}
