#include "stdafx.h"
#include "AOID.h"
#include "ImageProcess.h"

//#include "CameraImageView.h"
//#define camscale 56;
#define splitnum  1000
#define  x_off     30
//bool lessmarkR(const circlestruct &s1,const circlestruct &s2);
//bool lessmarkY(const circlestruct &s1,const circlestruct &s2);
//bool lessmarkX(const circlestruct &s1,const circlestruct &s2);
CImageProcess::CImageProcess(void)
{
}


CImageProcess::~CImageProcess(void)
{
}
/*bool CImageProcess::GetHole(Mat mat)
{
	
	contours.clear();
	Mat src;
	Mat mat= imread("F:\\result.bmp",1);
	mat.copyTo(src);
	//mat.copyTo(src);
	int threshold1=ThresholdOtsu(src);//����Ӧ��ֵ���㣻
	threshold(src,src,threshold1,255,THRESH_BINARY);//��ֵͼ�����ɣ�
	findContours(src,contours,CV_RETR_LIST,CV_CHAIN_APPROX_NONE);//
	int num=contours.size();
	double area1=0,length=0;
	int circlenum=0;
	Point2f center1;
	//float radius1;
	circles.clear();
	circlestruct circles1;
	for (int i=0;i<num;i++)
	{
	
		area1=contourArea(contours[i]);//�������
		length=contours[i].size();//�����ܳ�
		//int xsum=0,ysum=0;
		//�㷨����0.95��(��L^2)/(4*PI))<S<��L^2)/(4*PI)���ͣ��ܳ�ȷ��ʱ�������ΪԲ������ʽ�ұߺ����
		if (  ((0.5*length*length)<(4*PI*area1)) &&(length>30))
		{
			/*circlenum++;
			minEnclosingCircle( (Mat)contours[i], center1, radius1);//����С���Բ
			circles1.x=center1.x;
			circles1.y=center1.y; 
			circles1.R=radius1;
			circles.push_back(circles1);	*/

/*
		Point vi,vj,vk;
		int n=contours[i].size();
		vi=contours[i][0];
		vj=contours[i][n/3];//  n/4
		vk=contours[i][(n*2)/3]; // n/2
		float a,b,r;
		a=((vk.y-vi.y)*(vj.x*vj.x+vj.y*vj.y-vi.x*vi.x-vi.y*vi.y)-(vj.y-vi.y)*(vk.x*vk.x+vk.y*vk.y-vi.x*vi.x-vi.y*vi.y))/((2.0)*((vj.x-vi.x)*(vk.y-vi.y)-(vk.x-vi.x)*(vj.y-vi.y)));
		b=((vj.x-vi.x)*(vk.x*vk.x+vk.y*vk.y-vi.x*vi.x-vi.y*vi.y)-(vk.x-vi.x)*(vj.x*vj.x+vj.y*vj.y-vi.x*vi.x-vi.y*vi.y))/((2.0)*((vj.x-vi.x)*(vk.y-vi.y)-(vk.x-vi.x)*(vj.y-vi.y)));
		r=sqrt((vi.x-a)*(vi.x-a)+(vi.y-b)*(vi.y-b));

		Point vi2,vj2,vk2;
		
		vi2=contours[i][n/6];
		vj2=contours[i][n/2];//  n/4
		vk2=contours[i][(n*5)/6]; // n/2
		float a2,b2,r2;
		a2=((vk2.y-vi2.y)*(vj2.x*vj2.x+vj2.y*vj2.y-vi2.x*vi2.x-vi2.y*vi2.y)-(vj2.y-vi2.y)*(vk2.x*vk2.x+vk2.y*vk2.y-vi2.x*vi2.x-vi2.y*vi2.y))/((2.0)*((vj2.x-vi2.x)*(vk2.y-vi2.y)-(vk2.x-vi2.x)*(vj2.y-vi2.y)));
		b2=((vj2.x-vi2.x)*(vk2.x*vk2.x+vk2.y*vk2.y-vi2.x*vi2.x-vi2.y*vi2.y)-(vk2.x-vi2.x)*(vj2.x*vj2.x+vj2.y*vj2.y-vi2.x*vi2.x-vi2.y*vi2.y))/((2.0)*((vj2.x-vi2.x)*(vk2.y-vi2.y)-(vk2.x-vi2.x)*(vj2.y-vi2.y)));
		r2=sqrt((vi2.x-a2)*(vi2.x-a2)+(vi2.y-b2)*(vi2.y-b2));


		circles1.x=(a+a2)/2;
		circles1.y=(b+b2)/2; 
		circles1.R=(r+r2)/2;
		circles.push_back(circles1);
				
		}
	}
	//JudgeCircle(contours);
	
	sort(circles.begin(), circles.end(),lessmarkR);
	return TRUE;
}    
*/

