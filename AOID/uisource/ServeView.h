#pragma once

#include "resource.h"

// CServeView ������ͼ

class CServeView : public CFormView
{
	DECLARE_DYNCREATE(CServeView)

//protected:
public:
	CServeView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CServeView();

public:
	enum { IDD = IDD_SERVEVIEW };
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


