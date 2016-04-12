#pragma once

#include "resource.h"
#include "afxwin.h"

// CInchFunctionView 窗体视图

class CInchFunctionView : public CFormView
{
	DECLARE_DYNCREATE(CInchFunctionView)

//protected:
public:
	CInchFunctionView();           // 动态创建所使用的受保护的构造函数
	virtual ~CInchFunctionView();

public:
	enum { IDD = IDD_INCHFUNCTIONVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
/*
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnInitialUpdate();*/
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_xpos;
	CStatic m_ypos;
	CStatic m_zpos;
	CStatic m_picvalue;
	CStatic	m_speed;
	CString	m_XYstep;
	CString	m_Zstep;

	afx_msg void OnBnClickedGetvalue();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBtnUp();
	afx_msg void OnBtnDwon();
	afx_msg void OnButtonUp();
	afx_msg void OnButtonRight();
	afx_msg void OnButtonDown();
	afx_msg void OnButtonLeft();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};


