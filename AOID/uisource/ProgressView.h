#pragma once

#include "resource.h"
#include "TextProgressCtrl.h"
// CProgressView ������ͼ

class CProgressView : public CFormView
{
	DECLARE_DYNCREATE(CProgressView)

//protected:
public:
	CProgressView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CProgressView();
	bool WarnMessage(CString str,COLORREF col);
	void DrillProgress(int currentnum,int totalnum);

public:
	enum { IDD = IDD_PROGRESSVIEW };
	CTextProgressCtrl	m_pro;
	CString progressstr;
	COLORREF progresscol;


#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnButtonSpace();
	virtual void OnInitialUpdate();
};


