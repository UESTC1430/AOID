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
//	vector<KeyPoint> keypoints1,keypoints2;//��ֵ��
//	vector<circlestruct>img_split,src_split,end_split;
//	vector<vector<Point> > contours1,contours2;
	vector<DMatch> matches;
	FlannBasedMatcher matcher;
	//vector<Point2f>center;
	//vector<float>radius;
	//--------------------------------------------
	//vector<Point3f> circles;//���Բ�ġ��뾶����x,y��z�Ű뾶
//	vector<circlestruct>circles;
	//--------------------------------------------
	bool GetHole(Mat mat);
	Mat HoughGetHole(Mat mat);
	//*******************************************************************************
	//float GetImageValue(Mat mat);//����ͼ�����ݶȣ�����ͷ�۽���,���ı䴫���ͼ��
	//float GetImageValue2(Mat mat);//б�ʷ�
	//float GetImageValue3(Mat mat);//SMD
	//float GetImageValue4(Mat mat);//L��
	//**************************************************************************
	bool ImageCut(Mat mat);//matΪԭͼ��,srcΪ���к��ͼ��
	bool ImageRotate(Mat mat,Mat &src,double angle);//�������ͼ����ת�Ƕȡ���ת������   Ŀǰ��������������ת
	bool ImageResize(Mat mat,Mat &src,double scale);//scaleΪͼ����С����
    int ThresholdOtsu(Mat mat);//�Ҷ�ͼ����Ӧ��ֵ�ļ���
	//bool ImageSplit(Mat img,Mat src,Mat &resultimg);//��ֵ��
	//bool ImageSplit2(Mat img,Mat src,Mat &resultimg);//��Եƥ�䷨
	//bool ImageSplit3(Mat img,Mat src,Mat &resultimg);//ģ��ƥ�䷨
	//bool ImageSplit4(Mat img,Mat src,Mat &resultimg);//������ƥ��
	//bool ImageSplit5(Mat img,Mat src,Mat &resultimg);//�Ľ���

private:
	
	
public:
	bool JudgeCircle(vector<vector<Point>>contours);
};

