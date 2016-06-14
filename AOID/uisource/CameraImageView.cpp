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

void CCameraImageView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_camimg.OnInit();
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
	//ON_WM_MOUSEMOVE()
	//ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_BN_CLICKED(IDC_gettestimage, &CCameraImageView::OnBnClickedgettestimage)
	ON_BN_CLICKED(IDC_Camera, &CCameraImageView::OnBnClickedCamera)
	ON_BN_CLICKED(IDC_Houghline, &CCameraImageView::OnBnClickedHoughline)
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
	// TODO: Add your control notification handler code here
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	CWnd *pWin = GetDlgItem(IDC_MASTINIMAGE);
	pWin->GetClientRect(rectfile);
	m_rectfile = pWin->GetDC();
	int width=rectfile.Width();
	int height=rectfile.Height();
	CBrush myBrush;
	myBrush.CreateSolidBrush(RGB(250,0,0));
	if (theApp.mastprog.m_OriPosition==NULL)
	{
		MessageBox(NULL,_T("δ�����ļ�"),MB_OK);
		return ;
	}
	HoleInfoNode *curr=theApp.mastprog.m_OriPosition->pnext;
	//---------------------------------------------------------------zns
	xpcbmax=0;
	ypcbmax=0;
	float diameter=0;
	while(curr!=NULL)
	{
		if ((curr->position.nXs)<0)
			curr->position.nXs=-(curr->position.nXs);
		if ((curr->position.nYs)<0)
			curr->position.nYs=-(curr->position.nYs);
		if ((curr->position.nXs)>xpcbmax)
		{
			xpcbmax=curr->position.nXs;
		}
		if ((curr->position.nYs)>ypcbmax)
		{
			ypcbmax=curr->position.nYs;
		}
		if ((curr->position.diameter)>diameter)
		{
			diameter=curr->position.diameter;
		}
		curr=curr->pnext;
	}
	//-----------------------------------------------
	 xpcbmin=xpcbmax;
	 ypcbmin=ypcbmax;
	HoleInfoNode *curr2=theApp.mastprog.m_OriPosition->pnext;
	while(curr2!=NULL)
	{
		if ((curr2->position.nXs)<xpcbmin)
		{
			xpcbmin=curr2->position.nXs;
		}
		if ((curr2->position.nYs)<ypcbmin)
		{
			ypcbmin=curr2->position.nYs;
		}
		curr2=curr2->pnext;
	}

	float xscale=1,yscale=1;
	xpcbmax+=diameter;
	ypcbmax+=diameter;
	//xpcbmin=((xpcbmin-diameter)>0)?(xpcbmin-diameter):0;
	//ypcbmin=((ypcbmin-diameter)>0)?(ypcbmin-diameter):0;
	xpcbmin=xpcbmin-diameter;
	ypcbmin=ypcbmin-diameter;
	xscale=(width*1.0)/(xpcbmax-xpcbmin);
	yscale=(height*1.0)/(ypcbmax-ypcbmin);
	if (xscale>yscale)
	{
		filescale=yscale;
	}
	else
	{
		filescale=xscale;
	}
	m_rectfile->RoundRect(rectfile.left,rectfile.top,(rectfile.left)+(xpcbmax-xpcbmin)*filescale,(rectfile.top)+(ypcbmax-ypcbmin)*filescale,0,0);
	//------------------------------------------------------------------
	HoleInfoNode *curr3=theApp.mastprog.m_OriPosition->pnext;
	int num1=0;
	Xlu=xpcbmin;
	Ylu=ypcbmin;
	start_filescale=filescale;
	Xrd=Xlu+width/filescale;
	Yrd=Ylu+height/filescale;
	while(curr3!=NULL)
	{
		int r=(curr3->position.diameter)/2;
		int x1=(curr3->position.nXs-r-xpcbmin)*filescale;
		int x2=(curr3->position.nXs+r-xpcbmin)*filescale;
		int y1=(curr3->position.nYs-r-ypcbmin)*filescale;
		int y2=(curr3->position.nYs+r-ypcbmin)*filescale;
		m_rectfile->Ellipse(x1,y1,x2,y2);
		num1++;
		curr3=curr3->pnext;
	}
	/*CImage imag;
	imag.Create( (xpcbmax-xpcbmin)*filescale,(ypcbmax-ypcbmin)*filescale,32);
	CClientDC m_rectrader(pWin);
	::BitBlt(imag.GetDC(), 0,0,(xpcbmax-xpcbmin)*filescale,(ypcbmax-ypcbmin)*filescale, m_rectrader.m_hDC,0,0,SRCCOPY );
	imag.Save("G:/�ӹ�ͼ.bmp");
	ReleaseDC( &m_rectrader);
	imag.ReleaseDC();*/
	//----------------------------------------------
}


