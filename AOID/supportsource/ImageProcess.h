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
	vector<KeyPoint> keypoints1,keypoints2;//��ֵ��
	vector<circlestruct>img_split,src_split,end_split;
	vector<vector<Point> > contours1,contours2;
	vector<DMatch> matches;
	FlannBasedMatcher matcher;
	vector<circlestruct>circles;//3�㶨Բ����Բ���
	vector<circlestruct>circles_mu;//���Բ��Բ���
	vector<Point2f>infile;
	vector<Point2f>incam;
	vector<uchar>m;
	vector<circlestruct>  locationincam_temp,locationinfile_temp;






	//************************************************************ͼ��Բ�Ĳ���
	bool GetHole(Mat mat);//���ؼ�
	bool GetHighQHole(Mat mat,vector<Point>contour,int &max_num);//�����ؼ�
	//************************************************************ͼ������Ӧ��ֵ
	int ThresholdOtsu(Mat mat);//���
	//************************************************************����ͼ��������
	float GetImageValue(Mat mat);//Laplacian�޸�
	float GetImageValue2(Mat mat);//�߽�б�ʷ�
	float GetImageValue3(Mat mat);//SMD
	float GetImageValue4(Mat mat);//Laplacian
	//**************************************************************************ͼ����ת�ͷŴ���С����
	bool ImageCutAndRotate(Mat inputimg,Mat &outputimg,float matchangle,float matchscale,vector<cirmatch> circlesmatch,int xpcbmin,int ypcbmin,int xpcbmax,int ypcbmax);//matΪԭͼ��,srcΪ���к��ͼ��
	bool ImageRotate(Mat mat,Mat &src,double angle);//�������ͼ����ת�Ƕȡ���ת������   Ŀǰ��������������ת
	bool ImageResize(Mat mat,Mat &src,double scale);//scaleΪͼ����С����
    //******************************************************************************ͼ��ƴ�Ӳ���
	bool ImageSplit (Mat img,Mat src,Mat &resultimg);//��ֵ��
	bool ImageSplit2(Mat img,Mat src,Mat &resultimg);//��Եƥ�䷨
	bool ImageSplit3(Mat img,Mat src,Mat &resultimg);//ģ��ƥ�䷨
	bool ImageSplit4(Mat img,Mat src,Mat &resultimg);//������ƥ��
	bool ImageSplit5(Mat img,Mat src,Mat &resultimg);//�Ľ���
	//*********************************************************************************************ͼ��λ
	bool FourPiontPosition(	vector<circlestruct>  locationincam,vector<circlestruct> locationinfile ,float &matchangle,float &matchscale);//�ĵ㶨λ
	bool HighQualityLocation(vector<cirmatch> circlesmatch,float &matchangle,float &matchscale);//����ƥ�����ȡ�Ķԣ������ĵ㶨λ��
	bool HighQualityLocation2(vector<cirmatch> circlesmatch,float &matchangle,float &matchscale);//����ƥ��Լ�����ת�ǶȺͷŴ��
	bool HighQualityLocation3(vector<cirmatch> circlesmatch,float &matchangle,float &matchscale);//�ٳ�����ƥ�������ƥ�����ȡ�Ķԣ������ĵ㶨λ��
	
	

};

