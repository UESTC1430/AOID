#pragma once

#include "resource.h"

// CFileAndContentsView 窗体视图

class CFileAndContentsView : public CFormView
{
	DECLARE_DYNCREATE(CFileAndContentsView)

//protected:
public:
	CFileAndContentsView();           // 动态创建所使用的受保护的构造函数
	virtual ~CFileAndContentsView();

public:
	enum { IDD = IDD_FILEANDCONTENTSVIEW };
	CButton	m_subpathbtn;
	CButton	m_mastpathbtn;
	CButton	m_atppathbtn;
	CString	m_subprogpath;
	CString	m_atpprogpath;
	CString	m_mastprogpath;
	//CPathChangeDlg  pathchangedlg;
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMastpathChange();
	afx_msg void OnSubpathChange();

	afx_msg void OnAtppathChange();
	afx_msg void OnKillfocusMastprogpath();
	afx_msg void OnSetfocusMastprogpath();
	afx_msg void OnKillfocusSubprogpath();
	afx_msg void OnSetfocusSubprogpath();
	afx_msg void OnKillfocusAtpprogpath();
	afx_msg void OnSetfocusAtpprogpath();
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedMastpathbtn();
};


