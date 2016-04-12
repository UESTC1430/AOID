#pragma once
#include "toolview.h"
#include "staticbutton.h"
/////////////////////////////////////////////////////////////////////////////
// CToolPaneWnd frame

class CToolPaneWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CToolPaneWnd)
protected:
	CToolPaneWnd();           // protected constructor used by dynamic creation

// Attributes
public:
	CToolView  *m_pToolView;

	CStaticButton * m_pbutton1;
	CStaticButton * m_pbutton2;
	CStaticButton * m_pbutton3;
	CStaticButton * m_pbutton4;
	CStaticButton * m_pbutton5;
	CStaticButton * m_pbutton6;

	CView * m_pCurrentView;
	CWnd * m_pdlg;
	UINT m_nCurrentViewID;
	void SwitchToView(UINT nView);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolPaneWnd)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CToolPaneWnd();

	// Generated message map functions
	//{{AFX_MSG(CToolPaneWnd)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

