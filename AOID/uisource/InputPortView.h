#pragma once


#include "resource.h"
// CInputPortView 窗体视图

class CInputPortView : public CFormView
{
	DECLARE_DYNCREATE(CInputPortView)

//protected:
public:
	CInputPortView();           // 动态创建所使用的受保护的构造函数
	virtual ~CInputPortView();

public:
	enum { IDD = IDD_INPUTPORTVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};


