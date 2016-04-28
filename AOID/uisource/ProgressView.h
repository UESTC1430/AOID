#pragma once

#include "resource.h"
#include "TextProgressCtrl.h"
// CProgressView 窗体视图

class CProgressView : public CFormView
{
	DECLARE_DYNCREATE(CProgressView)

//protected:
public:
	CProgressView();           // 动态创建所使用的受保护的构造函数
	virtual ~CProgressView();
	bool WarnMessage(CString str,COLORREF col);
	void DrillProgress(int currentnum,int totalnum);

public:
	enum { IDD = IDD_PROGRESSVIEW };
	CTextProgressCtrl	m_pro;
	CString progressstr;
	COLORREF progresscol;


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
	afx_msg void OnButtonSpace();
	virtual void OnInitialUpdate();
};