void CCameraImageView::OnGetPiont()
 {
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	pwnd->m_imageprocess.GetHole(pwnd->m_imageprocess.resultimage);
	if (0==pwnd->m_imageprocess.circles.size())
	{
		pwnd->m_pProgPaneWnd->m_pProgressView->WarnMessage("��ͼƬ��δ�ҵ�Բ",red);

	}
	if (theApp.mastprog.m_OriPosition==NULL)
	{
		pwnd->m_pProgPaneWnd->m_pProgressView->WarnMessage("�ӹ��ļ�δ����",red);
		return ;
	}
	locationinfile.clear();
	locationincam.clear();
	pwnd->m_pProgPaneWnd->m_pProgressView->WarnMessage("�����ļ�����ͼ��ѡ��4����λ��",green);
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
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
  	if (locationinfile.size()==4&&locationincam.size()==4)
	{
		pwnd->m_pProgPaneWnd->m_pProgressView->WarnMessage("��λ��ѡ�����",white);
	}
	else
	{
		pwnd->m_pProgPaneWnd->m_pProgressView->WarnMessage("��λ��ѡ��������",red);
		return;
	}
	
    pwnd->m_imageprocess.FourPiontPosition(locationincam,locationinfile,matchangle,matchscale);
    pwnd->m_imageprocess.ImageRotate(pwnd->m_imageprocess.resultimage,pwnd->m_imageprocess.rotateimage,matchangle);
	//------------------------------------------------------------------------��ת��ȷ����еĶԱ�
	
	//�ҵ���ת��ĵ�һ��λ��
	//��תͼƬ�Ĵ�СΪ6310*6310�����ģ�3155��3155��
	Point2i rotato;
	rotato.x=(locationincam[0].x+locationincam[1].x+locationincam[2].x+locationincam[3].x)/4;
	rotato.y=(locationincam[0].y+locationincam[1].y+locationincam[2].y+locationincam[3].y)/4;

	//Point2i rotatofile;
	rotatofile.x=(locationinfile[0].x+locationinfile[1].x+locationinfile[2].x+locationinfile[3].x)/4;
	rotatofile.y=(locationinfile[0].y+locationinfile[1].y+locationinfile[2].y+locationinfile[3].y)/4;

	Point2i location10;//������ĵ�
	location10.x=rotato.x-pwnd->m_imageprocess.resultimage.cols/2;
	location10.y=rotato.y-pwnd->m_imageprocess.resultimage.rows/2;//���ͼƬ���ĵ������
	//Point2i location11;//��ת��(6310*6310ͼƬ������)
	float sinx=sinf(matchangle*PI/180);
	float cosx=cosf(matchangle*PI/180);
	float m_temp=pwnd->m_imageprocess.resultimage.rows*pwnd->m_imageprocess.resultimage.rows+pwnd->m_imageprocess.resultimage.cols*pwnd->m_imageprocess.resultimage.cols;
	int XY_off=sqrt(m_temp)/2;
	location11.x=(location10.x)*cosx+(location10.y)*sinx+XY_off;//�����Ϊ����ƫ��
	location11.y=(location10.y)*cosx-(location10.x)*sinx+XY_off;
	Rect box;//���н������
	box.x=location11.x-(int)((rotatofile.x-xpcbmin)/matchscale);
	box.y=location11.y-(int)((rotatofile.y-ypcbmin)/matchscale);
	box.width=(xpcbmax-xpcbmin)/matchscale;
	box.height=(ypcbmax-ypcbmin)/matchscale;
	Mat cutimageresult(pwnd->m_imageprocess.rotateimage,box);
	cutimageresult.copyTo(pwnd->m_imageprocess.cut_1);
	//imwrite("F:\\result1.bmp",dst);

	imwrite("4�㶨λ����ͼ.bmp",pwnd->m_imageprocess.cut_1);
	pwnd->m_imageprocess.GetHole(cutimageresult);

	Mat test=imread("F:/AOID/AOID/4�㶨λ����ͼ.bmp", CV_LOAD_IMAGE_COLOR );
	Mat test2=imread("F:/AOID/AOID/4�㶨λ����ͼ.bmp", CV_LOAD_IMAGE_COLOR );
	for(int i = 0; i < pwnd->m_imageprocess.circles.size(); i++)//�ѻ���任������Բ������
	{
		Point center(cvRound(pwnd->m_imageprocess.circles[i].x), cvRound(pwnd->m_imageprocess.circles[i].y));
		int radius = cvRound(pwnd->m_imageprocess.circles[i].R);
		circle( test, center, radius, Scalar(0, 0, 255) );
		circle( test2, center, radius, Scalar(0, 0, 255),-1 );
	}

	imwrite("4�㶨λ��Բ.bmp",test);
	imwrite("4�㶨λ��Բ_����.bmp",test2);
	Mat test3=imread("F:/AOID/AOID/4�㶨λ����ͼ.bmp", CV_LOAD_IMAGE_COLOR );
	Mat test4=imread("F:/AOID/AOID/4�㶨λ����ͼ.bmp", CV_LOAD_IMAGE_COLOR );

	HoleInfoNode *curr3=theApp.mastprog.m_OriPosition->pnext;
	while(curr3!=NULL)
	{
		Point center(cvRound((curr3->position.nXs-xpcbmin)/matchscale), cvRound((curr3->position.nYs-ypcbmin)/matchscale));
		int radius = cvRound(((curr3->position.diameter)/2)/matchscale);
		circle( test3, center, radius, Scalar(0, 0, 255) );
		circle( test4, center, radius, Scalar(0, 0, 255),-1 );
		curr3=curr3->pnext;
	}
	imwrite("4�㶨λ��ӹ��ļ�.bmp",test3);
	imwrite("4�㶨λ��ӹ��ļ�_����.bmp",test4);
	//DrawcvMat(cutimageresult,IDC_CAMIMG,1);
	DrawcvMat(cutimageresult,IDC_CAMIMG,1);
}


