#pragma once


#include "resource.h"
// COutputPortView 窗体视图

class COutputPortView : public CFormView
{
	DECLARE_DYNCREATE(COutputPortView)

//protected:
public:
	COutputPortView();           // 动态创建所使用的受保护的构造函数
	virtual ~COutputPortView();

public:
	enum { IDD = IDD_OUTPUTPORTVIEW };
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


