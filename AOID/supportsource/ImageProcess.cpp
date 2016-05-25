#include "stdafx.h"
#include "AOID.h"
#include "ImageProcess.h"

//#include "CameraImageView.h"
//#define camscale 56;
#define splitnum  1000
#define  x_off     30
bool lessmarkR(const circlestruct &s1,const circlestruct &s2);
bool lessmarkY(const circlestruct &s1,const circlestruct &s2);
bool lessmarkX(const circlestruct &s1,const circlestruct &s2);
CImageProcess::CImageProcess(void)
{
}

bool lessmarkR(const circlestruct &s1,const circlestruct &s2)
{
	if (s1.R>s2.R)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}

bool lessmarkY(const circlestruct &s1,const circlestruct &s2)
{
	if (s1.y>s2.y)
		return 1;
	else
		return 0;
}

bool lessmarkX(const circlestruct &s1,const circlestruct &s2)
{
	if (s1.x>s2.x)
		return 1;
	else
		return 0;
}

CImageProcess::~CImageProcess(void)
{
}
bool CImageProcess::GetHole  (Mat mat)
{
	Mat src,src1,src2; 
	mat.copyTo(src1);
	medianBlur(src1,src,5);//中值滤波
//	imwrite("G:/全图滤波图.bmp",src);
	int threshold1=230;//图像增强后设定阈值
	threshold(src,src2,threshold1,255,THRESH_BINARY);//二值图的生成；
//	imwrite("G:/全图二值图.bmp",src2);
	findContours(src2,contours,CV_RETR_LIST,CV_CHAIN_APPROX_NONE);
	int num=contours.size();
	double area1=0,length=0;
	int circlenum=0;
	Point2f center1;
	circles.clear();
	for (int i=0;i<num;i++)
	{
	
		area1=contourArea(contours[i]);//区域面积
		length=contours[i].size();//区域周长

		//算法：（0.95）(（L^2)/(4*PI))<S<（L^2)/(4*PI)解释：周长确定时面积最大的为圆，不等式右边恒成立
		if (length>5&&(0.8*length*length)<(4*PI*area1)&&length>16&&area1>16)
		{
			//*************************************************************将找到的轮廓进行亚精度变换
			int max_num;
			GetHighQHole(src,contours[i],max_num);
		}
	}
	//JudgeCircle(contours);*/
	/*circles_hough.clear();
	HoughCircles(src,circles_hough,CV_HOUGH_GRADIENT,1,src.cols/10);*/
	//sort(circles_hough.begin(), circles_hou.end(),lessmarkR);



	sort(circles.begin(), circles.end(),lessmarkR);
	sort(circles_mu.begin(), circles_mu.end(),lessmarkR);
	return TRUE;
}    
bool CImageProcess::GetHighQHole(Mat mat,vector<Point>contour,int &max_num)
{
   int x_min=mat.cols,x_max=0,y_min=mat.rows,y_max=0;
   int num=contour.size();
   for (int i=0;i<num;i++)
   {
	   if (contour[i].x>x_max)
		   x_max=contour[i].x;
	   if (contour[i].x<x_min)
		   x_min=contour[i].x;
	   if (contour[i].y>y_max)
		   y_max=contour[i].y;
	   if (contour[i].y<y_min)
		   y_min=contour[i].y;
   }
   Rect box;
   box.x=x_min-1;
   box.y=y_min-1;
   box.width=x_max-x_min+2;
   box.height=y_max-y_min+2;
   Mat cut(mat,box);
   Mat src,src1;
   ImageResize(cut,src,10);//图像放大
   threshold(src,src1,100,255,THRESH_BINARY);//二值图的生成；
   findContours(src1,contours_temp,CV_RETR_LIST,CV_CHAIN_APPROX_NONE);
   int num_temp=contours_temp.size();
   int max_size=contours_temp[0].size();
   max_num=0;
   for (int i=0;i<num_temp;i++)
   {
	   int temp=contours_temp[i].size();
	   if(temp>max_size)
	   {
		   max_size=temp;
		   max_num=i;
	   }
   }
   for (int i=0;i<max_size;i++)
   {
	   contours_temp[max_num][i].x+=(x_min-1)*10;
       contours_temp[max_num][i].y+=(y_min-1)*10;
   }
   	    Point2f vi,vj,vk;
		int n=contours_temp[max_num].size();
		
		//*****************************************************
		vi.x=(float)contours_temp[max_num][0].x/10.0;
		vi.y=(float)contours_temp[max_num][0].y/10.0;
		vj.x=(float)contours_temp[max_num][n/3].x/10.0;//  n/4
		vj.y=(float)contours_temp[max_num][n/3].y/10.0;//  n/4
		vk.x=(float)contours_temp[max_num][(n*2)/3].x/10.0; // n/2
		vk.y=(float)contours_temp[max_num][(n*2)/3].y/10.0;

		float a,b,r;
		a=((vk.y-vi.y)*(vj.x*vj.x+vj.y*vj.y-vi.x*vi.x-vi.y*vi.y)-(vj.y-vi.y)*(vk.x*vk.x+vk.y*vk.y-vi.x*vi.x-vi.y*vi.y))/((2.0)*((vj.x-vi.x)*(vk.y-vi.y)-(vk.x-vi.x)*(vj.y-vi.y)));
		b=((vj.x-vi.x)*(vk.x*vk.x+vk.y*vk.y-vi.x*vi.x-vi.y*vi.y)-(vk.x-vi.x)*(vj.x*vj.x+vj.y*vj.y-vi.x*vi.x-vi.y*vi.y))/((2.0)*((vj.x-vi.x)*(vk.y-vi.y)-(vk.x-vi.x)*(vj.y-vi.y)));
		r=sqrt((vi.x-a)*(vi.x-a)+(vi.y-b)*(vi.y-b));

		Point2f vi2,vj2,vk2;
		vi2.x=(float)contours_temp[max_num][n/6].x/10.0;
		vi2.y=(float)contours_temp[max_num][n/6].y/10.0;
		vj2.x=(float)contours_temp[max_num][n/2].x/10.0;//  n/4
		vj2.y=(float)contours_temp[max_num][n/2].y/10.0;//  n/4
		vk2.x=(float)contours_temp[max_num][(n*5)/6].x/10.0; // n/2
		vk2.y=(float)contours_temp[max_num][(n*5)/6].y/10.0; // n/2
		float a2,b2,r2;
		a2=((vk2.y-vi2.y)*(vj2.x*vj2.x+vj2.y*vj2.y-vi2.x*vi2.x-vi2.y*vi2.y)-(vj2.y-vi2.y)*(vk2.x*vk2.x+vk2.y*vk2.y-vi2.x*vi2.x-vi2.y*vi2.y))/((2.0)*((vj2.x-vi2.x)*(vk2.y-vi2.y)-(vk2.x-vi2.x)*(vj2.y-vi2.y)));
		b2=((vj2.x-vi2.x)*(vk2.x*vk2.x+vk2.y*vk2.y-vi2.x*vi2.x-vi2.y*vi2.y)-(vk2.x-vi2.x)*(vj2.x*vj2.x+vj2.y*vj2.y-vi2.x*vi2.x-vi2.y*vi2.y))/((2.0)*((vj2.x-vi2.x)*(vk2.y-vi2.y)-(vk2.x-vi2.x)*(vj2.y-vi2.y)));
		r2=sqrt((vi2.x-a2)*(vi2.x-a2)+(vi2.y-b2)*(vi2.y-b2));

		
		circlestruct circles1;
		circles1.x=(a+a2)/2.0;
		circles1.y=(b+b2)/2.0; 
		circles1.R=(r+r2)/2.0;
		circles.push_back(circles1);	
 		Moments mu;
		mu=moments(contours_temp[max_num]);
		circles1.x=(mu.m10)*0.1/(mu.m00);
		circles1.y=(mu.m01)*0.1/(mu.m00);
		circles1.R=(r+r2)/2.0;
		circles_mu.push_back(circles1);
        return true;
}

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