void CCameraImageView::OnBnClickedFocus()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CCameraImageView::OnBnClickedtest()
{
	// ��ת��������
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	pwnd->m_camera.img_sweep=imread("F:/bmpͼ/result.bmp",CV_LOAD_IMAGE_ANYDEPTH|CV_LOAD_IMAGE_ANYCOLOR);
	//Mat mat = imread( "F:/result.bmp",CV_LOAD_IMAGE_ANYDEPTH|CV_LOAD_IMAGE_ANYCOLOR );
	pwnd->m_imageprocess.GetHole(pwnd->m_camera.img_sweep);
	
	//DrawcvMat(	pwnd->m_camera.img_sweep,IDC_CAMIMG,1);
	m_camimg.m_bActive=1;
	m_camimg.ShowImage(pwnd->m_camera.img_sweep,0);
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
	int width=mat.cols*camscale;
	int height=mat.rows*camscale;
	IplImage* drawing_ipl = &IplImage(img);
	CvvImage Cvvimg;
	Cvvimg.CopyOf(drawing_ipl);
	CRect rect1 = CRect(rect.TopLeft(), CSize(width,height));
	// ��ͼƬ���Ƶ���ʾ�ؼ���ָ��������
	Cvvimg.DrawToHDC(hDC, &rect1 );
	ReleaseDC(pDC);	


}


void CCameraImageView::OnBnClickedHough()
{
	
	//Mat mat = imread( "F:\\result.bmp",CV_LOAD_IMAGE_ANYDEPTH|CV_LOAD_IMAGE_ANYCOLOR );
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	//pwnd->m_imageprocess.HoughGetHole(mat);
	pwnd->m_pOpPaneWnd->SwitchToView(VIEW_TESTITEM);

	//DrawcvMat(mat,IDC_CAMIMG,1);
}

bool CCameraImageView::ProgressInRectfile(CPoint start,CPoint end)
{
	int wide,height;
	wide = abs(start.x-end.x);
	height = abs(start.y-end.y);
	if(start==end)//Ϊ����ѡ��
	{
		GetSelectCircleFill(start.x,start.y);//�ҳ���Բ����location��
		return true;
	}
/*	if (0!=wide&&0!=height)//ѡ���Ϊ����
	{
		CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
		CWnd *pWin = GetDlgItem(IDC_MASTINIMAGE);
		pWin->GetClientRect(rectfile);
		m_rectfile = pWin->GetDC();
		int Width=rectfile.Width();
		int Height=rectfile.Height();
       //�Ŵ��������Ͻ��ڼӹ��ļ��е�����
    	 Xlu+=start.x/filescale;
		 Ylu+=start.y/filescale;
		 float xscale,yscale,scalepp;
		 xscale=wide*(1.0)/Width;
		 yscale=height*(1.0)/Height;
		if(xscale<yscale)
        	scalepp=xscale;
		else
			scalepp=yscale;

		//�����µ�ʵ�ʳߴ������صı������ӣ���pcb������
		filescale =filescale*scalepp;//�±���
		m_rectfile->FillSolidRect(0,0,Width,Height,RGB(255,255,255));//���¿ͻ��� 1. ��ɫ���ɫ 2.����֮ǰ��ͼ��
		//��ͼ�߽�
		int wideinfile=wide/filescale;
		int heightinfile=height/filescale;
		HoleInfoNode *curr=theApp.mastprog.m_OriPosition->pnext;
		while(curr->pnext!=NULL)
		{
			int x,y,R;
			x=curr->position.nXs-Xlu;
			y=curr->position.nYs-Ylu;
			R=curr->position.diameter/2;
			if (x>0&&x<wideinfile&&y>0&&y<heightinfile)
			{
				 m_rectfile->Ellipse((x-R-Xlu)*filescale,(y-R-Ylu)*filescale,(x+R-Xlu)*filescale,(y+R-Ylu)*filescale);
			}
			curr=curr->pnext;
		}
		return true;
	}*/
	return false;
}

bool CCameraImageView::GetSelectCircleFill(int x,int y)
{

	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	int x1,y1;
	int x2,y2;
	double x0,y0;
	double diameter,radius;
	int radiusx,radiusy;
	if (NULL==theApp.mastprog.m_OriPosition)
		return false;
	HoleInfoNode *pnode;
	pnode = theApp.mastprog.m_OriPosition->pnext;
	x=x/filescale+Xlu;
	y=y/filescale+Ylu;
	circlestruct  end,temp;
	bool  ALD=0;
	while(pnode)
	{
		diameter = pnode->position.diameter;
		radius = diameter/2;
		x0=pnode->position.nXs;
		y0=pnode->position.nYs;
		x1 = int(x0-2*radius);
		y1 = int(y0-2*radius);
		x2 = int(x0+2*radius);
		y2 = int(y0+2*radius);	
		if(x<=x2&&x>=x1&&y<=y2&&y>=y1)
		{
			//�����ҵ����ڵ�Բ;
			if (ALD==1)
			{
				temp.x=pnode->position.nXs;
				temp.y=pnode->position.nYs;
				temp.R=(pnode->position.diameter)/2;
				if ((temp.x-x)*(temp.x-x)+(temp.y-y)*(temp.y-y)<(end.x-x)*(end.x-x)+(end.y-y)*(end.y-y))
				{	
					end=temp;
				}

			}
			else
			{
				end.x=pnode->position.nXs;
				end.y=pnode->position.nYs;
				end.R=(pnode->position.diameter)/2;
				ALD=1;
			}
		}
		pnode=pnode->pnext;
	}
	locationinfile.push_back(end);
	return true;
}

bool CCameraImageView::ProgressInRectCam(CPoint start,CPoint end)
{
	int wide,height;
	wide = abs(start.x-end.x);
	height = abs(start.y-end.y);
	if(start==end)//Ϊ����ѡ��
	{
		GetSelectCircleCam(start.x,start.y);//�ҳ���Բ����location��
		return true;
	}
	if (0!=wide&&0!=height)//ѡ���Ϊ����
	{
		FillRect(m_rectcam->GetSafeHdc(),rectcam,CBrush(RGB(255,255,255)));//���ؼ�����תΪ��ɫ
		//------------------------��Ӵ���
		return true;
	}
	return false;
}

