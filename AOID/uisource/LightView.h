#pragma once


#include "resource.h"
// CLightView ������ͼ

class CLightView : public CFormView
{
	DECLARE_DYNCREATE(CLightView)

//protected:
public:
	CLightView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CLightView();

public:
	enum { IDD = IDD_LIGHTVIEW };
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