float CImageProcess::GetImageValue(Mat mat)
{

	float Isum=0;
	int Ixy;
	int rows = mat.rows;
	int cols = mat.cols;
	int sum  = rows*cols;
	for(int i=50;i<rows-52;i++)
	{
		for(int j=500;j<cols-502;j++)
		{
			Ixy= (-1)* mat.at<unsigned char>(i-1,j-1) + (-4)* mat.at<unsigned char>(i-1,j)+ (-1)* mat.at<unsigned char>(i-1,j+1)+
				(-4)* mat.at<unsigned char>(i,j-1)   +  20*  mat.at<unsigned char>(i,j)  + (-4)* mat.at<unsigned char>(i,j+1) +
				(-1)* mat.at<unsigned char>(i+1,j-1) + (-4)* mat.at<unsigned char>(i+1,j)+ (-1)* mat.at<unsigned char>(i+1,j+1);
			Isum+= abs(Ixy);
		}
	}

	if ( 0 >= sum)
		return 0 ;
	return  (Isum/sum) ;

}

float CImageProcess::GetImageValue2(Mat mat)
{

	float Isum;
	Isum=0;
	int rows = mat.rows;
	int cols = mat.cols;
	int sum  = rows*cols;
	float valuecol=0;
	int time=0;
	for(int i=0;i<mat.rows;i++)
	{
		int j=0;
		account account1,account2;
		account1.x=0;
		account1.y=0;
		account1.N=0;
		account2.x=0;
		account2.y=0;
		account2.N=0;
		while(j<mat.cols-2)
		{
			if (mat.at<unsigned char>(i,j)>mat.at<unsigned char>(i,j+1))
			{
				account2.x=i;
				account2.y=j;
				account2.N=2;
				j++;
				while(mat.at<unsigned char>(i,j)>mat.at<unsigned char>(i,j+1))
				{
					j++;
					if (j>mat.cols-2)
					{
						break;
					}
					account2.N++;
				}
			}
			if (account2.N>account1.N)
			{
				account1.x=account2.x;
				account1.y=account2.y;
				account1.N=account2.N;
			}
			j++;

		}
		if (account1.N>0)
		{			
			float vx=(account1.N+1)*(1.0)/2;
			float vy=0;
			float a=0,b=0,c=0,d=0;
			for(int m=1;m<(account1.N)+1;m++)
			{
				vy+=mat.at<unsigned char>(account1.x,account1.y+m-1);
				a+=(m*mat.at<unsigned char>(account1.x,account1.y+m-1));
			}
			vy=vy*(1.0)/account1.N;
			b=((account1.N)*vx)*vy;
			c=((account1.N)*(account1.N+1)*((2*account1.N)+1))/6;
			d=account1.N*vx*vx;
			valuecol+=((b-a)/(c-d));
			time++;
		}
	}
	if(time == 0)
	{
		return 0 ;
	}  
	return valuecol/time;
}