bool CCameraImageView::GetSelectCircleCam(int x, int y)
{
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	int x1,y1;
	int x2,y2;
	double x0,y0;
	double diameter,radius;
	int radiusx,radiusy;
	int num=pwnd->m_imageprocess.circles.size();
	if (0==num)
	{
		MessageBox(NULL,_T("δ�ҵ�Բ"),MB_OK);
		return false;
	}
	x=x/camscale;
	y=y/camscale;
	circlestruct  end,temp;
	bool ALD=0;
	for(int i=0;i<num;i++)
	{
		radius=pwnd->m_imageprocess.circles[i].R;
		x1 =(pwnd->m_imageprocess.circles[i].x)-2*radius;
		x2 =(pwnd->m_imageprocess.circles[i].x)+2*radius;
		y1 =(pwnd->m_imageprocess.circles[i].y)-2*radius;
		y2 =(pwnd->m_imageprocess.circles[i].y)+2*radius;
		if(x<=x2&&x>=x1&&y<=y2&&y>=y1)
		{
			if (ALD==1)
			{
				temp=pwnd->m_imageprocess.circles[i];
				if ((temp.x-x)*(temp.x-x)+(temp.y-y)*(temp.y-y)<(end.x-x)*(end.x-x)+(end.y-y)*(end.y-y))
				{
					end=temp;
				}
			}
			else
			{
				ALD=1;
				end=pwnd->m_imageprocess.circles[i];
			}	
		}
	}
	locationincam.push_back(end);
	return true;
}

void CCameraImageView::OnLButtonDown(UINT nFlags, CPoint point)
{
	//CClientDC dc(this);
	//OnPrepareDC(&dc,NULL);
	//dc.DPtoLP(&point);
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();

	//-----------------------------
	CWnd *pWin1= GetDlgItem(IDC_MASTINIMAGE);
	pWin1->GetWindowRect(rectfile);
	CWnd *pWin2= GetDlgItem(IDC_CAMIMG);
	pWin2->GetWindowRect(rectcam);
	ScreenToClient(rectfile);
	ScreenToClient(rectcam);
	//--------------------------------------------------------------------
	this->SetFocus();

	//--------------------------------------------
	//��������ڵ��ڿͻ����е�����
	inrectfile=false;
	inrectcam=false;
	int x,y;
	CPoint p;	
	p = point;
	startpoint = p;
	mouseexflag = true; //��갴�±��
	CRect test;
	test=rectfile;
	if (p.x>rectfile.left&&p.x<rectfile.right&&p.y>rectfile.top&&p.y<rectfile.bottom)
	{
		startpoint.x-=rectfile.left;
		startpoint.y-=rectfile.top;
		inrectfile=true;
		return;
	}
	if (p.x>rectcam.left&&p.x<rectcam.right&&p.y>rectcam.top&&p.y<rectcam.bottom)//������ͷͼƬ��������
	{
		startpoint.x-=rectcam.left;
		startpoint.y-=rectcam.top;
		inrectcam=true;
		return;
	}

	/*
	ASSERT(m_camimg);
	m_camimg.OnLButtonDown(nFlags,point);
	CView::OnLButtonDown(nFlags, point);
	*/
}

void CCameraImageView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	CWnd *pWin1= GetDlgItem(IDC_MASTINIMAGE);
	pWin1->GetWindowRect(rectfile);
	CWnd *pWin2= GetDlgItem(IDC_CAMIMG);
	pWin2->GetWindowRect(rectcam);
	ScreenToClient(rectfile);
	ScreenToClient(rectcam);
	if(mouseexflag == true)
	{
		mouseexflag = false;
		int x,y;	
		float xscalepp,yscalepp;
		//��������ڵ��ڿͻ�ȥ�е�����
		CPoint p;
		p = point;
		endpoint=p;
		if (true==inrectfile)
		{
			if (p.x>rectfile.left&&p.x<rectfile.right&&p.y>rectfile.top&&p.y<rectfile.bottom)//�ڶ��ļ���
			{
				endpoint.x-=rectfile.left;
				endpoint.y-=rectfile.top;
				ProgressInRectfile(startpoint,endpoint);  
			}
			else
			{
				pwnd->m_pProgPaneWnd->m_pProgressView->WarnMessage("�ӹ��ļ���ʾ��ѡ�񳬽�",red);
				return;
			}

		}
		if (true==inrectcam)
		{
			if (p.x>rectcam.left&&p.x<rectcam.right&&p.y>rectcam.top&&p.y<rectcam.bottom)//������ͷ�ɼ���
			{
				endpoint.x-=rectcam.left;
				endpoint.y-=rectcam.top;
				ProgressInRectCam(startpoint,endpoint);
			}
			else
			{
				pwnd->m_pProgPaneWnd->m_pProgressView->WarnMessage("����ͷ��ʾ��ѡ�񳬽�",red);
				return;
			}

		}
	}
	/*
	CClientDC dc(this);
	OnPrepareDC(&dc,NULL);
	dc.DPtoLP(&point);

	ASSERT(m_camimg);
	m_camimg.OnLButtonUp(nFlags,point);
	CView::OnLButtonUp(nFlags, point);
	*/
}

void CCameraImageView::OnMButtonDown(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc,NULL);
	dc.DPtoLP(&point);

	ASSERT(m_camimg);
	m_camimg.OnMButtonDown(nFlags,point);
	CView::OnMButtonDown(nFlags, point);
}

