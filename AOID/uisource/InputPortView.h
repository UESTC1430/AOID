#pragma once


#include "resource.h"
// CInputPortView ������ͼ

class CInputPortView : public CFormView
{
	DECLARE_DYNCREATE(CInputPortView)

//protected:
public:
	CInputPortView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CInputPortView();

public:
	enum { IDD = IDD_INPUTPORTVIEW };
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