float CImageProcess::GetImageValue3(Mat mat)
{

	float Isum;
	Isum=0;
	int rows = mat.rows;
	int cols = mat.cols;
	int sum  = rows*cols;
	float imagevalue=0;
	for(int i=1;i<mat.rows-1;i++)
	{
		for(int j=1;j<mat.cols-1;j++)
		{

			int v1=abs(mat.at<unsigned char>(i,j)-mat.at<unsigned char>(i,j-1));
			int v2=abs(mat.at<unsigned char>(i,j)-mat.at<unsigned char>(i+1,j));
			imagevalue+=(v1+v2);
		}

	}
	int numsize=(mat.cols)*(mat.rows);
	return  imagevalue/numsize;
}

float CImageProcess::GetImageValue4(Mat mat)
{

	float Isum=0;
	int Ixy;
	int rows = mat.rows;
	int cols = mat.cols;
	int sum  = rows*cols;
	for(int i=50;i<rows-52;i++)
	{
		for(int j=500;j<cols-502;j++)
		{
			Ixy= (-1)* mat.at<unsigned char>(i-1,j-1) + (-4)* mat.at<unsigned char>(i-1,j)+ (-1)* mat.at<unsigned char>(i-1,j+1)+
				(-4)* mat.at<unsigned char>(i,j-1)   +  20*  mat.at<unsigned char>(i,j)  + (-4)* mat.at<unsigned char>(i,j+1) +
				(-1)* mat.at<unsigned char>(i+1,j-1) + (-4)* mat.at<unsigned char>(i+1,j)+ (-1)* mat.at<unsigned char>(i+1,j+1);
			Isum+= (Ixy*Ixy);
		}
	}

	if ( 0 >= sum)
		return 0 ;
	return  (Isum/sum) ;
}

bool CImageProcess::ImageCutAndRotate(Mat inputimg,Mat &outputimg,float matchangle,float matchscale,vector<cirmatch> circlesmatch,int xpcbmin,int ypcbmin,int xpcbmax,int ypcbmax)
{
	int num=circlesmatch.size();
	Point2i rotateincam,rotateinfile;
	rotateincam.x=0;
	rotateincam.y=0;
	rotateinfile.x=0;
	rotateinfile.y=0;
	for(int i=0;i<num;i++)
	{
		rotateincam.x+=circlesmatch[i].circleincam.x;
		rotateincam.y+=circlesmatch[i].circleincam.y;
		rotateinfile.x+=circlesmatch[i].circleinfile.x;
		rotateinfile.y+=circlesmatch[i].circleinfile.y;
	}
	rotateincam.x=rotateincam.x/num;
	rotateincam.y=rotateincam.y/num;
	rotateinfile.x=rotateinfile.x/num;
	rotateinfile.y=rotateinfile.y/num;
	//两个图片的旋转对应点
	Point2i   location_temp;
	location_temp.x=rotateincam.x-inputimg.cols/2;
	location_temp.y=rotateincam.y-inputimg.rows/2;
	Point2i   location_temp2;//转为旋转后的坐标
	float sinx=sinf(matchangle*PI/180);
	float cosx=cosf(matchangle*PI/180);
	float m_temp=(float)inputimg.rows*(float)inputimg.rows+(float)inputimg.cols*(float)inputimg.cols;
	int XY_off=sqrt(m_temp)/2;
	location_temp2.x=(location_temp.x)*cosx+(location_temp.y)*sinx+XY_off;
	location_temp2.y=(location_temp.y)*cosx-(location_temp.x)*sinx+XY_off;
	Rect box;
	box.x=location_temp2.x-(int)((rotateinfile.x-xpcbmin)/matchscale);
	box.y=location_temp2.y-(int)((rotateinfile.y-ypcbmin)/matchscale);
	box.width=(xpcbmax-xpcbmin)/matchscale;
	box.height=(ypcbmax-ypcbmin)/matchscale;
	Mat rotate_result;
	ImageRotate(inputimg,rotate_result,matchangle);
	Mat cutimageresult(rotate_result,box);
	cutimageresult.copyTo(outputimg);
	return true;
}