void CCameraImageView::OnMButtonUp(UINT nFlags, CPoint point)
{
	
	CClientDC dc(this);
	OnPrepareDC(&dc,NULL);
	dc.DPtoLP(&point);

	ASSERT(m_camimg);
	m_camimg.OnMButtonUp(nFlags,point);
	CView::OnMButtonUp(nFlags, point);
	
}

void CCameraImageView::OnMouseMove(UINT nFlags, CPoint point)
{
	//CClientDC dc(this);
	//OnPrepareDC(&dc,NULL);
	//dc.DPtoLP(&point);

	ASSERT(m_camimg);
	m_camimg.OnMouseMove(nFlags,point);
	CView::OnMouseMove(nFlags, point);
}

BOOL CCameraImageView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	CClientDC dc(this);
	OnPrepareDC(&dc,NULL);
	dc.DPtoLP(&pt);

	ASSERT(m_camimg);
	m_camimg.OnMouseWheel(nFlags, zDelta ,pt);
	return CView::OnMouseWheel(nFlags, zDelta ,pt);


}


void CCameraImageView::OnBnClickedgettestimage()
{
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	pwnd->m_imageprocess.resultimage=imread("F:/4�㶨λ����ͼ.bmp", CV_LOAD_IMAGE_ANYDEPTH|CV_LOAD_IMAGE_ANYCOLOR );
	//pwnd->m_imageprocess.resultimage=imread("G:/�ɼ�ʵͼ.bmp",CV_LOAD_IMAGE_ANYDEPTH|CV_LOAD_IMAGE_ANYCOLOR);
	//m_camimg.ShowImage(pwnd->m_imageprocess.resultimage,0);
	DrawcvMat(pwnd->m_imageprocess.resultimage,IDC_CAMIMG,1);
}


void CCameraImageView::OnBnClickedCamera()
{
	OnCamera();
}
	
int CCameraImageView::OnCamera()

{
	VideoCapture cap(0);  
	if(!cap.isOpened())  
	{  
		return -1;  
	}  
	Mat frame;  
	Mat edges; 

	Sleep(2000);
	while(1)  
	{  
		cap>>frame;  
		cvtColor(frame, edges, CV_BGR2GRAY);  
		GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);  
		Canny(edges, edges, 0, 30, 3);  
		imshow("��ǰ��Ƶ",edges);  
		char c = cvWaitKey(33);
		  
		if (c == 13)
		{
			CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
			edges.copyTo(pwnd-> m_imageprocess.camerafusb);
			//Mat m_camerafusb = pwnd-> m_imageprocess.camerafusb.clone ();
			DrawcvMat(pwnd-> m_imageprocess.camerafusb,IDC_CAMIMG,1);
			imwrite("����ͼ.bmp",pwnd-> m_imageprocess.camerafusb);
			break;
			
		}
		if( c == 27)  break;

	}  
	cap.release();  
	cvDestroyWindow("��ǰ��Ƶ");  
	return 0;  
}

void CCameraImageView::Box()
{
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	pwnd-> m_imageprocess.camerafusb = imread("F:/AOID/AOID/���ȱ�׼��2.bmp",CV_LOAD_IMAGE_ANYDEPTH|CV_LOAD_IMAGE_ANYCOLOR);
	GaussianBlur(pwnd-> m_imageprocess.camerafusb,pwnd-> m_imageprocess.camerafusb, Size(7,7), 1.5, 1.5);  
	vector<Vec4i> lines;
	vector<Vec4i> linesout;
	vector<vector<Point> > contours;
	threshold(pwnd-> m_imageprocess.camerafusb,pwnd-> m_imageprocess.camerafusb,220,255,THRESH_BINARY);//��ֵͼ�����ɣ�
	findContours(pwnd-> m_imageprocess.camerafusb,contours,CV_RETR_LIST,CV_CHAIN_APPROX_NONE);
	for (auto i = pwnd-> m_imageprocess.camerafusb.begin<uchar>(); i != pwnd-> m_imageprocess.camerafusb.end<uchar>(); i++)
	{
		*i = 0 ;
	}
	for (auto itVec = contours.begin() ; itVec != contours.end();)
	{
		if ( (*itVec).size() > 9000 || (*itVec).size() < 6000 )
		{
			itVec = contours.erase(itVec);
		}
		else
			itVec++;
	}
	cvtColor(pwnd-> m_imageprocess.camerafusb, pwnd-> m_imageprocess.camerafusb, CV_GRAY2BGR);  

	//��С��Ӿ���
	for(int i = 0; i < contours.size(); i++)   
	{    
		End_Rage2D = minAreaRect(contours[i]);    //����cvMinAreaRect2��������õ���С��Χ����  �����ѵó���������ĽǶȣ����,�߶ȣ����е����������CvBox2D���͵Ľṹ���У���Ҫ��������������  
		DrawBox(End_Rage2D,pwnd-> m_imageprocess.camerafusb);

	}  //����175mm��׼������Ϊ168.5mm
	imwrite("���ȱ�׼���߳�.bmp",pwnd-> m_imageprocess.camerafusb);//pwnd-> m_imageprocess.camerafusb                                               
	DrawcvMat(pwnd-> m_imageprocess.camerafusb,IDC_CAMIMG,1);

}

