
#pragma once


#include "progview.h"


/////////////////////////////////////////////////////////////////////////////
// CMenuPaneWnd frame

class CMenuPaneWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CMenuPaneWnd)
public:
	CMenuPaneWnd();           // protected constructor used by dynamic creation

// Attributes
public:
	CProgView  * m_pProgView;
	CWnd * m_pdlg;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMenuPaneWnd)
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMenuPaneWnd();

	// Generated message map functions
	//{{AFX_MSG(CMenuPaneWnd)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