bool CImageProcess:: ImageRotate(Mat mat,Mat &src,double angle)
{
	int length;//输出图像的宽度或高度  
	//为了保证无论如何旋转都能放下，输出图像的长和宽都设为输入图像对角线长度乘以SCALE  
	//但如果是缩小(SCALE<=1)，这样会导致临时图像中放不下原图，所以对于所有缩小的情况，输出图像和临时图像的长宽都设为原图的对角线长度  
	float temp = (mat.cols*mat.cols) + (mat.rows*mat.rows) ;
	length = sqrt(temp);  
	//建立临时图像，长宽都是源图像的对角线长度，将源图像复制到临时图像的中心后再变换  
	Mat tempImg=Mat::zeros(length,length,mat.type());//临时图像，大小和输出图像一样大  
	int ROI_x = length/2 - mat.cols/2;//ROI矩形左上角的x坐标  1
	int ROI_y = length/2 - mat.rows/2;//ROI矩形左上角的y坐标  
	Rect ROIRect(ROI_x,ROI_y,mat.cols,mat.rows);//ROI矩形  */
	Mat tempImgROI2(tempImg,ROIRect);//tempImg的中间部分  
	mat.copyTo(tempImgROI2);//将原图复制到tempImg的中心  
	Point2f center(length/2,length/2);//旋转中心  
	Mat M = getRotationMatrix2D(center,angle,1);//计算旋转的仿射变换矩阵
	warpAffine(tempImg,src,M,Size(length,length));

	return TRUE;
}

bool CImageProcess::ImageResize(Mat mat,Mat &src,double scale)
{
	Size dsize = Size(mat.cols*scale,mat.rows*scale);
	resize(mat,src,dsize);
	return TRUE;
}

bool CImageProcess::ImageSplit(Mat img,Mat src,Mat &resultimg)
{
	MAXarea=0;
	FastFeatureDetector detector(15);
	detector.detect(img, keypoints1);
	FastFeatureDetector detector2(15);
	detector2.detect(src, keypoints2);
	int xkpmax=0,xkpmin=src.cols;
	for (int m=0;m<keypoints1.size();m++)
	{
		if (keypoints1[m].pt.x>xkpmax)
		{
			xkpmax=keypoints1[m].pt.x;
		}
	}
	for (int n=0;n<keypoints2.size();n++)
	{
		if (keypoints2[n].pt.x<xkpmin)
		{
			xkpmin=keypoints2[n].pt.x;
		}
	}
	keypoints1.clear();
	keypoints2.clear();
	//-------------------------------
	float    M1[splitnum],M2[splitnum];
	int step=img.rows/splitnum;
	for(int i=0;i<splitnum;i++)
	{
		if(0==img.at<unsigned char>(i*step,xkpmax))
			M1[i]=img.at<unsigned char>(i*step,0);
		else
			M1[i]=img.at<unsigned char>(i*step,xkpmax)*(1.0)/img.at<unsigned char>(i*step,xkpmax-x_off);//比值匹配模版
	}
	double m_min=255*splitnum;
	int x_pipei=0;
	for (int m=0;m<src.cols-x_off;m++)
	{	
		double m_temp=0;
		for(int i=0;i<splitnum;i++)
		{
			if(0==src.at<unsigned char>(i*step,m))
				M2[i]=src.at<unsigned char>(i*step,m+x_off);
			else
				M2[i]=src.at<unsigned char>(i*step,x_off)*(1.0)/src.at<unsigned char>(i*step,m);
			m_temp+=abs(M2[i]-M1[i]);
		}
		//计算当前比值与原比值差
		if (m_temp<m_min)
		{
			m_min=m_temp;
			x_pipei=m;
		}
	}

	if (!x_pipei)
	{
		return false;
	}
	MAXarea=x_pipei+x_off+img.cols-xkpmax;
	resultimg=Mat::zeros(4000,4000-MAXarea,CV_8UC1);
	if (MAXarea>2000)
		return  false;
	for(int j=0;j<img.rows;j++)
	{
		int i;
		for(i=0;i<2000-MAXarea;i++)
		{
			resultimg.at<unsigned char>(j,i)=img.at<unsigned char>(j,i);
		}
		for(i=2000-MAXarea;i<2000;i++)
		{
			int t=(img.at<unsigned char>(j,i)+src.at<unsigned char>(j,i+MAXarea-2000))/2;
			resultimg.at<unsigned char>(j,i)=t;
		}
		for(i=2000;i<4000-MAXarea;i++)
		{
			resultimg.at<unsigned char>(j,i)=src.at<unsigned char>(j,i+MAXarea-2000);
		}
	}
	return true;
}

