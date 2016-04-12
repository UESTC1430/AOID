#pragma once


#include "resource.h"
#include "afxwin.h"
// CCameraPosView ������ͼ

class CCameraPosView : public CFormView
{
	DECLARE_DYNCREATE(CCameraPosView)

//protected:
public:
	CCameraPosView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CCameraPosView();

public:
	enum { IDD = IDD_CAMERAPOSVIEW };//����Ի���ID
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
	
public:
//	Mat  camImage;//���ɨ����ͼ��
//	bool  CamStartGrap(Mat img,int nXArea,int nYArea,int L);
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	
public:
	CStatic m_xAera;
	CStatic m_yAera;
	afx_msg void OnCameraConnect();
	afx_msg void OnCameraClose();
	afx_msg void OnBnClickedMoving();
	afx_msg void OnClickedCamera();
};


