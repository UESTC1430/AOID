#pragma once

#include "Resource.h"
#include "staticbutton.h"
// CToolView ������ͼ

class CToolView : public CFormView
{
	DECLARE_DYNCREATE(CToolView)

//protected:
public:
	CToolView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
	CStaticButton * m_toolbutton;//�����迹Ϊ50ŷķʱ�����
	CStaticButton * m_slowbutton;
	bool toolviewhideflag;
	CRect m_toolviewrect; 

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedLock();
};


