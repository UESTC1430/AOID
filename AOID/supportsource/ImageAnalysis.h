#pragma once
#include "stdafx.h"
#include "CV_picture.h"
#include "ImageProcess.h"
// CImageAnalysis ������ͼ

class CImageAnalysis : public CFormView
{
	DECLARE_DYNCREATE(CImageAnalysis)
public:
	CImageAnalysis();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CImageAnalysis();

public:
	enum { IDD = IDD_IMAGEANALYSIS };
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
	afx_msg void OnBnClickedback();
	afx_msg void OnBnClickedsaltshow();
	afx_msg void OnBnClickedHough();
	void salt(Mat image, int n);
	CV_picture m_Show;
	CImageProcess m_imageprocess;
	virtual void OnInitialUpdate();
};


