#pragma once


#include "resource.h"
// CMachineRecordView 窗体视图

class CMachineRecordView : public CFormView
{
	DECLARE_DYNCREATE(CMachineRecordView)

//protected:
public:
	CMachineRecordView();           // 动态创建所使用的受保护的构造函数
	virtual ~CMachineRecordView();

public:
	enum { IDD = IDD_MACHINERECORDVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	virtual void OnInitialUpdate();
//	afx_msg void OnBnClickedBtndatetime();
	CButton m_Inport;
	CString m_Keywords;
	CListCtrl m_machinerecordlist;
	CComboBox type;
	CString m_typestr;
	HWND mhwnd;
	afx_msg void OnBtnDateTime();
	afx_msg void OnCertern();

};


