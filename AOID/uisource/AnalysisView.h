#pragma once

#include "Resource.h"
#include <afxext.h>
// CAnalysisView 窗体视图

class CAnalysisView : public CFormView
{
	DECLARE_DYNCREATE(CAnalysisView)

//protected:
public:
	CAnalysisView();           // 动态创建所使用的受保护的构造函数
	virtual ~CAnalysisView();

	// Form Data
public:
	//{{AFX_DATA(CAnalysisView)
	enum { IDD = IDD_ANALYSISVIEW };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	//CClientDC  m_rectrader;
	CRect radarrect;


	// Attributes
public:
	circlestruct radarpoint;
	vector<circlestruct>m_radarpoint;
	
	vector<CIRMATCH> m_circlematching;
	CIRMATCH temp_circlematch;

	vector<Point2f>infile;
	vector<Point2f>incam;
	vector<uchar>m;

	vector<Point2f>cam_P;
	vector<Point2f>camOut;
	vector<float>fileR;
	// Operations
public:

	CPoint startpoint,endpoint;
	bool mouseexflag ; //鼠标按下标记
	bool inrectchart;
	float Xscale;
	int circlenuminfile,circlenumincam;//存放圆的个数
	float matchscale;
	float matchangle;

// Overrides
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedRader();

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	bool ProgInChart(CPoint start,CPoint end);
	

	afx_msg void OnRadar();
};


