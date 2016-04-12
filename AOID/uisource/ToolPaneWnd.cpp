// ToolPaneWnd.cpp : implementation file
//

#include "stdafx.h"
#include "ToolPaneWnd.h"
#include "mainfrm.h"
#include "winpara.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolPaneWnd

IMPLEMENT_DYNCREATE(CToolPaneWnd, CFrameWnd)

CToolPaneWnd::CToolPaneWnd()
{
	
}

CToolPaneWnd::~CToolPaneWnd()
{
	delete m_pToolView;
}


BEGIN_MESSAGE_MAP(CToolPaneWnd, CFrameWnd)
	//{{AFX_MSG_MAP(CToolPaneWnd)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolPaneWnd message handlers
BOOL CToolPaneWnd::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	

	
	m_pToolView = new CToolView;
	((CView *)m_pToolView)->Create(NULL,NULL,0L,CFrameWnd::rectDefault,this, VIEW_TOOL,pContext);



	m_pToolView->SetDlgCtrlID(VIEW_TOOL);

	m_pbutton1 = m_pToolView->m_lockbutton;
	m_pbutton2 = NULL;
	m_pbutton3 = NULL;	
	m_pbutton4 = NULL;
	m_pbutton5 = NULL;
	m_pbutton6 = NULL;

	m_pToolView->ShowWindow(SW_SHOW);
	m_pToolView->SetDlgCtrlID(AFX_IDW_PANE_FIRST);
	m_nCurrentViewID = VIEW_TOOL;

	SetActiveView(m_pToolView);
	RecalcLayout();
	return TRUE;
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}
void CToolPaneWnd::SwitchToView(UINT nView)
{
	//ÇÐ»»ÊÔÍ¼
/*	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	if(pwnd->m_pShowwaveView->pWaveThread!=NULL)
	{
		pwnd->m_pShowwaveView->m_irefreshview = 0;
		pwnd->m_pShowwaveView->pWaveThread->SuspendThread();
	}
	
*/	CView * pOldActiveView = GetActiveView();
	CView *pNewActiveView = NULL;

	switch(nView)
	{
	case VIEW_TOOL:
		pNewActiveView = (CToolView *) m_pToolView;
	
	//	pwnd->m_pMenuPaneWnd->m_pTimebaseView->Update(pwnd->iLangFlag);
		break;
	

	default:
		break;
	}

	//	m_pCurrentView = (CView *)pNewActiveView;
		SetActiveView(pNewActiveView);
		pNewActiveView->ShowWindow(SW_SHOW);
		pNewActiveView->UpdateWindow();
		pNewActiveView->SetDlgCtrlID(AFX_IDW_PANE_FIRST);
		if(pOldActiveView)
		{
			pOldActiveView->ShowWindow(SW_HIDE);
			pOldActiveView->UpdateWindow();
			pOldActiveView->SetDlgCtrlID(m_nCurrentViewID);
		}
		m_nCurrentViewID = nView;
		RecalcLayout();
	
	
}

BOOL CToolPaneWnd::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CFrameWnd::PreCreateWindow(cs);
}

