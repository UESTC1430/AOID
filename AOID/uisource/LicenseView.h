#pragma once


#include "resource.h"
// CLicenseView ������ͼ

class CLicenseView : public CFormView
{
	DECLARE_DYNCREATE(CLicenseView)

//protected:
public:
	CLicenseView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CLicenseView();

public:
	enum { IDD = IDD_LICENSEVIEW };
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
	afx_msg void OnBtnOK();
//	bool GetLicenseResult(void);
	bool GetLicenseResult(CTime endtime);
};


