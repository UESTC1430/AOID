#pragma once


#include "resource.h"
#include "afxwin.h"
// CSoftWareInfoView ������ͼ

class CSoftWareInfoView : public CFormView
{
	

//protected:
public:
	CSoftWareInfoView();                           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	DECLARE_DYNCREATE(CSoftWareInfoView)          
	virtual ~CSoftWareInfoView();
public:
	virtual void OnInitialUpdate();
public:
	enum { IDD = IDD_SOFTWAREINFOVIEW };
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
	CEdit m_edit_version;
	CButton m_btn_clear;
	CButton m_btn_reload;
	CButton m_btn_close;
	afx_msg void OnButton1();
	afx_msg void OnButton3();
	afx_msg void OnButton2();
};


