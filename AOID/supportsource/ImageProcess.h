#pragma once

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
	Mat camerafusb;
	Mat resultimage;
	Mat cut_1;
	Mat rotateimage;
	Mat rotateimage2;
	Mat rotateimage3;
	int  MAXarea;
	vector<KeyPoint> keypoints1,keypoints2;//比值法
	vector<circlestruct>img_split,src_split,end_split;
	vector<vector<Point> > contours1,contours2;
	vector<DMatch> matches;
	FlannBasedMatcher matcher;
	vector<circlestruct>circles;//3点定圆法找圆结果
	vector<circlestruct>circles_mu;//外接圆找圆结果
	vector<Point2f>infile;
	vector<Point2f>incam;
	vector<uchar>m;
	vector<circlestruct>  locationincam_temp,locationinfile_temp;






	//************************************************************图像圆的查找
	bool GetHole(Mat mat);//像素级
	bool GetHighQHole(Mat mat,vector<Point>contour,int &max_num);//亚像素级
	//************************************************************图像自适应阈值
	int ThresholdOtsu(Mat mat);//大津法
	//************************************************************计算图像清晰度
	float GetImageValue(Mat mat);//Laplacian修改
	float GetImageValue2(Mat mat);//边界斜率法
	float GetImageValue3(Mat mat);//SMD
	float GetImageValue4(Mat mat);//Laplacian
	//**************************************************************************图像旋转和放大缩小函数
	bool ImageCutAndRotate(Mat inputimg,Mat &outputimg,float matchangle,float matchscale,vector<cirmatch> circlesmatch,int xpcbmin,int ypcbmin,int xpcbmax,int ypcbmax);//mat为原图像,src为剪切后的图像
	bool ImageRotate(Mat mat,Mat &src,double angle);//输入输出图像、旋转角度、旋转比例、   目前功能是绕中心旋转
	bool ImageResize(Mat mat,Mat &src,double scale);//scale为图像缩小倍数
    //******************************************************************************图像拼接测试
	bool ImageSplit (Mat img,Mat src,Mat &resultimg);//比值法
	bool ImageSplit2(Mat img,Mat src,Mat &resultimg);//边缘匹配法
	bool ImageSplit3(Mat img,Mat src,Mat &resultimg);//模版匹配法
	bool ImageSplit4(Mat img,Mat src,Mat &resultimg);//特征点匹配
	bool ImageSplit5(Mat img,Mat src,Mat &resultimg);//改进型
	//*********************************************************************************************图像定位
	bool FourPiontPosition(	vector<circlestruct>  locationincam,vector<circlestruct> locationinfile ,float &matchangle,float &matchscale);//四点定位
	bool HighQualityLocation(vector<cirmatch> circlesmatch,float &matchangle,float &matchscale);//所有匹配对任取四对，调用四点定位法
	bool HighQualityLocation2(vector<cirmatch> circlesmatch,float &matchangle,float &matchscale);//所有匹配对计算旋转角度和放大比
	bool HighQualityLocation3(vector<cirmatch> circlesmatch,float &matchangle,float &matchscale);//刨除错误匹配后，所有匹配对任取四对，调用四点定位法
	
	

};

