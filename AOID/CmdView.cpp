// CmdView.cpp : 实现文件
//

#include "stdafx.h"
#include "AOID.h"
#include "CmdView.h"
#include "afxdialogex.h"


// CCmdView 对话框

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


// CCmdView 消息处理程序


void CCmdView::OnButtonexe()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CCmdView::OnButtoncancel()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CCmdView::OnButtonhelp()
{
	// TODO: 在此添加控件通知处理程序代码
}


BOOL CCmdView::OnInitDialog()
{
	CDialog::OnInitDialog();
	CMainFrame *pwnd=(CMainFrame*) AfxGetMainWnd();	
	mhwnd=GetSafeHwnd();
	int len;
	CRect temprect;
	pwnd->m_pProgPaneWnd->m_pProgressView->GetWindowRect(&temprect);//获取进度条窗口的位置坐标，作为参考，移动命令输入窗口，使其在进度条窗口上方
	pwnd->m_CmdView.MoveWindow(temprect.left,temprect.top-60,temprect.Width(),60,false);
	// pwnd->m_CmdView.SetWindowPos(NULL,temprect.left,temprect.top-60,temprect.Width(),60,SWP_NOZORDER);//与MoveWindow作用相同
	if(NewCmdText==""&&PreCmdText!="")
	{
		m_CmdEdit.SetWindowText(PreCmdText);//将上一次cmd输入的内容显示在编辑框内
		len=m_CmdEdit.GetWindowTextLength();
		m_CmdEdit.SetFocus();
		m_CmdEdit.SetSel(0,len);//选中编辑框内所有内容
	}
	else if(NewCmdText!="")
	{
		m_CmdEdit.SetWindowText(NewCmdText);
		len=m_CmdEdit.GetWindowTextLength();
		m_CmdEdit.SetFocus();
		m_CmdEdit.SetSel(len,len);//将光标放在最后
		NewCmdText="";
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
