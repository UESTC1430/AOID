#pragma once


#include "resource.h"
// CUserAdminView ������ͼ

class CUserAdminView : public CFormView
{
	DECLARE_DYNCREATE(CUserAdminView)

//protected:
public:
	CUserAdminView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};


