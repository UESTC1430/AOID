#pragma once


/*typedef struct
{
	float x;
	float y;
	float R;

}circlestruct;*/
class CImageProcess
{
public:
	CImageProcess(void);
	~CImageProcess(void);
	typedef struct ACCOUNT
	{
		int x;
		int y;
		int N;
	}account;
	
	vector<vector<Point> > contours;
	vector<vector<Point> > contours_temp;

	int num;
	Mat resultimage;
	Mat rotateimage;
	//------------------------------------------
	int  MAXarea;
//	vector<KeyPoint> keypoints1,keypoints2;//比值法
//	vector<circlestruct>img_split,src_split,end_split;
//	vector<vector<Point> > contours1,contours2;
	vector<DMatch> matches;
	FlannBasedMatcher matcher;
	//vector<Point2f>center;
	//vector<float>radius;
	//--------------------------------------------
	//vector<Point3f> circles;//存放圆心、半径、（x,y）z放半径
//	vector<circlestruct>circles;
	//--------------------------------------------
	bool GetHole(Mat mat);
	Mat HoughGetHole(Mat mat);
	//*******************************************************************************
	//float GetImageValue(Mat mat);//计算图像总梯度，摄像头聚焦用,不改变传入的图像
	//float GetImageValue2(Mat mat);//斜率法
	//float GetImageValue3(Mat mat);//SMD
	//float GetImageValue4(Mat mat);//L改
	//**************************************************************************
	bool ImageCut(Mat mat);//mat为原图像,src为剪切后的图像
	bool ImageRotate(Mat mat,Mat &src,double angle);//输入输出图像、旋转角度、旋转比例、   目前功能是绕中心旋转
	bool ImageResize(Mat mat,Mat &src,double scale);//scale为图像缩小倍数
    int ThresholdOtsu(Mat mat);//灰度图自适应阈值的计算
	//bool ImageSplit(Mat img,Mat src,Mat &resultimg);//比值法
	//bool ImageSplit2(Mat img,Mat src,Mat &resultimg);//边缘匹配法
	//bool ImageSplit3(Mat img,Mat src,Mat &resultimg);//模版匹配法
	//bool ImageSplit4(Mat img,Mat src,Mat &resultimg);//特征点匹配
	//bool ImageSplit5(Mat img,Mat src,Mat &resultimg);//改进型

private:
	
	
public:
	bool JudgeCircle(vector<vector<Point>>contours);
};