int CImageProcess::ThresholdOtsu(Mat mat)
{
	int height=mat.rows;
	int width=mat.cols;
	//histogram
	float histogram[256]={0};
	for (int i=0;i<height;i++)
	{
		unsigned char *p=(unsigned char *)mat.data+mat.step*i;
		for(int j=0;j<width;j++)
		{
			histogram[*p++]++;
		}
	}
	//normalize histogram
	int size=height*width;
	for (int i=0;i<256;i++)
	{
		histogram[i]=histogram[i]/size;
	}
	//average pixel value
	float avgValue=0;
	for (int i=0;i<256;i++)
	{
		avgValue+=i*histogram[i];
	}
	int threshold1;
	float maxVariance=0;
	float w=0,u=0;
	for (int i=0;i<256;i++)
	{
		w+=histogram[i];
		u+=i*histogram[i];
		float t=avgValue*w-u;
		float variance=t*t/(w*(1-w));
		if (variance>maxVariance)
		{
			maxVariance=variance;
			threshold1=i;
		}
	}
	return threshold1;
}

bool CImageProcess:: ImageRotate(Mat mat,Mat &src,double angle)
{
	int length;//���ͼ��Ŀ�Ȼ�߶�  
	//Ϊ�˱�֤���������ת���ܷ��£����ͼ��ĳ��Ϳ���Ϊ����ͼ��Խ��߳��ȳ���SCALE  
	//���������С(SCALE<=1)�������ᵼ����ʱͼ���зŲ���ԭͼ�����Զ���������С����������ͼ�����ʱͼ��ĳ�����Ϊԭͼ�ĶԽ��߳���  
	float temp = (mat.cols*mat.cols) + (mat.rows*mat.rows) ;
	length = sqrt(temp);  
	//������ʱͼ�񣬳�����Դͼ��ĶԽ��߳��ȣ���Դͼ���Ƶ���ʱͼ������ĺ��ٱ任  
	Mat tempImg=Mat::zeros(length,length,mat.type());//��ʱͼ�񣬴�С�����ͼ��һ����  
	int ROI_x = length/2 - mat.cols/2;//ROI�������Ͻǵ�x����  1
	int ROI_y = length/2 - mat.rows/2;//ROI�������Ͻǵ�y����  
	Rect ROIRect(ROI_x,ROI_y,mat.cols,mat.rows);//ROI����  */
	Mat tempImgROI2(tempImg,ROIRect);//tempImg���м䲿��  
	mat.copyTo(tempImgROI2);//��ԭͼ���Ƶ�tempImg������  
	Point2f center(length/2,length/2);//��ת����  
	Mat M = getRotationMatrix2D(center,angle,1);//������ת�ķ���任����
	warpAffine(tempImg,src,M,Size(length,length));
	//����任  
	/*Mat rot_mat=getRotationMatrix2D(L1,angle,scale);
	warpAffine(mat,rotatoimage,rot_mat,mat.size());*/
//	Mat src5 =(Mat_<double>(2,3)<<1,0,0,0,1,0);
//	warpAffine(src,src,src5,Size(length,length));
	return TRUE;
}
