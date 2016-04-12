// ProgPaneWnd.cpp : implementation file
//

#include "stdafx.h"
//#include "cnc.h"
#include "ProgPaneWnd.h"
#include "winpara.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgPaneWnd

IMPLEMENT_DYNCREATE(CProgPaneWnd, CFrameWnd)

CProgPaneWnd::CProgPaneWnd()
{
}

CProgPaneWnd::~CProgPaneWnd()
{
}


BEGIN_MESSAGE_MAP(CProgPaneWnd, CFrameWnd)
	//{{AFX_MSG_MAP(CProgPaneWnd)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgPaneWnd message handlers

BOOL CProgPaneWnd::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_pProgressView = new CProgressView;
	((CView *)m_pProgressView)->Create(NULL,NULL,0L,CFrameWnd::rectDefault,this, VIEW_PROGRESS,pContext);
	m_pProgressView->SetDlgCtrlID(VIEW_PROGRESS);
	m_pProgressView->ShowWindow(SW_SHOW);
	m_pProgressView->SetDlgCtrlID(AFX_IDW_PANE_FIRST);
	m_nCurrentViewID = VIEW_PROGRESS;
	SetActiveView(m_pProgressView);
	RecalcLayout();
	return TRUE;
	return CFrameWnd::OnCreateClient(lpcs, pContext);
}
