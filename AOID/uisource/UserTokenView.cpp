// UserTokenView.cpp : 实现文件
//

#include "stdafx.h"
#include "AOID.h"
#include "MainFrm.h"
#include "UserTokenView.h"


// CUserTokenView

IMPLEMENT_DYNCREATE(CUserTokenView, CFormView)

CUserTokenView::CUserTokenView()
	: CFormView(CUserTokenView::IDD)
{

}

CUserTokenView::~CUserTokenView()
{
}

void CUserTokenView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CUserTokenView, CFormView)
	ON_BN_CLICKED(IDC_CHECK0, &CUserTokenView::OnCheck0)
	ON_BN_CLICKED(IDC_CHECK1, &CUserTokenView::OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CUserTokenView::OnCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CUserTokenView::OnCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &CUserTokenView::OnCheck4)
	ON_BN_CLICKED(IDC_CHECK5, &CUserTokenView::OnCheck5)
	ON_BN_CLICKED(IDC_CHECK6, &CUserTokenView::OnCheck6)
	ON_BN_CLICKED(IDC_CHECK7, &CUserTokenView::OnCheck7)
	ON_BN_CLICKED(IDC_CHECK8, &CUserTokenView::OnCheck8)
	ON_BN_CLICKED(IDC_CHECK9, &CUserTokenView::OnCheck9)
	ON_BN_CLICKED(IDC_CHECK10, &CUserTokenView::OnCheck10)
	ON_BN_CLICKED(IDC_CHECK11, &CUserTokenView::OnCheck11)
	ON_BN_CLICKED(IDC_CHECK12, &CUserTokenView::OnCheck12)
END_MESSAGE_MAP()


// CUserTokenView 诊断

#ifdef _DEBUG
void CUserTokenView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CUserTokenView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void CUserTokenView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
}


void CUserTokenView::OnCheck0()
{
	FlagChange(0);//用户标记参数修改标志被改变
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	if ( BST_CHECKED == IsDlgButtonChecked( IDC_CHECK0 ) )
	{
		pwnd->m_usermarkflag.AUTOCHANGEFLAG=true;
	}
	else
	{
		pwnd->m_usermarkflag.AUTOCHANGEFLAG=false;
	}
}


void CUserTokenView::OnCheck1()
{
	FlagChange(1);
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	if ( BST_CHECKED == IsDlgButtonChecked( IDC_CHECK1 ) )
	{
		pwnd->m_usermarkflag.MEARUETICKNESS=true;
	}
	else
	{
		pwnd->m_usermarkflag.MEARUETICKNESS=false;
	}
}


void CUserTokenView::OnCheck2()
{
	FlagChange(2);
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	if ( BST_CHECKED == IsDlgButtonChecked( IDC_CHECK2) )
	{
		pwnd->m_usermarkflag.DRILLMARCHING=true;
	}
	else
	{
		pwnd->m_usermarkflag.DRILLMARCHING=false;
	}
}


void CUserTokenView::OnCheck3()
{
	FlagChange(3);
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	if ( BST_CHECKED == IsDlgButtonChecked(IDC_CHECK3) )
	{
		pwnd->m_usermarkflag.CHECKSPRUNDRILLING=true;
	}
	else
	{
		pwnd->m_usermarkflag.CHECKSPRUNDRILLING=false;
	}
}


void CUserTokenView::OnCheck4()
{
	FlagChange(4);
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	if ( BST_CHECKED == IsDlgButtonChecked( IDC_CHECK4) )
	{
		pwnd->m_usermarkflag.RUNSPBEFOREDRILLMTC=true;
	}
	else
	{
		pwnd->m_usermarkflag.RUNSPBEFOREDRILLMTC=false;
	}
}


void CUserTokenView::OnCheck5()
{
	FlagChange(5);
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	if ( BST_CHECKED == IsDlgButtonChecked( IDC_CHECK5) )
	{
		pwnd->m_usermarkflag.BREAKTOOLCHECK=true;
	}
	else
	{
		pwnd->m_usermarkflag.BREAKTOOLCHECK=false;
	}
}


void CUserTokenView::OnCheck6()
{
	FlagChange(6);
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	if ( BST_CHECKED == IsDlgButtonChecked( IDC_CHECK6) )
	{
		pwnd->m_usermarkflag.BREAKEDGECHECK=true;
	}
	else
	{
		pwnd->m_usermarkflag.BREAKEDGECHECK=false;
	}
}


void CUserTokenView::OnCheck7()
{
	FlagChange(7);
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	if ( BST_CHECKED == IsDlgButtonChecked( IDC_CHECK7) )
	{
		pwnd->m_usermarkflag.AFTERCHECKTOOLLENGTH=true;
	}
	else
	{
		pwnd->m_usermarkflag.AFTERCHECKTOOLLENGTH=false;
	}
}


void CUserTokenView::OnCheck8()
{
	FlagChange(8);
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	if ( BST_CHECKED == IsDlgButtonChecked( IDC_CHECK8) )
	{
		pwnd->m_usermarkflag.AUTOAJUESTTOOLLENGH=true;
	}
	else
	{
		pwnd->m_usermarkflag.AUTOAJUESTTOOLLENGH=false;
	}
}


void CUserTokenView::OnCheck9()
{
	FlagChange(9);
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	if ( BST_CHECKED == IsDlgButtonChecked( IDC_CHECK9) )
	{
		pwnd->m_usermarkflag.MEARUENEWTOOL=true;
	}
	else
	{
		pwnd->m_usermarkflag.MEARUENEWTOOL=false;
	}
}


void CUserTokenView::OnCheck10()
{
	FlagChange(10);
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	if ( BST_CHECKED == IsDlgButtonChecked( IDC_CHECK10) )
	{
		pwnd->m_usermarkflag.MEARUEALLTOOL=true;
		m_QIC.EnableWindow(true);
	}
	else
	{
		pwnd->m_usermarkflag.MEARUEALLTOOL=false;
		m_QIC.SetCheck(0);
		m_QIC.EnableWindow(false);//不允许刀具测量时,QIC按钮不可用		
	}
}


void CUserTokenView::OnCheck11()
{
	FlagChange(11);
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	if ( BST_CHECKED == IsDlgButtonChecked( IDC_CHECK12) )
	{
		pwnd->m_usermarkflag.AUTOCHANGETOOLLIFE=true;
	}
	else
	{
		pwnd->m_usermarkflag.AUTOCHANGETOOLLIFE=false;
	}
}


void CUserTokenView::OnCheck12()
{
	FlagChange(12);
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	if ( BST_CHECKED == IsDlgButtonChecked( IDC_CHECK13) )
	{
		pwnd->m_usermarkflag.QIC=true;
	}
	else
	{
		pwnd->m_usermarkflag.QIC=false;
	}
}

int CUserTokenView::FlagChange(int num)
{
	/*	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	if(false==pwnd->IniChangeflag[num])
		pwnd->IniChangeflag[num]=true;
	else 
		pwnd->IniChangeflag[num]=false;*/
	return 0;
}
