#pragma once


#include "resource.h"
// CUserAdminView 窗体视图

class CUserAdminView : public CFormView
{
	DECLARE_DYNCREATE(CUserAdminView)

//protected:
public:
	CUserAdminView();           // 动态创建所使用的受保护的构造函数
	virtual ~CUserAdminView();

public:
	enum { IDD = IDD_USERADMINVIEW };
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


