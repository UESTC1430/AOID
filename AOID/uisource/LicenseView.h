#pragma once


#include "resource.h"
// CLicenseView 窗体视图

class CLicenseView : public CFormView
{
	DECLARE_DYNCREATE(CLicenseView)

//protected:
public:
	CLicenseView();           // 动态创建所使用的受保护的构造函数
	virtual ~CLicenseView();

public:
	enum { IDD = IDD_LICENSEVIEW };
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
	afx_msg void OnBtnOK();
//	bool GetLicenseResult(void);
	bool GetLicenseResult(CTime endtime);
};


