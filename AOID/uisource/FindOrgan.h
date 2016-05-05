#if !defined(AFX_FINDORGAN_H__27B280EA_6FB3_4C4C_9E1B_9E73D20BDA5E__INCLUDED_)
#define AFX_FINDORGAN_H__27B280EA_6FB3_4C4C_9E1B_9E73D20BDA5E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FindOrgan.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFindOrgan dialog
#include "resource.h"
class CFindOrgan : public CDialog
{
	// Construction
public:
	CFindOrgan(CWnd* pParent = NULL);   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CFindOrgan)
	enum { IDD = IDD_FINDORGAN };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindOrgan)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFindOrgan)
	afx_msg void OnFindOrgan();
	afx_msg void Cancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDORGAN_H__27B280EA_6FB3_4C4C_9E1B_9E73D20BDA5E__INCLUDED_)
