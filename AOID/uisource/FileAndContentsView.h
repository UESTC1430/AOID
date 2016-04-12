#pragma once

#include "resource.h"

// CFileAndContentsView ������ͼ

class CFileAndContentsView : public CFormView
{
	DECLARE_DYNCREATE(CFileAndContentsView)

//protected:
public:
	CFileAndContentsView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CFileAndContentsView();

public:
	enum { IDD = IDD_FILEANDCONTENTSVIEW };
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
	afx_msg void OnMastpathChange();
	afx_msg void OnSubpathChange();
};


