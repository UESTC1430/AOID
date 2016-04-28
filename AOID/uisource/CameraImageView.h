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
#include "CV_picture.h"
// CCameraImageView ������ͼ

class CCameraImageView : public CFormView
{
	DECLARE_DYNCREATE(CCameraImageView)

public:
	bool mouseexflag;//����϶���ǣ��ñ����Ч��˵����갴��
	CPoint endpoint; //����϶����
	CPoint startpoint;//����϶��յ�

	Point2i location11;
	Point2i rotatofile;
	bool inrectfile;//��ΪTUREʱ��ʾ���ļ�����
	bool inrectcam;
	//--------------------------------------------------------------------�ӹ��ļ���������
	CRect rectfile;
	CDC *m_rectfile;
	int xpcbmax;//�ӹ��ļ����Բ�ĵ������С
	int ypcbmax;
	int xpcbmin;
	int ypcbmin;
	int workwide;//����Ĭ�ϴ�������PCB�Ĵ�С����λ΢��
	int workheight;
	float filescale;//ʵ�ʳߴ������سߴ������ű���<1
	float start_filescale;
	float filewheel;//���ַŴ�ϵ��

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
	//**************************
	int  MAXarea;
	vector<KeyPoint> keypoints1,keypoints2;
	int i_max;
	float p_temp,p_max;

public:
	CCameraImageView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CCameraImageView();
	void DrawcvMat(Mat m_cvImg, UINT ID,bool flag);//�ؼ��ϻ���MAT����ͼ��true����Ҷ�ͼ
	CV_picture m_picture;
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
	afx_msg void InputImage();			//�ӹ��ļ�������ʾ
	afx_msg void OnGetPiont();			//��ȡ��λ��
	afx_msg void CameraimageShow();		//����ͷ�ɼ��ļ���ʾ
	afx_msg void OnCutImage();			//ͼ��ƥ��
	afx_msg void OnBnClickedFocus();
	afx_msg void OnBnClickedtest();
	afx_msg void OnBnClickedHough();
	virtual void OnInitialUpdate();	
private:	
	CV_picture m_camimg;
protected:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


