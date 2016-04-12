#pragma once

#include "Resource.h"
#include "staticbutton.h"
// CToolView 窗体视图

class CToolView : public CFormView
{
	DECLARE_DYNCREATE(CToolView)

//protected:
public:
	CToolView();           // 动态创建所使用的受保护的构造函数
	virtual ~CToolView();

public:
	enum { IDD = IDD_TOOLVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

	CStaticButton * m_lockbutton;
	CStaticButton * m_blockbutton;
	CStaticButton * m_toolbutton;//输入阻抗为50欧姆时的耦合
	CStaticButton * m_slowbutton;
	bool toolviewhideflag;
	CRect m_toolviewrect; 

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedLock();
};


