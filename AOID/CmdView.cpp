// CmdView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AOID.h"
#include "CmdView.h"
#include "afxdialogex.h"


// CCmdView �Ի���

IMPLEMENT_DYNAMIC(CCmdView, CDialog)

CCmdView::CCmdView(CWnd* pParent /*=NULL*/)
	: CDialog(CCmdView::IDD, pParent)
	, PreCmdText(_T(""))
	, NewCmdText(_T(""))
{

}

CCmdView::~CCmdView()
{
}

void CCmdView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDITCMD, m_CmdEdit);
}


BEGIN_MESSAGE_MAP(CCmdView, CDialog)
	ON_BN_CLICKED(IDC_BUTTONEXE, &CCmdView::OnButtonexe)
	ON_BN_CLICKED(IDC_BUTTONCANCEL, &CCmdView::OnButtoncancel)
	ON_BN_CLICKED(IDC_BUTTONHLEP, &CCmdView::OnButtonhelp)
END_MESSAGE_MAP()


// CCmdView ��Ϣ�������


void CCmdView::OnButtonexe()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CCmdView::OnButtoncancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CCmdView::OnButtonhelp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


BOOL CCmdView::OnInitDialog()
{
	CDialog::OnInitDialog();
	CMainFrame *pwnd=(CMainFrame*) AfxGetMainWnd();	
	mhwnd=GetSafeHwnd();
	int len;
	CRect temprect;
	pwnd->m_pProgPaneWnd->m_pProgressView->GetWindowRect(&temprect);//��ȡ���������ڵ�λ�����꣬��Ϊ�ο����ƶ��������봰�ڣ�ʹ���ڽ����������Ϸ�
	pwnd->m_CmdView.MoveWindow(temprect.left,temprect.top-60,temprect.Width(),60,false);
	// pwnd->m_CmdView.SetWindowPos(NULL,temprect.left,temprect.top-60,temprect.Width(),60,SWP_NOZORDER);//��MoveWindow������ͬ
	if(NewCmdText==""&&PreCmdText!="")
	{
		m_CmdEdit.SetWindowText(PreCmdText);//����һ��cmd�����������ʾ�ڱ༭����
		len=m_CmdEdit.GetWindowTextLength();
		m_CmdEdit.SetFocus();
		m_CmdEdit.SetSel(0,len);//ѡ�б༭������������
	}
	else if(NewCmdText!="")
	{
		m_CmdEdit.SetWindowText(NewCmdText);
		len=m_CmdEdit.GetWindowTextLength();
		m_CmdEdit.SetFocus();
		m_CmdEdit.SetSel(len,len);//�����������
		NewCmdText="";
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
