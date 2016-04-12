#pragma once


#include "resource.h"
// CLightView 窗体视图

class CLightView : public CFormView
{
	DECLARE_DYNCREATE(CLightView)

//protected:
public:
	CLightView();           // 动态创建所使用的受保护的构造函数
	virtual ~CLightView();

public:
	enum { IDD = IDD_LIGHTVIEW };
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


