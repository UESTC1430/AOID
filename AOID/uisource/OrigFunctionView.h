#pragma once


#include "resource.h"
// COrigFunctionView 窗体视图

class COrigFunctionView : public CFormView
{
	DECLARE_DYNCREATE(COrigFunctionView)

//protected:
public:
	COrigFunctionView();           // 动态创建所使用的受保护的构造函数
	virtual ~COrigFunctionView();

public:
	enum { IDD = IDD_ORIGFUNCTIONVIEW };
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