bool CImageProcess::ImageSplit2(Mat img,Mat src,Mat &resultimg)
{
	MAXarea=0;
	end_split.clear();
	GetHole(img);
	sort(circles.begin(), circles.end(),lessmarkX);
	int x_split=circles[0].x;
	int y_split=circles[0].y;
	int R_split=circles[0].R;
	GetHole(src);
	for(int i=0;i<circles.size();i++)
	{
		if(circles[i].y>y_split-10&&circles[i].y<y_split+10&&circles[i].R+20>R_split&&circles[i].R-20<R_split)
		{
			end_split.push_back(circles[i]);
		}
	}

	if (0==end_split.size())
	{
		return false;
	}
	unsigned int p_min=255*img.rows;
	unsigned int p_temp=0;
	int cols_now=0;
	for(int i=0;i<end_split.size();i++)
	{
		for (int m=-2;m<1;m++)
		{
			for (int j=0;j<img.rows;j++)
			{
				int M=img.at<unsigned char>(j,x_split)-src.at<unsigned char>(j,end_split[i].x+m);
				unsigned int M2=M*M;
				p_temp+=M;
			}
			if (p_temp<p_min)
			{
				p_min=p_temp;
				cols_now=end_split[i].x+m;
			}
		}
	}
	if (0==cols_now)
	{
		return false;
	}
	MAXarea=img.cols-x_split+cols_now;
	resultimg=Mat::zeros(4000,4000-MAXarea,CV_8UC1);
	if (MAXarea>2000)
		return  false;
	for(int j=0;j<img.rows;j++)
	{
		int i;
		for(i=0;i<2000-MAXarea;i++)
		{
			resultimg.at<unsigned char>(j,i)=img.at<unsigned char>(j,i);
		}
		for(i=2000-MAXarea;i<2000;i++)
		{
			int t=(img.at<unsigned char>(j,i)+src.at<unsigned char>(j,i+MAXarea-2000))/2;
			resultimg.at<unsigned char>(j,i)=t;
		}
		for(i=2000;i<4000-MAXarea;i++)
		{
			resultimg.at<unsigned char>(j,i)=src.at<unsigned char>(j,i+MAXarea-2000);
		}
	}

	return true;
}

bool CImageProcess::ImageSplit3(Mat img,Mat src,Mat &resultimg)
{

	MAXarea=0;
	FastFeatureDetector detector(15);
	detector.detect(img, keypoints1);
	int xkpmax=0,xkpmin=src.cols;
	Point2f img_point;
	for (int m=0;m<keypoints1.size();m++)
	{
		if (keypoints1[m].pt.x>xkpmax)
		{
			xkpmax=keypoints1[m].pt.x;
			img_point=keypoints1[m].pt;
		}
	}
	if (0==xkpmax)
		return false;
	int   M[3][3];
	for(int i=0;i<3;i++)
	{
		for (int j=0;j<3;j++)
		{
			if ((img_point.y+j-1)>img.rows||(img_point.y-1+j)<0||(img_point.x-1+i)>img.cols||(img_point.x-1+i)<0)
				return false;
			else
				M[i][j]=img.at<unsigned char>(img_point.y-1+j,img_point.x-1+i);
		}
	}
	//模版完成  
	int m_value=255*9;
	int m_temp=0;
	int cols_now=-1;
	for (int i=0;i<src.cols-3;i++)
	{		
		m_temp=abs(src.at<unsigned char>(img_point.y-1,i)-M[0][0])+abs(src.at<unsigned char>(img_point.y-1,i+1)-M[0][1])+abs(src.at<unsigned char>(img_point.y-1,i+2)-M[0][2])
			+abs(src.at<unsigned char>(img_point.y,i)-M[1][0])+  abs(src.at<unsigned char>(img_point.y,i+1)-M[1][1])+  abs(src.at<unsigned char>(img_point.y,i+2)-M[1][2])
			+abs(src.at<unsigned char>(img_point.y+1,i)-M[2][0])+abs(src.at<unsigned char>(img_point.y+1,i+1)-M[2][1])+abs(src.at<unsigned char>(img_point.y+1,i+2)-M[2][2]);
		if (m_temp<m_value)
		{
			m_value=m_temp;
			cols_now=i;
		}
	}
	if (-1==cols_now)
	{
		return false;
	}
	MAXarea=img.cols-xkpmax+cols_now+1;
	if (MAXarea>2000)
		return  false;
	resultimg=Mat::zeros(4000,4000-MAXarea,CV_8UC1);
	for(int j=0;j<img.rows;j++)
	{
		int i;
		for(i=0;i<2000-MAXarea;i++)
		{
			resultimg.at<unsigned char>(j,i)=img.at<unsigned char>(j,i);
		}
		for(i=2000-MAXarea;i<2000;i++)
		{
			int t=(img.at<unsigned char>(j,i)+src.at<unsigned char>(j,i+MAXarea-2000))/2;
			resultimg.at<unsigned char>(j,i)=t;
		}
		for(i=2000;i<4000-MAXarea;i++)
		{
			resultimg.at<unsigned char>(j,i)=src.at<unsigned char>(j,i+MAXarea-2000);
		}
	}
	return true;
}

