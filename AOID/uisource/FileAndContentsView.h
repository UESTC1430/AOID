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
};


