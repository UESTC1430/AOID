#pragma once


#include "resource.h"
#include "afxwin.h"
// CCameraPosView 窗体视图

class CCameraPosView : public CFormView
{
	DECLARE_DYNCREATE(CCameraPosView)

//protected:
public:
	CCameraPosView();           // 动态创建所使用的受保护的构造函数
	virtual ~CCameraPosView();

public:
	enum { IDD = IDD_CAMERAPOSVIEW };//定义对话框ID
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
	
public:
//	Mat  camImage;//存放扫描后的图像
//	bool  CamStartGrap(Mat img,int nXArea,int nYArea,int L);
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	
public:
	CStatic m_xAera;
	CStatic m_yAera;
	afx_msg void OnCameraConnect();
	afx_msg void OnCameraClose();
	afx_msg void OnBnClickedMoving();
	afx_msg void OnClickedCamera();
};


