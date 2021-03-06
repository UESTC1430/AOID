#pragma once
//以向左为x，向上为y作参考的
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
// CCameraImageView 窗体视图

class CCameraImageView : public CFormView
{
	DECLARE_DYNCREATE(CCameraImageView)

public:
	bool mouseexflag;//鼠标拖动标记，该标记有效，说明鼠标按下
	CPoint endpoint; //鼠标拖动起点
	CPoint startpoint;//鼠标拖动终点

	Point2i location11;
	Point2i rotatofile;
	bool inrectfile;//当为TURE时表示在文件区域
	bool inrectcam;
	//--------------------------------------------------------------------加工文件参数处理
	CRect rectfile;
	CDC *m_rectfile;
	int xpcbmax;//加工文件打孔圆心的最大最小
	int ypcbmax;
	int xpcbmin;
	int ypcbmin;
	int workwide;//程序默认处理的最大PCB的大小，单位微米
	int workheight;
	float filescale;//实际尺寸与像素尺寸间的缩放比例<1
	float start_filescale;
	float filewheel;//滚轮放大系数

	circlestruct  location;//存放文件中找到的圆
	vector<circlestruct>  locationinfile;
	int Xlu;//放大区域左上角x坐标
	int Ylu;//放大区域左上角y坐标
	int Xrd;//放大区域右下角x坐标
	int Yrd;//放大区域右下角y坐标

	//---------------------------------------------------------------------
	vector<circlestruct>  locationincam;
	CRect rectcam;
	CDC *m_rectcam;
	float camscale;//实际尺寸与像素尺寸间的缩放比例
	RotatedRect     End_Rage2D; //轮廓最小外接矩形参数  
	
	vector<vector<Point> > contours1;
	//**************************
	int  MAXarea;
	vector<KeyPoint> keypoints1,keypoints2;
	int i_max;
	float p_temp,p_max;

public:
	CCameraImageView();           // 动态创建所使用的受保护的构造函数
	virtual ~CCameraImageView();
	void DrawcvMat(Mat m_cvImg, UINT ID,bool flag);//控件上绘制MAT类型图：true处理灰度图
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void InputImage();			//加工文件输入显示
	afx_msg void OnGetPiont();			//获取定位点
	afx_msg void CameraimageShow();		//摄像头采集文件显示
	afx_msg void OnCutImage();			//图像匹配
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
public:
	bool ProgressInRectfile(CPoint start,CPoint end);	
	bool GetSelectCircleFill(int x,int y);//根据x，y值求选中行
	bool ProgressInRectCam(CPoint start,CPoint end);
	bool GetSelectCircleCam(int x, int y);//根据x，y值求选中行
	afx_msg void OnBnClickedgettestimage();
	afx_msg void OnBnClickedCamera();
	int OnCamera();
	afx_msg void OnBnClickedHoughline();
	int Findn(Mat * img, int i, int j);//查找像素点非零邻点的个数
	//Mat * ThinImage(Mat * img, int k); //细化直线功能函数
	/** 
 * @brief 对输入图像进行细化 
 * @param src为输入图像,用cvThreshold函数处理过的8位灰度图像格式，元素中只有0与1,1代表有元素，0代表为空白 
 * @param maxIterations限制迭代次数，如果不进行限制，默认为-1，代表不限制迭代次数，直到获得最终结果 
 * @return 为对src细化后的输出图像,格式与src格式相同，元素中只有0与1,1代表有元素，0代表为空白 
 */  
	Mat thinImage(const Mat & src, const int maxIterations );
	//轮廓最小外接矩形识别直线
	void Box();
	//画轮廓最小外接矩形
	void DrawBox(CvBox2D box,Mat img);
};


