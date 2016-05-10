#include "stdafx.h"
#include "AOID.h"
#include "ImageAnalysis.h"
#include <iostream> 

// CImageAnalysis

IMPLEMENT_DYNCREATE(CImageAnalysis, CFormView)

CImageAnalysis::CImageAnalysis()
	: CFormView(CImageAnalysis::IDD)
{
}

CImageAnalysis::~CImageAnalysis()
{
}

void CImageAnalysis::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Show, m_Show);
}

BEGIN_MESSAGE_MAP(CImageAnalysis, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CImageAnalysis::OnBnClickedback)
	ON_BN_CLICKED(IDC_BUTTON3, &CImageAnalysis::OnBnClickedsaltshow)
	ON_BN_CLICKED(IDC_Hough, &CImageAnalysis::OnBnClickedHough)
END_MESSAGE_MAP()


// CImageAnalysis 诊断

#ifdef _DEBUG
void CImageAnalysis::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CImageAnalysis::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CImageAnalysis 消息处理程序


void CImageAnalysis::OnBnClickedback()
{

	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	pwnd->m_pOpPaneWnd->SwitchToView(VIEW_F3SUBITEM1);
	
}
void CImageAnalysis::salt(Mat image, int n)
{
	for(int k=0; k<n; k++)
	{	
		int j = rand()%image.rows;
		int i = rand()%image.cols;
	

		if(image.channels() == 1)
		{
			image.at<uchar>(j,i) = 255;
	    }
		else
		{
			image.at<cv::Vec3b>(j,i)[0] = 255;
			image.at<cv::Vec3b>(j,i)[1] = 255;
			image.at<cv::Vec3b>(j,i)[2] = 255;
		}
    }
};

void CImageAnalysis::OnBnClickedsaltshow()
{
	Mat image;
	image= imread("F:\\Lena.bmp",1);
	salt(image, 10000);
	namedWindow("image");
	imshow("image",image);
	waitKey(0);
}

void
	 CImageAnalysis::Histogram()
{
	Mat mat = imread( "F:\\4点定位剪切图.bmp",CV_LOAD_IMAGE_ANYDEPTH|CV_LOAD_IMAGE_ANYCOLOR );
	Mat src,src1,src2;
	Mat hist;
	int histSize = 255;
	float range[] = { 0, 255 } ;
	const float* histRange = { range };
	bool uniform = true; 
	bool accumulate = false;
	calcHist( &src1, 1, 0, Mat(), hist, 1, &histSize, &histRange, uniform, accumulate );
	int hist_w = 400; int hist_h = 400;
	int bin_w = cvRound( (double) hist_w/histSize );

	Mat histImage( hist_w, hist_h, CV_8UC3, Scalar( 255,255,255) );
	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
	for( int i = 1; i < histSize; i++ )
	{
		line( histImage, Point( bin_w*(i-1), hist_h - cvRound(hist.at<float>(i-1)) ) ,
			Point( bin_w*(i), hist_h - cvRound(hist.at<float>(i)) ),
			Scalar( 0, 0, 255), 2, 8, 0  );
	}
	namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE );
	imshow("calcHist Demo", histImage );
}

