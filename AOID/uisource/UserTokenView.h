#pragma once


#include "resource.h"
// CUserTokenView ������ͼ

class CUserTokenView : public CFormView
{
	DECLARE_DYNCREATE(CUserTokenView)

//protected:
public:
	CUserTokenView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CUserTokenView();

public:
	enum { IDD = IDD_USERTOKENVIEW };
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
//	afx_msg void OnCheck0();
//	afx_msg void OnCheck1();
//	afx_msg void OnCheck2();
//	afx_msg void OnCheck3();
//	afx_msg void OnCheck4();
//	afx_msg void OnCheck5();
//	afx_msg void OnCheck6();
//	afx_msg void OnCheck7();
//	afx_msg void OnCheck8();
//	afx_msg void OnCheck9();
//	afx_msg void OnCheck10();
//	afx_msg void OnCheck11();
//	afx_msg void OnCheck12();
	virtual void OnInitialUpdate();
//	int FlagChange(int num);
};


