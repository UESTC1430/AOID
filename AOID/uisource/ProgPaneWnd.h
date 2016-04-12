
#pragma once

// ProgPaneWnd.h : header file
//
#include "ProgressView.h"
/////////////////////////////////////////////////////////////////////////////
// CProgPaneWnd frame

class CProgPaneWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CProgPaneWnd)
protected:
	CProgPaneWnd();           // protected constructor used by dynamic creation

// Attributes
public:
	UINT m_nCurrentViewID;		//记录当前view的ID
   	CProgressView *m_pProgressView;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgPaneWnd)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CProgPaneWnd();

	// Generated message map functions
	//{{AFX_MSG(CProgPaneWnd)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

