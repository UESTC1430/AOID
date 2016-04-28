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
		MessageBox(NULL,_T("未导入文件"),MB_OK);
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
	imag.Save("G:/加工图.bmp");
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
		pwnd->m_pProgPaneWnd->m_pProgressView->WarnMessage("在图片上未找到圆",red);

	}
	if (theApp.mastprog.m_OriPosition==NULL)
	{
		pwnd->m_pProgPaneWnd->m_pProgressView->WarnMessage("加工文件未导入",red);
		return ;
	}
	locationinfile.clear();
	locationincam.clear();
	pwnd->m_pProgPaneWnd->m_pProgressView->WarnMessage("请在文件导入图上选择4个定位点",green);
}


void CCameraImageView::CameraimageShow()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	DrawcvMat(pwnd->m_camera.img_sweep,IDC_CAMIMG,1);
	imwrite("G:/扫描图.bmp",pwnd->m_camera.img_sweep);
}


void CCameraImageView::OnCutImage()
{
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
  	if (locationinfile.size()==4&&locationincam.size()==4)
	{
		pwnd->m_pProgPaneWnd->m_pProgressView->WarnMessage("定位点选择完毕",white);
	}
	else
	{
		pwnd->m_pProgPaneWnd->m_pProgressView->WarnMessage("定位点选择发生错误",red);
		return;
	}
	
    pwnd->m_imageprocess.FourPiontPosition(locationincam,locationinfile,matchangle,matchscale);
    pwnd->m_imageprocess.ImageRotate(pwnd->m_imageprocess.resultimage,pwnd->m_imageprocess.rotateimage,matchangle);
	//------------------------------------------------------------------------旋转正确后进行的对比
	
	//找到旋转后的第一定位点
	//旋转图片的大小为6310*6310，中心（3155，3155）
	Point2i rotato;
	rotato.x=(locationincam[0].x+locationincam[1].x+locationincam[2].x+locationincam[3].x)/4;
	rotato.y=(locationincam[0].y+locationincam[1].y+locationincam[2].y+locationincam[3].y)/4;

	//Point2i rotatofile;
	rotatofile.x=(locationinfile[0].x+locationinfile[1].x+locationinfile[2].x+locationinfile[3].x)/4;
	rotatofile.y=(locationinfile[0].y+locationinfile[1].y+locationinfile[2].y+locationinfile[3].y)/4;

	Point2i location10;//存放中心点
	location10.x=rotato.x-pwnd->m_imageprocess.resultimage.cols/2;
	location10.y=rotato.y-pwnd->m_imageprocess.resultimage.rows/2;//相对图片中心点的坐标
	//Point2i location11;//旋转后(6310*6310图片的坐标)
	float sinx=sinf(matchangle*PI/180);
	float cosx=cosf(matchangle*PI/180);
	float m_temp=pwnd->m_imageprocess.resultimage.rows*pwnd->m_imageprocess.resultimage.rows+pwnd->m_imageprocess.resultimage.cols*pwnd->m_imageprocess.resultimage.cols;
	int XY_off=sqrt(m_temp)/2;
	location11.x=(location10.x)*cosx+(location10.y)*sinx+XY_off;//最后项为坐标偏移
	location11.y=(location10.y)*cosx-(location10.x)*sinx+XY_off;
	Rect box;//剪切结果区域
	box.x=location11.x-(int)((rotatofile.x-xpcbmin)/matchscale);
	box.y=location11.y-(int)((rotatofile.y-ypcbmin)/matchscale);
	box.width=(xpcbmax-xpcbmin)/matchscale;
	box.height=(ypcbmax-ypcbmin)/matchscale;
	Mat cutimageresult(pwnd->m_imageprocess.rotateimage,box);
	cutimageresult.copyTo(pwnd->m_imageprocess.cut_1);
	//imwrite("F:\\result1.bmp",dst);

	imwrite("G:\\4点定位剪切图.bmp",pwnd->m_imageprocess.cut_1);
	pwnd->m_imageprocess.GetHole(cutimageresult);

	Mat test=imread("G:/4点定位剪切图.bmp", CV_LOAD_IMAGE_COLOR );
	Mat test2=imread("G:/4点定位剪切图.bmp", CV_LOAD_IMAGE_COLOR );
	for(int i = 0; i < pwnd->m_imageprocess.circles.size(); i++)//把霍夫变换检测出的圆画出来
	{
		Point center(cvRound(pwnd->m_imageprocess.circles[i].x), cvRound(pwnd->m_imageprocess.circles[i].y));
		int radius = cvRound(pwnd->m_imageprocess.circles[i].R);
		circle( test, center, radius, Scalar(0, 0, 255) );
		circle( test2, center, radius, Scalar(0, 0, 255),-1 );
	}

	imwrite("G:/4点定位找圆.bmp",test);
	imwrite("G:/4点定位找圆_论文.bmp",test2);
	Mat test3=imread("G:/4点定位剪切图.bmp", CV_LOAD_IMAGE_COLOR );
	Mat test4=imread("G:/4点定位剪切图.bmp", CV_LOAD_IMAGE_COLOR );

	HoleInfoNode *curr3=theApp.mastprog.m_OriPosition->pnext;
	while(curr3!=NULL)
	{
		Point center(cvRound((curr3->position.nXs-xpcbmin)/matchscale), cvRound((curr3->position.nYs-ypcbmin)/matchscale));
		int radius = cvRound(((curr3->position.diameter)/2)/matchscale);
		circle( test3, center, radius, Scalar(0, 0, 255) );
		circle( test4, center, radius, Scalar(0, 0, 255),-1 );
		curr3=curr3->pnext;
	}
	imwrite("G:/4点定位与加工文件.bmp",test3);
	imwrite("G:/4点定位与加工文件_论文.bmp",test4);
	DrawcvMat(cutimageresult,IDC_CAMIMG,1);

   /* DrawcvMat(cutimageresult,IDC_CAMIMG,1);
	CWnd *pWin = GetDlgItem(IDC_CAMIMG);
	pWin->GetClientRect(rectcam);
	m_rectcam = pWin->GetDC();
	//---------------------------------------------------------------------zns0915
	Xlu=xpcbmin;
	Ylu=ypcbmin;
	filescale=start_filescale;
	/*CBrush brush,*oldbrush; 
	brush.CreateSolidBrush(RGB(255,0,0)); 
	oldbrush=m_rectcam->SelectObject(&brush); 
	for (int i=0;i<4;i++)
	{	
		int x1=(locationinfile[i].x-xpcbmin-locationinfile[i].R)*filescale;
		int x2=(locationinfile[i].x-xpcbmin+locationinfile[i].R)*filescale;
		int y1=(locationinfile[i].y-ypcbmin-locationinfile[i].R)*filescale;
		int y2=(locationinfile[i].y-ypcbmin+locationinfile[i].R)*filescale;
		m_rectcam->Ellipse(x1,y1,x2,y2);
	}
	 m_rectcam->SelectObject(oldbrush);*

	CBrush brush,*oldbrush;
	HoleInfoNode *curr3=theApp.mastprog.m_OriPosition->pnext;
	brush.CreateSolidBrush(RGB(255,0,0)); 
	oldbrush=m_rectcam->SelectObject(&brush); 
	 while(curr3!=NULL)
	{	
		int x1=(curr3->position.nXs-xpcbmin-(curr3->position.diameter)/2)*filescale;
		int x2=(curr3->position.nXs-xpcbmin+(curr3->position.diameter)/2)*filescale;
		int y1=(curr3->position.nYs-ypcbmin-(curr3->position.diameter)/2)*filescale;
		int y2=(curr3->position.nYs-ypcbmin+(curr3->position.diameter)/2)*filescale;
		m_rectcam->Ellipse(x1,y1,x2,y2);
		 curr3=curr3->pnext;
	}
	m_rectcam->SelectObject(oldbrush);
	
	

	//-----------------------------------------------------------------------------
	/*Point2i location10;//存放中心点
	location10.x=locationincam[0].x-2048;
	location10.y=locationincam[0].y-2400;//相对图片中心点的坐标
	Point2i location11;//旋转后(6310*6310图片的坐标)
	float sinx=sinf(matchangle*PI/180);
	float cosx=cosf(matchangle*PI/180);
	location11.x=(location10.x)*cosx-(location10.y)*sinx+3155;//最后项为坐标偏移
	location11.y=(location10.x)*sinx+(location10.y)*cosx+3155;
	Rect box;//剪切结果区域
	box.x=location11.x-(int)(locationinfile[0].x/matchscale);//
	box.y=location11.y-(int)(locationinfile[0].y/matchscale);//
	box.width=xpcbmax/matchscale;
	box.height=ypcbmax/matchscale;
	Mat cutimageresult(pwnd->m_imageprocess.rotateimage,box);
	pwnd->m_imageprocess.GetHole(cutimageresult);
	DrawcvMat(cutimageresult,IDC_CAMIMG,1);*/







	



	//__________________________________________________________zns
/*	pwnd->m_pOpPaneWnd->m_pF1SubItem2View->inputcircles.clear();
	circlestruct   inputcircles1;
	if (theApp.mastprog.m_OriPosition==NULL)
	{
		MessageBox(_T("未导入文件"),_T("提示"),MB_OK);
		return ;
	}
	HoleInfoNode *curr=theApp.mastprog.m_OriPosition->pnext;
	int nummast=0;
	circlestruct  xmaxpoint,xminpoint,ymaxpoint,yminpoint;
	xmaxpoint.x=0;
	ymaxpoint.y=0;
	xminpoint.x=xpcbmax;
	yminpoint.y=ypcbmax;
	while(curr!=NULL)
	{
		//单位均转换为微米级
		inputcircles1.x=curr->position.nXs;
		inputcircles1.y=curr->position.nYs;
		inputcircles1.R=curr->position.diameter*500;
		pwnd->m_pOpPaneWnd->m_pF1SubItem2View->inputcircles.push_back(inputcircles1);
		if (inputcircles1.x>xmaxpoint.x)
		{
			xmaxpoint=inputcircles1;
		}
		if (inputcircles1.y>ymaxpoint.y)
		{
			ymaxpoint=inputcircles1;
		}
		if (inputcircles1.x<xminpoint.x)
		{
			xminpoint=inputcircles1;
		}
		if (inputcircles1.y>yminpoint.y)
		{
			yminpoint=inputcircles1;
		}
		curr=curr->pnext;
		nummast++;
	}
	if (nummast!=pwnd->m_pOpPaneWnd->m_pF1SubItem2View->inputcircles.size())
	{
    	MessageBox(_T("文件提取圆错误"),_T("错误"),MB_OK);
	}
	sort(pwnd->m_pOpPaneWnd->m_pF1SubItem2View->inputcircles.begin(),pwnd->m_pOpPaneWnd->m_pF1SubItem2View->inputcircles.end(),lessmark); 
	pwnd->m_imageprocess.GetHole(pwnd->m_camera.img);
	pwnd->m_imageprocess.contours;
	sort(pwnd->m_imageprocess.circles.begin(),pwnd->m_imageprocess.circles.end(),lessmark);*/
   /* pwnd->m_imageprocess.GetHole(pwnd->m_camera.img);
	sort(pwnd->m_imageprocess.contours.begin(),pwnd->m_imageprocess.contours.end(),maxsize);
	pwnd->m_imageprocess.contours;
	int xmax=0,ymax=0;
	Rect box;
	box.x=contours1[0][0].x;
	box.y=contours1[0][0].y;
	for(int i=0;i<contours1[0].size();i++)
	{
		if (contours1[0][i].x<box.x)
		{
			box.x=contours1[0][i].x;
		}
		if (contours1[0][i].y<box.y)
		{
			box.y=contours1[0][i].y;
		}
		if (contours1[0][i].x>xmax)
		{
			xmax=contours1[0][i].x;
		}
		if (contours1[0][i].y>ymax)
		{
			ymax=contours1[0][i].y;
		}

	}
	box.width=xmax-box.x;
	box.height=ymax-box.y;
	Mat cutimageresult2(pwnd->m_imageprocess.rotateimage,box);
	DrawcvMat(cutimageresult2,IDC_CAMIMG,1);
	//---------------------------------------------------------------------------------------zns
	//矫正算法：默认位置偏差不大
	/*circlestruct circle1,circle2;//加工文件上选取两个定位圆,单位微米
	circle1=pwnd->m_pOpPaneWnd->m_pF1SubItem2View->inputcircles[0];
	circle2=pwnd->m_pOpPaneWnd->m_pF1SubItem2View->inputcircles[pwnd->m_pOpPaneWnd->m_pF1SubItem2View->inputcircles.size()-1];
	circlestruct camcircle1,camcircle2;//摄像头采集图片上的定位圆
	camcircle1=pwnd->m_imageprocess.circles[0];//左上角的圆
	camcircle2=pwnd->m_imageprocess.circles[0];

	int angle=atanf((circle1.y-circle2.y)/(circle1.x-circle2.x))-atanf((camcircle1.y-camcircle2.y)/(camcircle1.x-camcircle2.x));
	Mat resultiamge;
	pwnd->m_imageprocess.ImageRotate(pwnd->m_camera.img,angle);

	//---------------------------------------------------------------------------------------
	pwnd->m_imageprocess.contours;
	//-------------------------------------------------------------图像的定位
	
	findContours(pwnd->m_imageprocess.rotateimage,contours1,CV_RETR_LIST,CV_CHAIN_APPROX_NONE);//提取的外轮廓
	int xmax=0,ymax=0;
	Rect box;
	box.x=contours1[0][0].x;
	box.y=contours1[0][0].y;
	for(int i=0;i<contours1[0].size();i++)
	{
	if (contours1[0][i].x<box.x)
	{
	box.x=contours1[0][i].x;
	}
	if (contours1[0][i].y<box.y)
	{
	box.y=contours1[0][i].y;
	}
	if (contours1[0][i].x>xmax)
	{
	xmax=contours1[0][i].x;
	}
	if (contours1[0][i].y>ymax)
	{
	ymax=contours1[0][i].y;
	}

	}
	box.width=xmax-box.x;
	box.height=ymax-box.y;
	Mat cutimageresult2(pwnd->m_imageprocess.rotateimage,box);
	DrawcvMat(cutimageresult2,IDC_CAMIMG,1);*/
	//-----------------------------------------------------------zns
/*	Rect box;//剪切结果区域widt
	box.x=0;
	box.y=0;
	box.width=4000;
	box.height=4000;
	Mat cutimageresult(pwnd->m_imageprocess.rotateimage,box);*/
//	DrawcvMat(cutimageresult,IDC_CAMIMG,1);
}


