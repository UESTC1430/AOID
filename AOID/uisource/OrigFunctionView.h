#pragma once


#include "resource.h"
// COrigFunctionView ������ͼ

class COrigFunctionView : public CFormView
{
	DECLARE_DYNCREATE(COrigFunctionView)

//protected:
public:
	COrigFunctionView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~COrigFunctionView();

public:
	enum { IDD = IDD_ORIGFUNCTIONVIEW };
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


