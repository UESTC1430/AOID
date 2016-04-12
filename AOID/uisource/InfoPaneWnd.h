
#pragma once

// InfoPaneWnd.h : header file
#include "infoview.h"

/////////////////////////////////////////////////////////////////////////////
// CInfoPaneWnd frame

class CInfoPaneWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CInfoPaneWnd)
protected:
	CInfoPaneWnd();           // protected constructor used by dynamic creation

// Attributes
public:
	CInfoView * m_pInfoView;

	

	CView * m_pCurrentView;
	CWnd * m_pdlg;
	UINT m_nCurrentViewID;
	void SwitchToView(UINT nView);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInfoPaneWnd)
		protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CInfoPaneWnd();

	// Generated message map functions
	//{{AFX_MSG(CInfoPaneWnd)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

