#pragma once

#include "resource.h"

// CProgressView ������ͼ

class CProgressView : public CFormView
{
	DECLARE_DYNCREATE(CProgressView)

//protected:
public:
	CProgressView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CProgressView();

public:
	enum { IDD = IDD_PROGRESSVIEW };
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


