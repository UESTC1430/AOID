#pragma once

#include "resource.h"

// CInfoView ������ͼ

class CInfoView : public CFormView
{
	DECLARE_DYNCREATE(CInfoView)


public:
	CInfoView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CInfoView();


	enum { IDD = IDD_INFOVIEW };
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