bool CImageProcess::ImageSplit4(Mat img,Mat src,Mat &resultimg)
{
	MAXarea=0;
	SurfFeatureDetector detector;
	detector.detect(img, keypoints1);
	detector.detect(src, keypoints2);
	SurfFeatureDetector extractor;
	Mat descriptor1,descriptor2;
	matcher.clear();
	Mat img_matches;
	extractor.compute(img,keypoints1,descriptor1);
	extractor.compute(src,keypoints2,descriptor2);
	matcher.match(descriptor1,descriptor2,matches);
	drawMatches(img,keypoints1,src,keypoints2,matches,img_matches);
	return true;
}

bool CImageProcess::ImageSplit5(Mat img,Mat src,Mat &resultimg)
{
	MAXarea=0;
	end_split.clear();
	GetHole(img);
	sort(circles.begin(), circles.end(),lessmarkX);
	int xkpmax=circles[0].x;
	int m_temp=0;
	int m_value=src.rows;
	int cols_now=-1;
	for (int i=0;i<src.cols;i++)
	{	
		for (int j=0;j<img.rows;j++)
		{
			int M=img.at<unsigned char>(j,xkpmax)-src.at<unsigned char>(j,i);
			m_temp+=abs(M);
		}
		if (m_temp<m_value)
		{
			m_value=m_temp;
			cols_now=i;
		}
	}
	MAXarea=img.cols-xkpmax+cols_now;
	if (MAXarea>2000)
		return  false;
	resultimg=Mat::zeros(4000,4000-MAXarea,CV_8UC1);
	for(int j=0;j<img.rows;j++)
	{
		int i;
		for(i=0;i<2000-MAXarea;i++)
		{
			resultimg.at<unsigned char>(j,i)=img.at<unsigned char>(j,i);
		}
		for(i=2000-MAXarea;i<2000;i++)
		{
			int t=(img.at<unsigned char>(j,i)+src.at<unsigned char>(j,i+MAXarea-2000))/2;
			resultimg.at<unsigned char>(j,i)=t;
		}
		for(i=2000;i<4000-MAXarea;i++)
		{
			resultimg.at<unsigned char>(j,i)=src.at<unsigned char>(j,i+MAXarea-2000);
		}
	}
	return true;
}

