// InfoPaneWnd.cpp : implementation file
//

#include "stdafx.h"
#include "InfoPaneWnd.h"
#include "mainfrm.h"


#define VIEW_INFO		16

/////////////////////////////////////////////////////////////////////////////
// CInfoPaneWnd

IMPLEMENT_DYNCREATE(CInfoPaneWnd, CFrameWnd)

CInfoPaneWnd::CInfoPaneWnd()
{
}

CInfoPaneWnd::~CInfoPaneWnd()
{
//	delete m_pInfoView;
}


BEGIN_MESSAGE_MAP(CInfoPaneWnd, CFrameWnd)
	//{{AFX_MSG_MAP(CInfoPaneWnd)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfoPaneWnd message handlers
BOOL CInfoPaneWnd::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	
	

	m_pInfoView = new CInfoView;
	((CView *)m_pInfoView)->Create(NULL,NULL,0L,CFrameWnd::rectDefault,this, VIEW_INFO,pContext);

	


	m_pInfoView->SetDlgCtrlID(VIEW_INFO);


	m_pInfoView->ShowWindow(SW_SHOW);
	m_pInfoView->SetDlgCtrlID(AFX_IDW_PANE_FIRST);
	m_nCurrentViewID = VIEW_INFO;

	SetActiveView(m_pInfoView);
	RecalcLayout();
	return TRUE;
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}
void CInfoPaneWnd::SwitchToView(UINT nView)
{
	//ÇÐ»»ÊÔÍ¼

	CView * pOldActiveView = GetActiveView();
	CView *pNewActiveView = NULL;


	switch(nView)
	{
	case VIEW_INFO:
		pNewActiveView = (CInfoView * ) m_pInfoView;
		
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

BOOL CInfoPaneWnd::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CFrameWnd::PreCreateWindow(cs);
}