void CCameraImageView::OnBnClickedFocus()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CCameraImageView::OnBnClickedtest()
{
	// 跳转到测试用
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	pwnd->m_camera.img_sweep=imread("F:/bmp图/result.bmp",CV_LOAD_IMAGE_ANYDEPTH|CV_LOAD_IMAGE_ANYCOLOR);
	//Mat mat = imread( "F:/result.bmp",CV_LOAD_IMAGE_ANYDEPTH|CV_LOAD_IMAGE_ANYCOLOR );
	pwnd->m_imageprocess.GetHole(pwnd->m_camera.img_sweep);
	
	//DrawcvMat(	pwnd->m_camera.img_sweep,IDC_CAMIMG,1);
	m_camimg.m_bActive=1;
	m_camimg.ShowImage(pwnd->m_camera.img_sweep,0);
}

void CCameraImageView::DrawcvMat(Mat mat, UINT ID,bool flag)//显示mat在picture控件中
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
	// 将图片绘制到显示控件的指定区域内
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

void CCameraImageView::OnLButtonDown(UINT nFlags, CPoint point)
{
	//CClientDC dc(this);
	//OnPrepareDC(&dc,NULL);
	//dc.DPtoLP(&point);

	ASSERT(m_camimg);
	m_camimg.OnLButtonDown(nFlags,point);
	CView::OnLButtonDown(nFlags, point);
}

void CCameraImageView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc,NULL);
	dc.DPtoLP(&point);

	ASSERT(m_camimg);
	m_camimg.OnLButtonUp(nFlags,point);
	CView::OnLButtonUp(nFlags, point);
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
