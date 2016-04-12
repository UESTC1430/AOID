#pragma once
//������Ϊx������Ϊy���ο���
#define ORD1	1//(X,Y)
#define ORD2	2//(Y,X)
#define ORD3	3//(-y,x)
#define ORD4	4//(-x,y)
#define ORD5	5//(-y,x)
#define ORD6	6//(-x,-y)
#define ORD7	7//(x,-y)
#define ORD8	8//(y,-x)

#include "resource.h"
// CCameraImageView ������ͼ

class CCameraImageView : public CFormView
{
	DECLARE_DYNCREATE(CCameraImageView)
public:
	float camscale;
	// protected constructor used by dynamic creation
/*	bool mouseexflag;//����϶���ǣ��ñ����Ч��˵����갴��
	CPoint endpoint; //����϶����
	CPoint startpoint;//����϶��յ�
	bool inrectfile;//��ΪTUREʱ��ʾ���ļ�����
	bool inrectcam;
	//--------------------------------------------------------------------�ӹ��ļ���������
	CRect rectfile;
	CDC *m_rectfile;

	int iholefilein;//����Ƿ��д���ļ�����0��û�е��룬1������
	int xpcbmax;//�ӹ��ļ����Բ�ĵ������С
	int ypcbmax;
	int workwide;//����Ĭ�ϴ�������PCB�Ĵ�С����λ΢��
	int workheight;
	float filescale;//ʵ�ʳߴ������سߴ������ű���

	circlestruct  location;//����ļ����ҵ���Բ
	vector<circlestruct>  locationinfile;
	int Xlu;//�Ŵ��������Ͻ�x����
	int Ylu;//�Ŵ��������Ͻ�y����
	int Xrd;//�Ŵ��������½�x����
	int Yrd;//�Ŵ��������½�y����

	//---------------------------------------------------------------------
	vector<circlestruct>  locationincam;
	CRect rectcam;
	CDC *m_rectcam;
	float camscale;//ʵ�ʳߴ������سߴ������ű���

	vector<vector<Point> > contours1;
//protected:*/
public:
	CCameraImageView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CCameraImageView();
	void DrawcvMat(Mat m_cvImg, UINT ID,bool flag);//�ؼ��ϻ���MAT����ͼ��true����Ҷ�ͼ

public:
	enum { IDD = IDD_CAMERAIMAGEVIEW };
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
	afx_msg void InputImage();
	afx_msg void OnGetPiont();
	afx_msg void CameraimageShow();
	afx_msg void OnCutImage();
	afx_msg void OnBnClickedFocus();
	afx_msg void OnBnClickedtest();
	afx_msg void OnBnClickedHough();
};