void CCameraImageView::OnBnClickedHoughline() //б�ߵ�������ֱ��
{
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	pwnd-> m_imageprocess.camerafusb = imread("F:/AOID/AOID/���ȱ�׼��2.bmp",CV_LOAD_IMAGE_ANYDEPTH|CV_LOAD_IMAGE_ANYCOLOR);
	//	"F:/AOID/AOID/�ޱ���_cr.bmp"
	//medianBlur(pwnd-> m_imageprocess.camerafusb,pwnd-> m_imageprocess.camerafusb,5);//��ֵ�˲�
	GaussianBlur(pwnd-> m_imageprocess.camerafusb,pwnd-> m_imageprocess.camerafusb, Size(7,7), 1.5, 1.5);  
	//Laplacian( pwnd-> m_imageprocess.camerafusb, pwnd-> m_imageprocess.camerafusb, CV_8U, 3, 1, 0, BORDER_DEFAULT );
	//Canny(pwnd-> m_imageprocess.camerafusb,pwnd-> m_imageprocess.camerafusb, 20,60, 3);  
	vector<Vec4i> lines;
	vector<Vec4i> linesout;
	vector<vector<Point> > contours;

	threshold(pwnd-> m_imageprocess.camerafusb,pwnd-> m_imageprocess.camerafusb,220,255,THRESH_BINARY);//��ֵͼ�����ɣ�
	findContours(pwnd-> m_imageprocess.camerafusb,contours,CV_RETR_LIST,CV_CHAIN_APPROX_NONE);
	for (auto i = pwnd-> m_imageprocess.camerafusb.begin<uchar>(); i != pwnd-> m_imageprocess.camerafusb.end<uchar>(); i++)
	{
		*i = 0 ;
	}
	for (auto itVec = contours.begin() ; itVec != contours.end();)
	{
		if ( (*itVec).size() > 9000 || (*itVec).size() < 6000 )
		{
			itVec = contours.erase(itVec);
		}
		else
			itVec++;
	}
	cvtColor(pwnd-> m_imageprocess.camerafusb, pwnd-> m_imageprocess.camerafusb, CV_GRAY2BGR);  

	//��С��Ӿ���
	for(int i = 0; i < contours.size(); i++)   
	{    
		End_Rage2D = minAreaRect(contours[i]);    //����cvMinAreaRect2��������õ���С��Χ����  �����ѵó���������ĽǶȣ����,�߶ȣ����е����������CvBox2D���͵Ľṹ���У���Ҫ��������������  
		DrawBox(End_Rage2D,pwnd-> m_imageprocess.camerafusb);

	}  //����175mm��׼������Ϊ168.5mm

	//drawContours(pwnd-> m_imageprocess.camerafusb,contours1,-1,Scalar(255,0,0),2);
	

// 	drawContours(pwnd-> m_imageprocess.camerafusb,contours,-1,Scalar(255),2,8);
// 
// 	pwnd->m_imageprocess.camerafusb = thinImage(pwnd-> m_imageprocess.camerafusb,-1);
// 	
// 	HoughLinesP(pwnd-> m_imageprocess.camerafusb, lines, 1, CV_PI/180, 100, 100, 30 );
// 
// 	for (auto i = pwnd-> m_imageprocess.camerafusb.begin<uchar>(); i != pwnd-> m_imageprocess.camerafusb.end<uchar>(); i++)
// 	{
// 		*i = 255 ;
// 	}
// 	cvtColor(pwnd-> m_imageprocess.camerafusb, pwnd-> m_imageprocess.camerafusb, CV_GRAY2BGR); 
 /*	
	auto iter = contours1.begin();
	while (iter != contours1.end()) 
	{
		if (*iter > csize)
		{
			++iter;
		}
		else 
		{
			iter = contours1.erase(iter);
		}
	}
	*/

// 	for (int i =0 ; i< lines.size(); i++)
// 		{
// 			float dis =  sqrt(float((lines[i][0]-lines[i][2])^2+(lines[i][1]-lines[i][3])^2));
// 			if (lines[i][0] * lines[i][1] * lines[i][2] * lines[i][3] == 0 || lines[i][0] <= 10  )
// 			{
// 
// 			} 
// 			else
// 			{
// 				line( pwnd-> m_imageprocess.camerafusb, Point(lines[i][0],lines[i][1]), Point(lines[i][2], lines[i][3]), Scalar(0,0,255), 1, 8); //CV_AA �����
// 			}
// 		}
// 	

	imwrite("���ȱ�׼���߳�.bmp",pwnd-> m_imageprocess.camerafusb);//pwnd-> m_imageprocess.camerafusb                                               
	DrawcvMat(pwnd-> m_imageprocess.camerafusb,IDC_CAMIMG,1);
	
	//836,95   3796,104
}

