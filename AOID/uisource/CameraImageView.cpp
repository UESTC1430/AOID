// CameraImageView.cpp : 实现文件
//

#include "stdafx.h"
#include "AOID.h"
#include "CameraImageView.h"


// CCameraImageView

IMPLEMENT_DYNCREATE(CCameraImageView, CFormView)

CCameraImageView::CCameraImageView()
	: CFormView(CCameraImageView::IDD)
{

}

CCameraImageView::~CCameraImageView()
{
}

void CCameraImageView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCameraImageView, CFormView)
	ON_BN_CLICKED(IDC_INPUT, &CCameraImageView::InputImage)
	ON_BN_CLICKED(IDC_GETPIONT, &CCameraImageView::OnGetPiont)
	ON_BN_CLICKED(IDC_CAMERAIMAGE, &CCameraImageView::CameraimageShow)
	ON_BN_CLICKED(IDC_CUTIMAGE, &CCameraImageView::OnCutImage)
	ON_BN_CLICKED(IDC_BUTTON1, &CCameraImageView::OnBnClickedFocus)
	ON_BN_CLICKED(IDC_BUTTON2, &CCameraImageView::OnBnClickedtest)
	ON_BN_CLICKED(IDC_BUTTON3, &CCameraImageView::OnBnClickedHough)
END_MESSAGE_MAP()


// CCameraImageView 诊断

#ifdef _DEBUG
void CCameraImageView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCameraImageView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCameraImageView 消息处理程序


void CCameraImageView::InputImage()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CCameraImageView::OnGetPiont()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CCameraImageView::CameraimageShow()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CCameraImageView::OnCutImage()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CCameraImageView::OnBnClickedFocus()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CCameraImageView::OnBnClickedtest()
{
	// 跳转到测试用
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	pwnd->m_pOpPaneWnd->SwitchToView(VIEW_TESTITEM);
}

void CCameraImageView::DrawcvMat(Mat mat, UINT ID,bool flag)//显示mat在picture控件中
{
	Mat img;
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	double scale1=(rect.Width()*1.0)/mat.cols;
	double scale2=(rect.Height()*1.0)/mat.rows;
	Size dsize;
	if(scale1>scale2)
		camscale=scale2;
	else
		camscale=scale1;
	dsize = Size(mat.cols*camscale,mat.rows*camscale);
	resize(mat,img,dsize);
	int width,height,depth,channel;
	width=img.cols;
	height=img.rows;
	depth=img.depth();
	channel=img.channels();
	int bits,colors,i;
	bits=(8<<(depth/2))*channel;
	if (bits>8)
	{
		colors=0;
	} 
	else
	{
		colors=1<<bits;
	}
	if (bits==24)
	{
		bits=32;
	}
	BITMAPINFOHEADER BIH={40,0,0,1,8,BI_RGB,0,0,0,0,0};
	BIH.biWidth=width;
	BIH.biHeight=height;
	BIH.biBitCount=bits;
	LPBITMAPINFO lpBmi;
	lpBmi=(LPBITMAPINFO)malloc(40+4*colors);
	memcpy(lpBmi,&BIH,40);
	RGBQUAD VgaColorTab[256];
	if (bits==8)
	{
		if (flag==1)
		{
			for (i=0;i<256;i++)
			{
				VgaColorTab[i].rgbRed=VgaColorTab[i].rgbGreen=VgaColorTab[i].rgbBlue=(BYTE)i;
			}
			memcpy(lpBmi->bmiColors,VgaColorTab,1024);
		}
		else
		{
			memcpy(lpBmi->bmiColors,VgaColorTab,1024);
		}
	}

	unsigned char *m_pDibBits;
	int x,y;
	unsigned char *bmpdata;
	unsigned char *imgData=img.data;
	if (bits==8)
	{
		m_pDibBits=new unsigned char[width * height];
		for (x=0;x<height;x++)
		{
			bmpdata=m_pDibBits+(height-1-x)*width;
			memcpy(bmpdata,imgData,width);
			imgData=imgData+width;

		}

	}
	else
	{
		if (bits==32)
		{
			m_pDibBits=new unsigned char[width*height*4];
			for (x=0;x<height;x++)
			{
				bmpdata=m_pDibBits+(height-1-x)*width*4;
				for (y=0;y<width;y++)
				{
					memcpy(bmpdata,imgData,3);
					bmpdata[3]=255;
					bmpdata=bmpdata+4;
					imgData=imgData+3;
				}

			}
		}
	}
	CDC *pDC = GetDlgItem(ID)->GetDC();	
	SetStretchBltMode(pDC->GetSafeHdc(),HALFTONE);
	StretchDIBits(pDC->GetSafeHdc(),0,0,width,height,0,0,width,height,m_pDibBits,lpBmi,BI_RGB,SRCCOPY);

}


void CCameraImageView::OnBnClickedHough()
{
	
	Mat mat = imread( "F:\\result.bmp",CV_LOAD_IMAGE_ANYDEPTH|CV_LOAD_IMAGE_ANYCOLOR );
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	//pwnd->m_imageprocess.HoughGetHole(mat);

	DrawcvMat(mat,IDC_CAMIMG,1);
}