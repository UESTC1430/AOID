
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "AOID.h"
#include "MainFrm.h"
#include "OpPaneWnd.h"
#include "menupanewnd.h"
#include "progpanewnd.h"
#include "toolpanewnd.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
END_MESSAGE_MAP()

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
	m_pOpPaneWnd=NULL;
	m_pMenuPaneWnd = NULL; 
	m_pProgPaneWnd = NULL;
	m_pToolPaneWnd = NULL;
	m_pInfoPaneWnd = NULL;
	int a=max(1,2);
	cmdviewflag=false;//��ʼ������ʾcmdview
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2008);
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	cs.cx= 1024;
	cs.cy=768;
	return TRUE;
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	int widecol2=305;//�ڶ��еĿ��
	int highrow2=170;//�ڶ��еĸ߶ȣ� infoview ��
	CRect rect;
	GetClientRect(&rect);
	if(m_wndSplitter1.CreateStatic(this,2,1)==NULL)//��������һ�е��зִ���
		return FALSE;
	if(!m_wndSplitter1.CreateView(1,0,RUNTIME_CLASS(CInfoPaneWnd),CSize(rect.Width(),highrow2),pContext))
		return FALSE;
	m_wndSplitter1.SetRowInfo(0,rect.Height()-highrow2,0);//���õ�һ�еĿ��
	if(NULL==m_wndSplitter2.CreateStatic(&m_wndSplitter1,2,2,WS_CHILD|WS_VISIBLE, m_wndSplitter1.IdFromRowCol(0, 0)))
        return FALSE; //����0��0�� �ֳ�2��2��)
	 if(!m_wndSplitter2.CreateView(0,0,RUNTIME_CLASS(COpPaneWnd),CSize(rect.Width()-widecol2,475),pContext))
		return FALSE;
	
	if(!m_wndSplitter2.CreateView(0,1,RUNTIME_CLASS(CMenuPaneWnd),CSize(widecol2,475),pContext))
		return FALSE;
	
	if(!m_wndSplitter2.CreateView(1,0,RUNTIME_CLASS(CProgPaneWnd),CSize(rect.Width()-widecol2,rect.Height()-480-highrow2),pContext))
		return FALSE;
	
	if(!m_wndSplitter2.CreateView(1,1,RUNTIME_CLASS(CToolPaneWnd),CSize(widecol2,rect.Height()-480-highrow2),pContext))
		return FALSE;
	this->m_pOpPaneWnd   = (COpPaneWnd   *)m_wndSplitter2.GetPane(0,0);
	this->m_pMenuPaneWnd = (CMenuPaneWnd *)m_wndSplitter2.GetPane(0,1);	
	this->m_pProgPaneWnd = (CProgPaneWnd *)m_wndSplitter2.GetPane(1,0);
	this->m_pToolPaneWnd = (CToolPaneWnd *)m_wndSplitter2.GetPane(1,1);
	this->m_pInfoPaneWnd = (CInfoPaneWnd *)m_wndSplitter1.GetPane(1,0);

	this->m_pMenuPaneWnd->GetWindowRect(&rect);
	this->m_pMenuPaneWnd->GetWindowRect(&rect);
	return true;
}


void CMainFrame::ShowCmdView(bool flag)
{
	if(flag==true)
	{
		if(cmdviewflag==false)
		{
			m_CmdView.Create(IDD_CMDVIEW,NULL);
			m_CmdView.ShowWindow(SW_SHOW);
			m_pMenuPaneWnd->m_pProgView->HighLightFnButton(4);
			cmdviewflag=true;
		}		
	}
	else
	{
		if(cmdviewflag==true)
		{
			m_CmdView.DestroyWindow();
			cmdviewflag=false;
		}
		m_pMenuPaneWnd->m_pProgView->HighLightFnButton(m_pMenuPaneWnd->m_pProgView->fbtnnum);
	}
}
