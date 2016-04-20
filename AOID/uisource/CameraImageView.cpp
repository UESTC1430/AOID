// CameraImageView.cpp : ʵ���ļ�
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
	DDX_Control(pDX, IDC_CAMIMG, m_camimg);
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


// CCameraImageView ���

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


// CCameraImageView ��Ϣ�������


void CCameraImageView::InputImage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CCameraImageView::OnGetPiont()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CCameraImageView::CameraimageShow()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	DrawcvMat(pwnd->m_camera.img_sweep,IDC_CAMIMG,1);
	imwrite("G:/ɨ��ͼ.bmp",pwnd->m_camera.img_sweep);
}


void CCameraImageView::OnCutImage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CCameraImageView::OnBnClickedFocus()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CCameraImageView::OnBnClickedtest()
{
	// ��ת��������
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	pwnd->m_camera.img_sweep=imread("G:/�ɼ�ʵͼ.bmp",CV_LOAD_IMAGE_ANYDEPTH|CV_LOAD_IMAGE_ANYCOLOR);
	//DrawcvMat(	pwnd->m_camera.img_sweep,IDC_CAMIMG,1);
	m_camimg.ShowImage(pwnd->m_camera.img_sweep,1);
}

void CCameraImageView::DrawcvMat(Mat mat, UINT ID,bool flag)//��ʾmat��picture�ؼ���
{
	Mat img;
	CRect rect;
	CDC* pDC=GetDlgItem(ID)->GetDC();
	HDC hDC=pDC->GetSafeHdc();
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
	IplImage* drawing_ipl = &IplImage(img);
	CvvImage Cvvimg;
	Cvvimg.CopyOf(drawing_ipl);
	// ��ͼƬ���Ƶ���ʾ�ؼ���ָ��������
	Cvvimg.DrawToHDC(hDC, &rect );
	ReleaseDC(pDC);	

}


void CCameraImageView::OnBnClickedHough()
{
	
	Mat mat = imread( "F:\\result.bmp",CV_LOAD_IMAGE_ANYDEPTH|CV_LOAD_IMAGE_ANYCOLOR );
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	//pwnd->m_imageprocess.HoughGetHole(mat);

	DrawcvMat(mat,IDC_CAMIMG,1);
}