void CImageAnalysis::OnBnClickedHough()
{
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	GetDlgItem(IDC_Show);
	Mat mat = imread( "F:\\4点定位剪切图.bmp",CV_LOAD_IMAGE_ANYDEPTH|CV_LOAD_IMAGE_ANYCOLOR );
	Mat src,src1,src2;
	
	mat.copyTo(src);
	medianBlur(src,src1,5);//中值滤波
	int threshold1=100;

	Mat hist;
	int histSize = 255;
	float range[] = { 0, 255 } ;
	const float* histRange = { range };
	bool uniform = true; 
	bool accumulate = false;
	calcHist( &src1, 1, 0, Mat(), hist, 1, &histSize, &histRange, uniform, accumulate );
	int hist_w = 400; int hist_h = 400;
	int bin_w = cvRound( (double) 3*hist_w/histSize );

	Mat histImage( hist_w, hist_h, CV_8UC3, Scalar( 255,255,255) );
	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );


	for( int i = 1; i < 255; i++ )
	{
		line( histImage, Point( bin_w*(i-1), hist_h - cvRound(hist.at<float>(i-1)) ) ,
			Point( bin_w*(i), hist_h - cvRound(hist.at<float>(i)) ),
			Scalar( 0, 0, 0), 2, 8, 0  );
		/*line( histImage, Point( bin_w*(i), hist_h - cvRound(hist.at<float>(i)) ) ,
			Point( bin_w*(i), hist_h  ),
			Scalar( 0, 0, 0), 2, 8, 0  );*/
	}
	
	namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE );
	imshow("calcHist Demo", histImage );
	imwrite("hist.bmp",histImage);
	//Histogram();

	//m_Show.ShowImage(hist,0);
	//threshold(src1,src1,threshold1,255,THRESH_BINARY);//二值图的生成；
	//vector<vector<Point> > contours;
	//vector<Vec3f> circles;
	//findContours(src2,contours,CV_RETR_LIST,CV_CHAIN_APPROX_NONE);

	// Apply the Hough Transform to find the circles
	/*HoughCircles( src,circles, CV_HOUGH_GRADIENT, 1, 1, 200, 10, 2,1000);
	for( size_t i = 0; i < circles.size(); i++ )
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		// circle center
		circle( src, center, 3, Scalar(0,255,0), -1, 8, 0 );
		// circle outline
		circle( src, center, radius, Scalar(0,0,255), 3, 8, 0 );
	}*/
	/*pwnd->m_imageprocess.ImageRotate(src1,src2,1.5);
	Mat src3=Mat::zeros(src2.rows,src2.cols,src2.type());//src2.cols+10
	Mat dst=Mat::zeros(src2.rows,src2.cols,src2.type());
	int src2_half_rows=src2.rows/2;
	int src1_half_rows=src1.rows/2;
	int i,j,k;
	uchar *p,*q;
	MatIterator_<uchar> begin1,begin2;
	begin1=src1.begin<uchar>();
	begin2=src2.begin<uchar>();

	for(i=src2_half_rows-src1_half_rows;i!=src2_half_rows+src1_half_rows;++i)
	{
		p=src3.ptr<uchar>(i);

		for(j=0;j!=src1.cols;++j)
		{
			p[j]=*begin1;
			++begin1;
		}
	}
	int dx=825,dy=5;//dst中只装载src1  小于（828，0）则向原点移动
	for (int i = 0; i < dst.rows; i++)
	{
		p = dst.ptr<uchar>(i);
		for (int j = 0; j < dst.cols; j++)
		{
			//平移后坐标映射到原图像
			int x = j - dx;
			int y = i - dy;

			//保证映射后的坐标在原图像范围内
			if (x >= 0 && y >= 0 && x <src3. cols && y < src3.rows)
				p[j] = src3.ptr<uchar>(y)[x];
		}
	}

	for(i=0;i!=src2.rows;++i)
	{
		q=dst.ptr<uchar>(i);
		for(j=0;j!=src2.cols;++j)//src2.cols+10
		{
			k=q[j]/2+*begin2/2;
			
			q[j]=k;
			
			++begin2;
		}
	}
	//m_Show.ShowImage(src2,0);
	//m_Show.ShowImage(dst,0);
	//imwrite("F:\\result1.bmp",dst);
	threshold(dst,dst,threshold1,255,THRESH_BINARY);//二值图的生成；
	vector<vector<Point> > contours;
	findContours(dst,contours,CV_RETR_LIST,CV_CHAIN_APPROX_NONE);
	//system("pause");
	/// 绘出轮廓
	Mat gray ;
	cvtColor(dst,gray , CV_GRAY2BGR); 
	for( int i = 0; i<contours.size(); i++ )
	{
		drawContours( gray, contours, i, Scalar(255,0,0), 2, 8, contours[0], 0, Point() );
	}
	

	m_Show.ShowImage(hist,0);*/

}


void CImageAnalysis::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	m_Show.OnInit();
}
