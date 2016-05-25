#pragma once

#include "resource.h"

// CMastProgInView 窗体视图

class CMastProgInView : public CFormView
{
	DECLARE_DYNCREATE(CMastProgInView)

//protected:
public:
	CMastProgInView();           // 动态创建所使用的受保护的构造函数
	virtual ~CMastProgInView();

public:
	enum { IDD = IDD_MASTPROGINVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
	virtual void OnInitialUpdate();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_diskdrive;
	CComboBox m_mainprofilename;
	CComboBox m_filetype;
	CString m_filecontentstr;
	CListCtrl m_filenamelist;
	CString m_pathstr;
	CString filetype;
	int filecount;    //主程序文件名下拉列表行数
	CString pathandname;
//	StyleFormat dlg;
	afx_msg void OnSelchangeCombodrive();
	afx_msg void OnSelchangeComboFileType();
	afx_msg void OnDblclkListfilename(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnInport();
};