bool CImageProcess:: FourPiontPosition(	vector<circlestruct>  locationincam,vector<circlestruct> locationinfile ,float &matchangle,float &matchscale)
{
	double temp_y = (double)locationinfile[0].y-(double)locationinfile[1].y ;
	double temp_x = (double)locationinfile[0].x-(double)locationinfile[1].x ;
	double file = sqrt( temp_y*temp_y + temp_x*temp_x );

	double temp_y2 = (double)locationinfile[0].y-(double)locationinfile[2].y ;
	double temp_x2 = (double)locationinfile[0].x-(double)locationinfile[2].x ;
	double file2 = sqrt( temp_y2*temp_y2 + temp_x2*temp_x2 );

	double temp_y3 = (double)locationinfile[0].y-(double)locationinfile[3].y ;
	double temp_x3 = (double)locationinfile[0].x-(double)locationinfile[3].x ;
	double file3 = sqrt( temp_y3*temp_y3 + temp_x3*temp_x3 );

	double temp_y4 = (double)locationinfile[1].y-(double)locationinfile[2].y ;
	double temp_x4 = (double)locationinfile[1].x-(double)locationinfile[2].x ;
	double file4 = sqrt( temp_y4*temp_y4 + temp_x4*temp_x4 );

	double temp_y5 = (double)locationinfile[1].y-(double)locationinfile[3].y ;
	double temp_x5 = (double)locationinfile[1].x-(double)locationinfile[3].x ;
	double file5 = sqrt( temp_y5*temp_y5 + temp_x5*temp_x5 );

	double temp_y6 = (double)locationinfile[2].y-(double)locationinfile[3].y ;
	double temp_x6 = (double)locationinfile[2].x-(double)locationinfile[3].x ;
	double file6 = sqrt( temp_y6*temp_y6 + temp_x6*temp_x6 );


	double camoff= ((double)locationincam[0].y-(double)locationincam[1].y) * ((double)locationincam[0].y-(double)locationincam[1].y)+  ((double)locationincam[0].x-(double)locationincam[1].x)*  ((double)locationincam[0].x-(double)locationincam[1].x);
	double cam=sqrt(camoff)*56;

	double camoff2= ((double)locationincam[0].y-(double)locationincam[2].y) * ((double)locationincam[0].y-(double)locationincam[2].y)+  ((double)locationincam[0].x-(double)locationincam[2].x)*  ((double)locationincam[0].x-(double)locationincam[2].x);
	double cam2=sqrt(camoff2)*56;

	double camoff3= ((double)locationincam[0].y-(double)locationincam[3].y) * ((double)locationincam[0].y-(double)locationincam[3].y)+  ((double)locationincam[0].x-(double)locationincam[3].x)*  ((double)locationincam[0].x-(double)locationincam[3].x);
	double cam3=sqrt(camoff3)*56;

	double camoff4= ((double)locationincam[1].y-(double)locationincam[2].y) * ((double)locationincam[1].y-(double)locationincam[2].y)+  ((double)locationincam[1].x-(double)locationincam[2].x)*  ((double)locationincam[1].x-(double)locationincam[2].x);
	double cam4=sqrt(camoff4)*56;

	double camoff5= ((double)locationincam[1].y-(double)locationincam[3].y) * ((double)locationincam[1].y-(double)locationincam[3].y)+  ((double)locationincam[1].x-(double)locationincam[3].x)*  ((double)locationincam[1].x-(double)locationincam[3].x);
	double cam5=sqrt(camoff5)*56;

	double camoff6= ((double)locationincam[2].y-(double)locationincam[3].y) * ((double)locationincam[2].y-(double)locationincam[3].y)+  ((double)locationincam[2].x-(double)locationincam[3].x)*  ((double)locationincam[2].x-(double)locationincam[3].x);
	double cam6=sqrt(camoff6)*56;

	float angle_f1,angle_c1,angle_f2,angle_c2,angle_f3,angle_c3,angle_f4,angle_c4,angle_f5,angle_c5,angle_f6,angle_c6;

	angle_f1=(atan2f(locationinfile[0].y-locationinfile[1].y,locationinfile[0].x-locationinfile[1].x))*180/PI;

	angle_c1=(atan2f((locationincam[0].y-locationincam[1].y),(locationincam[0].x-locationincam[1].x)))*180/PI;

	angle_f2=(atan2f((locationinfile[0].y-locationinfile[2].y),(locationinfile[0].x-locationinfile[2].x)))*180/PI;

	angle_c2=(atan2f((locationincam[0].y-locationincam[2].y),(locationincam[0].x-locationincam[2].x)))*180/PI;

	angle_f3=(atan2f((locationinfile[0].y-locationinfile[3].y),(locationinfile[0].x-locationinfile[3].x)))*180/PI;

	angle_c3=(atan2f((locationincam[0].y-locationincam[3].y),(locationincam[0].x-locationincam[3].x)))*180/PI;

	angle_f4=(atan2f((locationinfile[1].y-locationinfile[2].y),(locationinfile[1].x-locationinfile[2].x)))*180/PI;

	angle_c4=(atan2f((locationincam[1].y-locationincam[2].y),(locationincam[1].x-locationincam[2].x)))*180/PI;

	angle_f5=(atan2f((locationinfile[1].y-locationinfile[3].y),(locationinfile[1].x-locationinfile[3].x)))*180/PI;

	angle_c5=(atan2f((locationincam[1].y-locationincam[3].y),(locationincam[1].x-locationincam[3].x)))*180/PI;

	angle_f6=(atan2f((locationinfile[2].y-locationinfile[3].y),(locationinfile[2].x-locationinfile[3].x)))*180/PI;

	angle_c6=(atan2f((locationincam[2].y-locationincam[3].y),(locationincam[2].x-locationincam[3].x)))*180/PI;
	float matchscale_temp=(file/cam+file2/cam2+file3/cam3+file4/cam4+file5/cam5+file6/cam6)/6;
	float matchangle_temp=(angle_c1-angle_f1+angle_c2-angle_f2+angle_c3-angle_f3+angle_c4-angle_f4+angle_c5-angle_f5+angle_c6-angle_f6)/6;
	matchscale=matchscale_temp;//(((int)matchscale_temp*100)*1.0)/100;
	matchangle=matchangle_temp;//(((int)matchangle_temp*100)*1.0)/100;
	return true;
}