//�������ص�����ڵ�ĸ���
int  CCameraImageView::Findn(Mat* img, int i, int j)
{
	CvScalar s1 = cvGet2D(img, i, j);
	CvScalar s2 = cvGet2D(img, i - 1, j);
	CvScalar s3 = cvGet2D(img, i - 1, j + 1);
	CvScalar s4 = cvGet2D(img, i, j + 1);
	CvScalar s5 = cvGet2D(img, i + 1, j + 1);
	CvScalar s6 = cvGet2D(img, i + 1, j);
	CvScalar s7 = cvGet2D(img, i + 1, j - 1);
	CvScalar s8 = cvGet2D(img, i, j - 1);
	CvScalar s9 = cvGet2D(img, i - 1, j - 1);
	int a = s1.val[0];
	int b = s2.val[0];
	int c = s3.val[0];
	int d = s4.val[0];
	int e = s5.val[0];
	int f = s6.val[0];
	int g = s7.val[0];
	int h = s8.val[0];
	int l = s9.val[0];
	int find[] = { a, b, c, d, e, f, g, h, l };//��8����˳�������飬�������
	int n = 0;
	for (int x = 2; x < 9; ++x)
	{
		if (find[x] == 0 && find[x + 1] == 255)
		{
			n = n + 1;
		}
	}
	return n;
}
/*
//ϸ��ֱ�߹��ܺ���
Mat* CCameraImageView::ThinImage(Mat* img, int k)
{
	int condition = 0;//�������������
	int mark = 0;//�ɹ��ı�־λ
	int firstN = 0;//��һ�������ڵ�ĸ���
	CvScalar s;
	for (int n = 0; n < k; ++n)
	{
		for (int i = 1; i < img->cols - 1; ++i)
		{
			 for (int j = 1; j < img->rows - 1;++j)
			{//��ʼ����1��Ѱ��
				condition = 0;//��ʼ������������
			   //cout << "1" << endl;
				s = cvGet2D(img, i, j);
				if (s.val[0] == 255)//�������ǰ���㣬����Ե
				 {
					//cout << "2" << endl;
					 //*************************��һ����*************************
					 //*************************step1****************************
					firstN = 0;
					 for (int ii = -1; ii < 1; ++ii)
					 {
						 for (int jj = -1; jj < 1; ++jj)
						{
							s = cvGet2D(img, i + ii, j + jj);
							 if (s.val[0] == 255)
							 {
								  firstN = firstN + 1;
							}
						 }
					 }
					 if (firstN < 3 || firstN > 7)
					 {
						 continue;
					 }
				   else
					 {
						condition = condition + 1;
					 }
     //**************************************************************
     //*************************step2********************************
				  if (Findn(img, i, j) != 1)
					{
						 continue;
					 }
				 else
					{
						condition = condition + 1;
					}
     //***************************************************************
     //*************************step3*********************************
				CvScalar s1 = cvGet2D(img, i - 1, j);
				CvScalar s2 = cvGet2D(img, i, j + 1);
				CvScalar s3 = cvGet2D(img, i + 1, j);
				CvScalar s4 = cvGet2D(img, i, j - 1);
				int a = s1.val[0];//2
				int b = s2.val[0];//4
				int c = s3.val[0];//6
				int d = s4.val[0];//8
				if (a * b * c != 0)
				  {
					continue;
				  }
				else
				 {
					condition = condition + 1;
				 }
     //******************************************************************
     //******************************step4*******************************
				if (b * c * d != 0)
				  {
					 continue;
				  }
				 else
				  {
					 condition = condition + 1;
				  }
     //******************************************************************
     //��һ���̵Ľ������
				 if (condition == 4)
				  {
					mark = 1;
      //((char *)(img->imageData + img->widthStep * (i)))[j] = 0;
					CvScalar p;
					p.val[0] = 0;
					cvSet2D(img, i, j, p);
      //cout << "11111111111111111111111111111111111" << endl;
				  }
			  }
		  }
  	  }
  //****************************����2************************************
	 for (int i = 1; i < img->cols - 1; ++i)
	 {
		 for (int j = 1; j < img->rows - 1;++j)
			{//��ʼ����1��Ѱ��
			  condition = 0;//��ʼ������������
			 //cout << "1" << endl;
			  s = cvGet2D(img, i, j);
			 if (s.val[0] == 255)//�������ǰ���㣬����Ե
			  {
     //cout << "2" << endl;
     //*************************�ڶ�����********************************
     //*************************step1***********************************
				 firstN = 0;
				 for (int ii = -1; ii < 1; ++ii)
				{
					 for (int jj = -1; jj < 1; ++jj)
					 {
						  s = cvGet2D(img, i + ii, j + jj);
						 if (s.val[0] == 255)
						{
						  firstN = firstN + 1;
						 }
					 }
				}
				if (firstN < 3 || firstN > 7)
				{
					continue;
				 }
				else
				 {
					condition = condition + 1;
				 }
     //*****************************************************************
     //*************************step2***********************************
				 if (Findn(img, i, j) != 1)
				{
					 continue;
				}
				else
				 {
					 condition = condition + 1;
				 }
     //*****************************************************************
     //*************************step3***********************************
				 CvScalar s1 = cvGet2D(img, i - 1, j);
				 CvScalar s2 = cvGet2D(img, i, j + 1);
				 CvScalar s3 = cvGet2D(img, i + 1, j);
				 CvScalar s4 = cvGet2D(img, i, j - 1);
				 int a = s1.val[0];//2
				 int b = s2.val[0];//4
				 int c = s3.val[0];//6
				 int d = s4.val[0];//8
				 if (a * b * d != 0)
				{
				  continue;
				}
				else
				{
				  condition = condition + 1;
			    }
     //*******************************************************************
     //******************************step4********************************
				 if (a * c * d != 0)
				 {
				   continue;
				 }
				 else
				 {
					condition = condition + 1;
				  }
     //*******************************************************************
     //�ڶ����̵Ľ������
				 if (condition == 4)
				 {
					  mark = 1;
					 //((char *)(img->imageData + img->widthStep * (i)))[j] = 0;
					  CvScalar p;
					  p.val[0] = 0;
					  cvSet2D(img, i, j, p);
					 //cout << "222222222222222222222222" << endl;
				 }
				}
			}
		}
	 //cout << " end " << endl;
	}
 return img;
}
*/
Mat CCameraImageView::thinImage(const Mat & src, const int maxIterations = -1)  
{  
	assert(src.type() == CV_8UC1);  
	cv::Mat dst;  
	int width  = src.cols;  
	int height = src.rows;  
	src.copyTo(dst);  
	int count = 0;  //��¼��������  
	while (true)  
	{  
		count++;  
		if (maxIterations != -1 && count > maxIterations) //���ƴ������ҵ�����������  
			break;  
		std::vector<uchar *> mFlag; //���ڱ����Ҫɾ���ĵ�  
		//�Ե���  
		for (int i = 0; i < height ;++i)  
		{  
			uchar * p = dst.ptr<uchar>(i);  
			for (int j = 0; j < width; ++j)  
			{  
				//��������ĸ����������б��  
				//  p9 p2 p3  
				//  p8 p1 p4  
				//  p7 p6 p5  
				uchar p1 = p[j];  
				if (p1 != 1) continue;  
				uchar p4 = (j == width - 1) ? 0 : *(p + j + 1);  
				uchar p8 = (j == 0) ? 0 : *(p + j - 1);  
				uchar p2 = (i == 0) ? 0 : *(p - dst.step + j);  
				uchar p3 = (i == 0 || j == width - 1) ? 0 : *(p - dst.step + j + 1);  
				uchar p9 = (i == 0 || j == 0) ? 0 : *(p - dst.step + j - 1);  
				uchar p6 = (i == height - 1) ? 0 : *(p + dst.step + j);  
				uchar p5 = (i == height - 1 || j == width - 1) ? 0 : *(p + dst.step + j + 1);  
				uchar p7 = (i == height - 1 || j == 0) ? 0 : *(p + dst.step + j - 1);  
				if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) >= 2 && (p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) <= 6)  
				{  
					int ap = 0;  
					if (p2 == 0 && p3 == 1) ++ap;  
					if (p3 == 0 && p4 == 1) ++ap;  
					if (p4 == 0 && p5 == 1) ++ap;  
					if (p5 == 0 && p6 == 1) ++ap;  
					if (p6 == 0 && p7 == 1) ++ap;  
					if (p7 == 0 && p8 == 1) ++ap;  
					if (p8 == 0 && p9 == 1) ++ap;  
					if (p9 == 0 && p2 == 1) ++ap;  

					if (ap == 1 && p2 * p4 * p6 == 0 && p4 * p6 * p8 == 0)  
					{  
						//���  
						mFlag.push_back(p+j);  
					}  
				}  
			}  
		}  

		//����ǵĵ�ɾ��  
		for (std::vector<uchar *>::iterator i = mFlag.begin(); i != mFlag.end(); ++i)  
		{  
			**i = 0;  
		}  

		//ֱ��û�е����㣬�㷨����  
		if (mFlag.empty())  
		{  
			break;  
		}  
		else  
		{  
			mFlag.clear();//��mFlag���  
		}  

		//�Ե���  
		for (int i = 0; i < height; ++i)  
		{  
			uchar * p = dst.ptr<uchar>(i);  
			for (int j = 0; j < width; ++j)  
			{  
				//��������ĸ����������б��  
				//  p9 p2 p3  
				//  p8 p1 p4  
				//  p7 p6 p5  
				uchar p1 = p[j];  
				if (p1 != 1) continue;  
				uchar p4 = (j == width - 1) ? 0 : *(p + j + 1);  
				uchar p8 = (j == 0) ? 0 : *(p + j - 1);  
				uchar p2 = (i == 0) ? 0 : *(p - dst.step + j);  
				uchar p3 = (i == 0 || j == width - 1) ? 0 : *(p - dst.step + j + 1);  
				uchar p9 = (i == 0 || j == 0) ? 0 : *(p - dst.step + j - 1);  
				uchar p6 = (i == height - 1) ? 0 : *(p + dst.step + j);  
				uchar p5 = (i == height - 1 || j == width - 1) ? 0 : *(p + dst.step + j + 1);  
				uchar p7 = (i == height - 1 || j == 0) ? 0 : *(p + dst.step + j - 1);  

				if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) >= 2 && (p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) <= 6)  
				{  
					int ap = 0;  
					if (p2 == 0 && p3 == 1) ++ap;  
					if (p3 == 0 && p4 == 1) ++ap;  
					if (p4 == 0 && p5 == 1) ++ap;  
					if (p5 == 0 && p6 == 1) ++ap;  
					if (p6 == 0 && p7 == 1) ++ap;  
					if (p7 == 0 && p8 == 1) ++ap;  
					if (p8 == 0 && p9 == 1) ++ap;  
					if (p9 == 0 && p2 == 1) ++ap;  

					if (ap == 1 && p2 * p4 * p8 == 0 && p2 * p6 * p8 == 0)  
					{  
						//���  
						mFlag.push_back(p+j);  
					}  
				}  
			}  
		}  

		//����ǵĵ�ɾ��  
		for (std::vector<uchar *>::iterator i = mFlag.begin(); i != mFlag.end(); ++i)  
		{  
			**i = 0;  
		}  

		//ֱ��û�е����㣬�㷨����  
		if (mFlag.empty())  
		{  
			break;  
		}  
		else  
		{  
			mFlag.clear();//��mFlag���  
		}  
	}  
	return dst;  
}  

void CCameraImageView::DrawBox(CvBox2D box,Mat img)
{
	CvPoint2D32f point[4]; 
	int i; 
	for ( i=0; i<4; i++) 
	{ 
		point[i].x = 0; 
		point[i].y = 0; 
	} 
	cvBoxPoints(box, point); //�����ά���Ӷ��� 
	CvPoint pt[4]; 
	for ( i=0; i<4; i++) 
	{ 
		pt[i].x = (int)point[i].x; 
		pt[i].y = (int)point[i].y; 
	} 
	line( img, pt[0], pt[1], Scalar(0,0,255), 1, 8 ); 
	line( img, pt[1], pt[2], Scalar(0,0,255), 1, 8 ); 
	line( img, pt[2], pt[3], Scalar(0,0,255), 1, 8 ); 
	line( img, pt[3], pt[0], Scalar(0,0,255), 1, 8 ); 
}
