#pragma once

#include "Resource.h"

// CAnalysisView 窗体视图

class CAnalysisView : public CFormView
{
	DECLARE_DYNCREATE(CAnalysisView)

//protected:
public:
	CAnalysisView();           // 动态创建所使用的受保护的构造函数
	virtual ~CAnalysisView();

public:
	enum { IDD = IDD_ANALYSISVIEW };
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