bool CImageProcess:: HighQualityLocation(vector<cirmatch> circlesmatch,float &matchangle,float &matchscale)
{
	int num=circlesmatch.size();
	float sum_matchscale=0,sum_matchangle=0,temp_ang=0,temp_sca=0;
	int sum=0;
	if (num<5)
	{
		return false;
	}
	int num1=0;
	while(num1<num)
	{
		int num2=num1+1;
		while(num2<num)
		{
			int num3=num2+1;
			while (num3<num)
			{
				int num4=num3+1;
				while(num4<num)
				{

					locationincam_temp.clear();
					locationinfile_temp.clear();
					circlestruct temp_cam,temp_file;
					temp_cam=circlesmatch[num1].circleincam;
					locationincam_temp.push_back(temp_cam);
					temp_cam=circlesmatch[num2].circleincam;
					locationincam_temp.push_back(temp_cam);
					temp_cam=circlesmatch[num3].circleincam;
					locationincam_temp.push_back(temp_cam);
					temp_cam=circlesmatch[num4].circleincam;
					locationincam_temp.push_back(temp_cam);
					temp_file=circlesmatch[num1].circleinfile;
					locationinfile_temp.push_back(temp_file);
					temp_file=circlesmatch[num2].circleinfile;
					locationinfile_temp.push_back(temp_file);
					temp_file=circlesmatch[num3].circleinfile;
					locationinfile_temp.push_back(temp_file);
					temp_file=circlesmatch[num4].circleinfile;
					locationinfile_temp.push_back(temp_file);
					if (true==FourPiontPosition(locationincam_temp,locationinfile_temp,temp_ang,temp_sca))
					{	
						if ((temp_ang>-1)&&(temp_ang<1)&&(temp_sca>matchscale-1)&&(temp_sca<matchscale+1))
						{	
							sum++;	
							sum_matchangle+=temp_ang;
							sum_matchscale+=temp_sca;	
						}	
					}


					num4++;
				}
				num3++;
			}
			num2++;
		}
		num1++;
	}
	matchangle=sum_matchangle/sum;
	matchscale=sum_matchscale/sum;
	return true;
}

bool CImageProcess:: HighQualityLocation2(vector<cirmatch> circlesmatch,float &matchangle,float &matchscale)
{
	int num=circlesmatch.size();
	float sum_matchscale=0,sum_matchangle=0,temp_ang=0,temp_sca=0;
	int sum=0;

	for (int i=0;i<num-1;i++)
	{
		for (int j=i+1;j<num;j++)
		{
			double camoff= ((double)circlesmatch[i].circleincam.y-(double)circlesmatch[j].circleincam.y) * ((double)circlesmatch[i].circleincam.y-(double)circlesmatch[j].circleincam.y)+  ((double)circlesmatch[i].circleincam.x-(double)circlesmatch[j].circleincam.x)* ((double)circlesmatch[i].circleincam.x-(double)circlesmatch[j].circleincam.x);
			double cam=sqrt(camoff);
			double temp_y = (double)circlesmatch[i].circleinfile.y-(double)circlesmatch[j].circleinfile.y ;
			double temp_x = (double)circlesmatch[i].circleinfile.x-(double)circlesmatch[j].circleinfile.x;
			double file = sqrt( temp_y*temp_y + temp_x*temp_x );

			float angle_f1=(atan2f(circlesmatch[i].circleinfile.y-circlesmatch[j].circleinfile.y,circlesmatch[i].circleinfile.x-circlesmatch[j].circleinfile.x))*180/PI;
			float angle_c1=(atan2f((circlesmatch[i].circleincam.y-circlesmatch[j].circleincam.y),(circlesmatch[i].circleincam.x-circlesmatch[i].circleincam.x)))*180/PI;
			temp_ang=angle_c1-angle_f1;
			temp_sca=file/cam;
			if ((temp_ang>-1)&&(temp_ang<1)&&(temp_sca>matchscale-1)&&(temp_sca<matchscale+1))
			{	
				sum++;
				sum_matchscale+=temp_sca;
				sum_matchangle+=temp_ang;
			}

		}
	}
	matchangle=sum_matchangle/sum;
	matchscale=sum_matchscale/sum;
	return true;
}

bool CImageProcess:: HighQualityLocation3(vector<cirmatch> circlesmatch,float &matchangle,float &matchscale)
{
	int num=circlesmatch.size();
	float sum_matchscale=0,sum_matchangle=0,temp_ang=0,temp_sca=0;
	int sum=0;

	Point2f temp_infile,temp_incam;
	for (int i=0;i<num;i++)
	{
		temp_infile.x=circlesmatch[i].circleinfile.x;
		temp_infile.y=circlesmatch[i].circleinfile.y;
		temp_incam.x=circlesmatch[i].circleincam.x;
		temp_incam.y=circlesmatch[i].circleincam.y;
		infile.push_back(temp_infile);
		incam.push_back(temp_incam);
	}
	Mat outputA;
	Mat fundamental_matrix=findFundamentalMat(infile,incam,FM_RANSAC,3,0.99,outputA);//求得基础矩阵
	int a[100];
	for (int i=0;i<num;i++)
	{
		a[i]=outputA.at<unsigned char>(i,0);
	}
	Mat m_homography;

	m_homography=findHomography(infile,incam,CV_RANSAC,3,m);//返回值为变换矩阵
	vector<cirmatch>::iterator itr = circlesmatch.begin();

	int n_temp=0;
	for (int i=0;i<num;i++)
	{
		if (a[i]==0)
		{
			vector<cirmatch>::iterator itr = circlesmatch.begin();
			int off=i-n_temp;
			circlesmatch.erase(itr+off);
			n_temp++; 
		}
	}

	HighQualityLocation(circlesmatch,matchangle,matchscale);
	incam.clear();
	infile.clear();
	m.clear();
	return true;
}
