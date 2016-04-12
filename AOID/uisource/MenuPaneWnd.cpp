// MenuPaneWnd.cpp : implementation file
//

#include "stdafx.h"
#include "MenuPaneWnd.h"
#include "mainfrm.h"
#include "winpara.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMenuPaneWnd

IMPLEMENT_DYNCREATE(CMenuPaneWnd, CFrameWnd)

CMenuPaneWnd::CMenuPaneWnd()
{
	
}

CMenuPaneWnd::~CMenuPaneWnd()
{
	

	delete this->m_pProgView;
}


BEGIN_MESSAGE_MAP(CMenuPaneWnd, CFrameWnd)
	//{{AFX_MSG_MAP(CMenuPaneWnd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMenuPaneWnd message handlers

BOOL CMenuPaneWnd::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	CRect rect;
	
	m_pProgView = new CProgView;

	
	this->GetWindowRect(&rect);
	((CView *)m_pProgView)->Create(NULL,NULL,0L,CFrameWnd::rectDefault,this, VIEW_PROG,pContext);


	m_pProgView->SetDlgCtrlID(VIEW_PROG);

	m_pProgView->ShowWindow(SW_SHOW);	

	m_pProgView->SetDlgCtrlID(AFX_IDW_PANE_FIRST);

	SetActiveView(m_pProgView);



	RecalcLayout();
	

	return TRUE;
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}


BOOL CMenuPaneWnd::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CFrameWnd::PreCreateWindow(cs);
}

