#pragma once

#include "resource.h"

// CMFunctionView 窗体视图

class CMFunctionView : public CFormView
{
	DECLARE_DYNCREATE(CMFunctionView)

//protected:
public:
	CMFunctionView();           // 动态创建所使用的受保护的构造函数
	virtual ~CMFunctionView();

public:
	enum { IDD = IDD_MFUNCTIONVIEW };
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
//	afx_msg void OnBtnM1();
	afx_msg void OnSelchangeComboM1();
//	afx_msg void OnSelchangeCombom2();
	afx_msg void OnSelchangeComboM3();
	afx_msg void OnSelchangeComboM2();
	afx_msg void OnSelchangeComboM10();
	afx_msg void OnSelchangeComboM11();
	afx_msg void OnSelchangeComboM12();
	afx_msg void OnSelchangeComboM13();
	afx_msg void OnSelchangeComboM14();
	afx_msg void OnSelchangeComboM4();
	afx_msg void OnSelchangeComboM5();
	afx_msg void OnSelchangeComboM6();
	afx_msg void OnSelchangeComboM7();
	afx_msg void OnSelchangeComboM8();
	afx_msg void OnSelchangeComboM9();
	afx_msg void OnClickedBtnM10();
	afx_msg void OnClickedBtnM11();
	afx_msg void OnClickedBtnM12();
	afx_msg void OnClickedBtnM13();
	afx_msg void OnClickedBtnM14();
	afx_msg void OnClickedBtnM2();
	afx_msg void OnClickedBtnM3();
	afx_msg void OnClickedBtnM4();
	afx_msg void OnClickedBtnM5();
	afx_msg void OnClickedBtnM6();
	afx_msg void OnClickedBtnM7();
	afx_msg void OnClickedBtnM8();
	afx_msg void OnClickedBtnM9();
	afx_msg void OnClickedBtnM1();
};


