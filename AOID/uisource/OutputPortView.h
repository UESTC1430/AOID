#pragma once


#include "resource.h"
// COutputPortView ������ͼ

class COutputPortView : public CFormView
{
	DECLARE_DYNCREATE(COutputPortView)

//protected:
public:
	COutputPortView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~COutputPortView();

public:
	enum { IDD = IDD_OUTPUTPORTVIEW };
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


