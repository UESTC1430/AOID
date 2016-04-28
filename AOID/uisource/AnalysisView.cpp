// AnalysisView.cpp : 实现文件
//

#include "stdafx.h"
#include "AOID.h"
#include "AnalysisView.h"
#include <atlimage.h>

// CAnalysisView

IMPLEMENT_DYNCREATE(CAnalysisView, CFormView)

CAnalysisView::CAnalysisView()
	: CFormView(CAnalysisView::IDD)
{

}

CAnalysisView::~CAnalysisView()
{
}

void CAnalysisView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAnalysisView, CFormView)

	ON_BN_CLICKED(IDC_BUTTON1, &CAnalysisView::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAnalysisView::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CAnalysisView::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CAnalysisView::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_Radar, &CAnalysisView::OnRadar)
END_MESSAGE_MAP()


// CAnalysisView 诊断

#ifdef _DEBUG
void CAnalysisView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAnalysisView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

// CAnalysisView 消息处理程序
void CAnalysisView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
}





void CAnalysisView::OnRadar()
{

	// TODO: Add your control notification handler code here
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	CWnd *pWin = GetDlgItem(IDC_RADARCHART);
	CClientDC m_rectrader(pWin);
	pWin->GetClientRect(radarrect);
	int xcenter=radarrect.Width()/2;
	int ycenter=radarrect.Height()/2;
	m_radarpoint.clear();
	CImage imag;
	imag.Create( radarrect.Width(),radarrect.Height(),32);
	
	//------------------------------------------------雷达图的绘制
	m_rectrader.RoundRect(radarrect.left,radarrect.top,radarrect.right,radarrect.bottom,0,0);//画矩形框
	int n=6;//需要几个圈
	float step;
	if (radarrect.Width()>radarrect.Height())
		step=radarrect.Height()/(2*n);
	else
		step=radarrect.Width()/(2*n);
	for(int i=n;i>0;i--)
	{
        m_rectrader.Ellipse((radarrect.Width()/2-i*step),(radarrect.Height()/2-i*step),(radarrect.Width()/2+i*step),(radarrect.Height()/2+i*step));//画同心圆
	}
	m_rectrader.MoveTo(radarrect.Width()/2,0);
	m_rectrader.LineTo(radarrect.Width()/2,radarrect.Height());
	m_rectrader.MoveTo(0,radarrect.Height()/2);
	m_rectrader.LineTo(radarrect.Width(),radarrect.Height()/2);//画十字

	//****************************************************************************
/*	m_circlematching.clear();
	circlenumincam=pwnd->m_imageprocess.circles.size();
	for (int i=0;i<circlenumincam;i++)
	{
		radarpoint.R=pwnd->m_imageprocess.circles[i].R*matchscale;
		radarpoint.x=pwnd->m_imageprocess.circles[i].x*matchscale+pwnd->m_pOpPaneWnd->m_pF3SubItem1View->xpcbmin;
		radarpoint.y=pwnd->m_imageprocess.circles[i].y*matchscale+pwnd->m_pOpPaneWnd->m_pF3SubItem1View->ypcbmin;
		m_radarpoint.push_back(radarpoint);//m_radarpoint存放图片信息

	}
	circlenuminfile=0;
	if (NULL==theApp.mastprog.m_OriPosition)
		return ;
	HoleInfoNode *pnode;
	pnode = theApp.mastprog.m_OriPosition->pnext;//pnode存放加工文件信息
	int a[100];
	for (int i=0;i<100;i++)
	{
		a[i]=0;
	}
	//---------------------------------------------------------------------
	//精度达到100um即可的条件下已加工文件为基准找对应圆
	while(pnode)
	{
		circlenuminfile++;
		int x0,x1,y0,y1,d,m=-1;
		bool ALD=0;
		d=pnode->position.diameter;
		x0=pnode->position.nXs-d;
		x1=pnode->position.nXs+d;
		y0=pnode->position.nYs-d;
		y1=pnode->position.nYs+d;
		circlestruct end,temp;
		for (int i=0;i<circlenumincam;i++)
		{
			if (a[i]==1)
			{
				continue;
			}
			if (m_radarpoint[i].x>x0&&m_radarpoint[i].x<x1&&m_radarpoint[i].y>y0&&m_radarpoint[i].y<y1)
			{
				if (ALD==1)
				{
					temp=m_radarpoint[i];
					if (((temp.x)-(pnode->position.nXs))*((temp.x)-(pnode->position.nXs))+((temp.y)-(pnode->position.nYs))*((temp.y)-(pnode->position.nYs))<
						((end.x)-(pnode->position.nXs))*((end.x)-(pnode->position.nXs))+((end.y)-(pnode->position.nYs))*((end.y)-(pnode->position.nYs)))
					{
						end=temp;
						m=i;
					}

				}
				else
				{
					ALD=1;
				    end=m_radarpoint[i];
					m=i;
				}
			}
	    }		
		if (m!=-1)
		{
			a[m]=1;
			temp_circlematch.circleincam=pwnd->m_imageprocess.circles[m];
			temp_circlematch.circleinfile.x=pnode->position.nXs;
			temp_circlematch.circleinfile.y=pnode->position.nYs;
			temp_circlematch.circleinfile.R=d/2;
			temp_circlematch.x_off=end.x-pnode->position.nXs;
			temp_circlematch.y_off=end.y-pnode->position.nYs;
			temp_circlematch.R_off=end.R-d/2;
			m_circlematching.push_back(temp_circlematch);
		}
		pnode=pnode->pnext;
	}
	int cnum=m_circlematching.size();
	//**********************************************************匹配完成，精确定位
	if (true==pwnd->m_imageprocess.HighQualityLocation(m_circlematching,matchangle,matchscale))
	{	
		pwnd->m_imageprocess.ImageRotate(pwnd->m_imageprocess.rotateimage,pwnd->m_imageprocess.rotateimage2,matchangle);
	

	//------------------------------------------------------------------------旋转正确后进行的对比
	
	//找到旋转后的第一定位点
	//旋转图片的大小为6310*6310，中心（3155，3155）
	Point2i rotato;
	rotato.x=(m_circlematching[0].circleincam.x+m_circlematching[1].circleincam.x+m_circlematching[2].circleincam.x+m_circlematching[3].circleincam.x)/4;
	rotato.y=(m_circlematching[0].circleincam.y+m_circlematching[1].circleincam.y+m_circlematching[3].circleincam.y+m_circlematching[3].circleincam.y)/4;

	Point2i rotatofile;
	rotatofile.x=(m_circlematching[0].circleinfile.x+m_circlematching[1].circleinfile.x+m_circlematching[2].circleinfile.x+m_circlematching[3].circleinfile.x)/4;
	rotatofile.y=(m_circlematching[0].circleinfile.y+m_circlematching[1].circleinfile.y+m_circlematching[2].circleinfile.y+m_circlematching[3].circleinfile.y)/4;

	Point2i location10;//存放中心点
	location10.x=rotato.x-pwnd->m_imageprocess.resultimage.cols/2;
	location10.y=rotato.y-pwnd->m_imageprocess.resultimage.rows/2;//相对图片中心点的坐标
	Point2i location11;//旋转后(6310*6310图片的坐标)
	float sinx=sinf(matchangle*PI/180);
	float cosx=cosf(matchangle*PI/180);
	float m_temp=pwnd->m_imageprocess.resultimage.rows*pwnd->m_imageprocess.resultimage.rows+pwnd->m_imageprocess.resultimage.cols*pwnd->m_imageprocess.resultimage.cols;
	int XY_off=sqrt(m_temp)/2;
	location11.x=(location10.x)*cosx+(location10.y)*sinx+XY_off;//最后项为坐标偏移
	location11.y=(location10.y)*cosx-(location10.x)*sinx+XY_off;
	Rect box;//剪切结果区域
	box.x=location11.x-(int)((rotatofile.x-pwnd->m_pOpPaneWnd->m_pF3SubItem1View->xpcbmin)/matchscale);
	box.y=location11.y-(int)((rotatofile.y-pwnd->m_pOpPaneWnd->m_pF3SubItem1View->ypcbmin)/matchscale);
	box.width=(pwnd->m_pOpPaneWnd->m_pF3SubItem1View->xpcbmax-pwnd->m_pOpPaneWnd->m_pF3SubItem1View->xpcbmin)/matchscale;
	box.height=(pwnd->m_pOpPaneWnd->m_pF3SubItem1View->ypcbmax-pwnd->m_pOpPaneWnd->m_pF3SubItem1View->ypcbmin)/matchscale;
	Mat cutimageresult(pwnd->m_imageprocess.rotateimage2,box);
	pwnd->m_imageprocess.GetHole(cutimageresult);
	}
	//******************************************************************************************************************
	
	m_circlematching.clear();
	circlenumincam=pwnd->m_imageprocess.circles.size();
	for (int i=0;i<circlenumincam;i++)
	{
		radarpoint.R=pwnd->m_imageprocess.circles[i].R*matchscale;
		radarpoint.x=pwnd->m_imageprocess.circles[i].x*matchscale+pwnd->m_pOpPaneWnd->m_pF3SubItem1View->xpcbmin;
		radarpoint.y=pwnd->m_imageprocess.circles[i].y*matchscale+pwnd->m_pOpPaneWnd->m_pF3SubItem1View->ypcbmin;
		m_radarpoint.push_back(radarpoint);//m_radarpoint存放图片信息

	}
	circlenuminfile=0;
	if (NULL==theApp.mastprog.m_OriPosition)
		return ;
	pnode = theApp.mastprog.m_OriPosition->pnext;//pnode存放加工文件信息
	int b[100];
	for (int i=0;i<100;i++)
	{
		b[i]=0;
	}
	//---------------------------------------------------------------------
	//精度达到100um即可的条件下已加工文件为基准找对应圆
	while(pnode)
	{
		circlenuminfile++;
		int x0,x1,y0,y1,d,m=-1;
		bool ALD=0;
		d=pnode->position.diameter;
		x0=pnode->position.nXs-2*d;
		x1=pnode->position.nXs+2*d;
		y0=pnode->position.nYs-2*d;
		y1=pnode->position.nYs+2*d;
		circlestruct end,temp;
		for (int i=0;i<circlenumincam;i++)
		{
			if (b[i]==1)
			{
				continue;
			}
			if (m_radarpoint[i].x>x0&&m_radarpoint[i].x<x1&&m_radarpoint[i].y>y0&&m_radarpoint[i].y<y1)
			{
				if (ALD==1)
				{
					temp=m_radarpoint[i];
					if (((temp.x)-(pnode->position.nXs))*((temp.x)-(pnode->position.nXs))+((temp.y)-(pnode->position.nYs))*((temp.y)-(pnode->position.nYs))<
						((end.x)-(pnode->position.nXs))*((end.x)-(pnode->position.nXs))+((end.y)-(pnode->position.nYs))*((end.y)-(pnode->position.nYs)))
					{
						end=temp;
						m=i;
					}

				}
				else
				{
					ALD=1;
					end=m_radarpoint[i];
					m=i;
				}
			}
		}		
		if (m!=-1)
		{
			b[m]=1;
			temp_circlematch.circleincam=end;
			temp_circlematch.circleinfile.x=pnode->position.nXs;
			temp_circlematch.circleinfile.y=pnode->position.nYs;
			temp_circlematch.circleinfile.R=d/2;
			temp_circlematch.x_off=end.x-pnode->position.nXs;
			temp_circlematch.y_off=end.y-pnode->position.nYs;
			temp_circlematch.R_off=end.R-d/2;
			m_circlematching.push_back(temp_circlematch);
		}
		pnode=pnode->pnext;
	}

*/
    int  cnum=m_circlematching.size();

	for (int i=0;i<cnum;i++)
	{
		int x=(m_circlematching[i].x_off*step)/1000+xcenter;
		int y=(m_circlematching[i].y_off*step)/1000+ycenter;
		m_rectrader.SetPixel(x,y,RGB(0,0,255));
		m_rectrader.SetPixel(x-1,y,RGB(0,0,255));
		m_rectrader.SetPixel(x+1,y,RGB(0,0,255));
		m_rectrader.SetPixel(x,y-1,RGB(0,0,255));
		m_rectrader.SetPixel(x,y+1,RGB(0,0,255));
	}
//-----------------------------------------------------------------测试画图的读出
	/*CDC	memDC;
	memDC.CreateCompatibleDC(&m_rectrader);
	int Width = radarrect.Width();
	int Height = radarrect.Height();
	int iBits; //当前显示分辨率下每个像素所占字节数
	WORD wBitCount; ////位图中每个像素所占字节数
	DWORD dwPaletteSize=0, dwBmBitsSize;//定义调色板大小，位图中像素字节大小
	CBitmap m_bitmap;
	m_bitmap.CreateCompatibleBitmap(&m_rectrader, Width, Height);*/
	::BitBlt(imag.GetDC(), 0,0,radarrect.Width(),radarrect.Height(), m_rectrader.m_hDC,0,0,SRCCOPY );
	imag.Save("F://AOID/AOID/雷达图.bmp");
	ReleaseDC( &m_rectrader);
	imag.ReleaseDC();
	//------------------------------------------------------------
}


void CAnalysisView::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	Mat   cut_2;
	m_circlematching.clear();
	m_radarpoint.clear();
	circlenumincam=pwnd->m_imageprocess.circles.size();
	for (int i=0;i<circlenumincam;i++)
	{
		radarpoint.R=pwnd->m_imageprocess.circles[i].R*matchscale;
		radarpoint.x=pwnd->m_imageprocess.circles[i].x*matchscale+pwnd->m_pOpPaneWnd->m_pF3SubItem1View->xpcbmin;
		radarpoint.y=pwnd->m_imageprocess.circles[i].y*matchscale+pwnd->m_pOpPaneWnd->m_pF3SubItem1View->ypcbmin;
		m_radarpoint.push_back(radarpoint);//m_radarpoint存放图片信息

	}
	circlenuminfile=0;
	if (NULL==theApp.mastprog.m_OriPosition)
		return ;
	HoleInfoNode *pnode;
	pnode = theApp.mastprog.m_OriPosition->pnext;//pnode存放加工文件信息
	int a[100];
	for (int i=0;i<100;i++)
	{
		a[i]=0;
	}
	//---------------------------------------------------------------------
	//精度达到100um即可的条件下已加工文件为基准找对应圆
	while(pnode)
	{
		if (pnode->position.diameter<2000)
		{
			pnode=pnode->pnext;
			continue;
		}
		circlenuminfile++;
		int x0,x1,y0,y1,d,m=-1;
		bool ALD=0;
		d=pnode->position.diameter;
		x0=pnode->position.nXs-2*d;
		x1=pnode->position.nXs+2*d;
		y0=pnode->position.nYs-2*d;
		y1=pnode->position.nYs+2*d;
		circlestruct end,temp;
		for (int i=0;i<circlenumincam;i++)
		{
			if (m_radarpoint[i].x>x0&&m_radarpoint[i].x<x1&&m_radarpoint[i].y>y0&&m_radarpoint[i].y<y1)
			{
				if (ALD==1)
				{
					temp=m_radarpoint[i];
					if (((temp.x)-(pnode->position.nXs))*((temp.x)-(pnode->position.nXs))+((temp.y)-(pnode->position.nYs))*((temp.y)-(pnode->position.nYs))<
						((end.x)-(pnode->position.nXs))*((end.x)-(pnode->position.nXs))+((end.y)-(pnode->position.nYs))*((end.y)-(pnode->position.nYs)))
					{
						end=temp;
						m=i;
					}

				}
				else
				{
					ALD=1;
				    end=m_radarpoint[i];
					m=i;
				}
			}
	    }		
		if (m!=-1)
		{
			a[m]++;
			temp_circlematch.circleincam=pwnd->m_imageprocess.circles[m];
			temp_circlematch.circleinfile.x=pnode->position.nXs;
			temp_circlematch.circleinfile.y=pnode->position.nYs;
			temp_circlematch.circleinfile.R=d/2;
			temp_circlematch.x_off=end.x-pnode->position.nXs;
			temp_circlematch.y_off=end.y-pnode->position.nYs;
			temp_circlematch.R_off=end.R-d/2;
			m_circlematching.push_back(temp_circlematch);
		}
		pnode=pnode->pnext;
	}
	int cnum=m_circlematching.size();
	//**********************************************************匹配完成，精确定位2015.12.21
	if (true==pwnd->m_imageprocess.HighQualityLocation3(m_circlematching,matchangle,matchscale))
	{	
		/*imwrite("G:/cut_1_1.bmp",pwnd->m_imageprocess.cut_1);
		pwnd->m_imageprocess.ImageRotate(pwnd->m_imageprocess.cut_1,pwnd->m_imageprocess.rotateimage2,matchangle);
		imwrite("G:/cut_2_1.bmp",pwnd->m_imageprocess.rotateimage2);
	//------------------------------------------------------------------------旋转正确后进行的对比
	double m_temp=(double)pwnd->m_imageprocess.cut_1.rows*(double)pwnd->m_imageprocess.cut_1.rows+(double)pwnd->m_imageprocess.cut_1.cols*(double)pwnd->m_imageprocess.cut_1.cols;
	int XY_off=sqrt(m_temp)/2;
	Rect box;//剪切结果区域
	box.width=(pwnd->m_pOpPaneWnd->m_pF3SubItem1View->xpcbmax-pwnd->m_pOpPaneWnd->m_pF3SubItem1View->xpcbmin)/matchscale;
	box.height=(pwnd->m_pOpPaneWnd->m_pF3SubItem1View->ypcbmax-pwnd->m_pOpPaneWnd->m_pF3SubItem1View->ypcbmin)/matchscale;
	box.x=XY_off-(box.width)/2;
	box.y=XY_off-(box.height)/2;
	Mat cutimageresult(pwnd->m_imageprocess.rotateimage2,box);
	cutimageresult.copyTo(cut_2);
	imwrite("G:/cut_2.bmp",cutimageresult);
	pwnd->m_imageprocess.GetHole(cutimageresult);*/
		pwnd->m_imageprocess.ImageCutAndRotate(pwnd->m_imageprocess.cut_1,pwnd->m_imageprocess.rotateimage2,matchangle,matchscale,m_circlematching,pwnd->m_pOpPaneWnd->m_pF3SubItem1View->xpcbmin,pwnd->m_pOpPaneWnd->m_pF3SubItem1View->ypcbmin,pwnd->m_pOpPaneWnd->m_pF3SubItem1View->xpcbmax,pwnd->m_pOpPaneWnd->m_pF3SubItem1View->ypcbmax);
		imwrite("F://AOID/AOID/cut_2.bmp",pwnd->m_imageprocess.rotateimage2);
		pwnd->m_imageprocess.GetHole(pwnd->m_imageprocess.rotateimage2);
	}
	//******************************************************************************************************************测试2015.12.21
	
	m_circlematching.clear();
	m_radarpoint.clear();
	circlenumincam=pwnd->m_imageprocess.circles.size();
	for (int i=0;i<circlenumincam;i++)
	{
		radarpoint.R=pwnd->m_imageprocess.circles[i].R*matchscale;
		radarpoint.x=pwnd->m_imageprocess.circles[i].x*matchscale+pwnd->m_pOpPaneWnd->m_pF3SubItem1View->xpcbmin;
		radarpoint.y=pwnd->m_imageprocess.circles[i].y*matchscale+pwnd->m_pOpPaneWnd->m_pF3SubItem1View->ypcbmin;
		m_radarpoint.push_back(radarpoint);//m_radarpoint存放图片信息

	}
	circlenuminfile=0;
	if (NULL==theApp.mastprog.m_OriPosition)
		return ;
	pnode = theApp.mastprog.m_OriPosition->pnext;//pnode存放加工文件信息
	int b[100];
	for (int i=0;i<100;i++)
	{
		b[i]=0;
	}
	//---------------------------------------------------------------------
	//精度达到100um即可的条件下已加工文件为基准找对应圆
	while(pnode)
	{
		circlenuminfile++;
		int x0,x1,y0,y1,d,m=-1;
		bool ALD=0;
		d=pnode->position.diameter;
		x0=pnode->position.nXs-2*d;
		x1=pnode->position.nXs+2*d;
		y0=pnode->position.nYs-2*d;
		y1=pnode->position.nYs+2*d;
		circlestruct end,temp;
		for (int i=0;i<circlenumincam;i++)
		{
			if (m_radarpoint[i].x>x0&&m_radarpoint[i].x<x1&&m_radarpoint[i].y>y0&&m_radarpoint[i].y<y1)
			{
				if (ALD==1)
				{
					temp=m_radarpoint[i];
					if (((temp.x)-(pnode->position.nXs))*((temp.x)-(pnode->position.nXs))+((temp.y)-(pnode->position.nYs))*((temp.y)-(pnode->position.nYs))<
						((end.x)-(pnode->position.nXs))*((end.x)-(pnode->position.nXs))+((end.y)-(pnode->position.nYs))*((end.y)-(pnode->position.nYs)))
					{
						end=temp;
						m=i;
					}

				}
				else
				{
					ALD=1;
					end=m_radarpoint[i];
					m=i;
				}
			}
		}		
		if (m!=-1)
		{
			b[m]++;
			temp_circlematch.circleincam=pwnd->m_imageprocess.circles[m];
			temp_circlematch.circleinfile.x=pnode->position.nXs;
			temp_circlematch.circleinfile.y=pnode->position.nYs;
			temp_circlematch.circleinfile.R=d/2;
			temp_circlematch.x_off=end.x-pnode->position.nXs;
			temp_circlematch.y_off=end.y-pnode->position.nYs;
			temp_circlematch.R_off=end.R-d/2;
			m_circlematching.push_back(temp_circlematch);
		}
		pnode=pnode->pnext;
	}
	//*******************************************************************第三次定位
	 cnum=m_circlematching.size();
	//**********************************************************匹配完成，精确定位2015.12.21
	if (true==pwnd->m_imageprocess.HighQualityLocation3(m_circlematching,matchangle,matchscale))
	{	
		/*imwrite("G:/cut_2.bmp",cut_2);
		pwnd->m_imageprocess.ImageRotate(cut_2,pwnd->m_imageprocess.rotateimage3,matchangle);
		imwrite("G:/3.bmp",pwnd->m_imageprocess.rotateimage3);
	//------------------------------------------------------------------------旋转正确后进行的对比
	double m_temp3=(double)cut_2.rows*(double)cut_2.rows+(double)cut_2.cols*(double)cut_2.cols;
	int XY_off3=sqrt(m_temp3)/2;
	Rect box3;//剪切结果区域
	box3.width=(pwnd->m_pOpPaneWnd->m_pF3SubItem1View->xpcbmax-pwnd->m_pOpPaneWnd->m_pF3SubItem1View->xpcbmin)/matchscale;
	box3.height=(pwnd->m_pOpPaneWnd->m_pF3SubItem1View->ypcbmax-pwnd->m_pOpPaneWnd->m_pF3SubItem1View->ypcbmin)/matchscale;
	box3.x=XY_off3-(box3.width)/2;
	box3.y=XY_off3-(box3.height)/2;
	Mat cutimageresult3(pwnd->m_imageprocess.rotateimage3,box3);
	imwrite("G:/cut_3.bmp",cutimageresult3);
	pwnd->m_imageprocess.GetHole(cutimageresult3);*/
		pwnd->m_imageprocess.ImageCutAndRotate(pwnd->m_imageprocess.rotateimage2,pwnd->m_imageprocess.rotateimage3,matchangle,matchscale,m_circlematching,pwnd->m_pOpPaneWnd->m_pF3SubItem1View->xpcbmin,pwnd->m_pOpPaneWnd->m_pF3SubItem1View->ypcbmin,pwnd->m_pOpPaneWnd->m_pF3SubItem1View->xpcbmax,pwnd->m_pOpPaneWnd->m_pF3SubItem1View->ypcbmax);
		imwrite("F://AOID/AOID/cut_3.bmp",pwnd->m_imageprocess.rotateimage3);
		pwnd->m_imageprocess.GetHole(pwnd->m_imageprocess.rotateimage3);
	}
	//******************************************************************************************************************测试2015.12.21
	
	m_circlematching.clear();
	m_radarpoint.clear();
	circlenumincam=pwnd->m_imageprocess.circles.size();
	for (int i=0;i<circlenumincam;i++)
	{
		radarpoint.R=pwnd->m_imageprocess.circles[i].R*matchscale;
		radarpoint.x=pwnd->m_imageprocess.circles[i].x*matchscale+pwnd->m_pOpPaneWnd->m_pF3SubItem1View->xpcbmin;
		radarpoint.y=pwnd->m_imageprocess.circles[i].y*matchscale+pwnd->m_pOpPaneWnd->m_pF3SubItem1View->ypcbmin;
		m_radarpoint.push_back(radarpoint);//m_radarpoint存放图片信息

	}
	circlenuminfile=0;
	if (NULL==theApp.mastprog.m_OriPosition)
		return ;
	pnode = theApp.mastprog.m_OriPosition->pnext;//pnode存放加工文件信息
	int c[100];
	for (int i=0;i<100;i++)
	{
		c[i]=0;
	}
	//---------------------------------------------------------------------
	//精度达到100um即可的条件下已加工文件为基准找对应圆
	while(pnode)
	{
		circlenuminfile++;
		int x0,x1,y0,y1,d,m=-1;
		bool ALD=0;
		d=pnode->position.diameter;
		x0=pnode->position.nXs-2*d;
		x1=pnode->position.nXs+2*d;
		y0=pnode->position.nYs-2*d;
		y1=pnode->position.nYs+2*d;
		circlestruct end,temp;
		for (int i=0;i<circlenumincam;i++)
		{
			if (m_radarpoint[i].x>x0&&m_radarpoint[i].x<x1&&m_radarpoint[i].y>y0&&m_radarpoint[i].y<y1)
			{
				if (ALD==1)
				{
					temp=m_radarpoint[i];
					if (((temp.x)-(pnode->position.nXs))*((temp.x)-(pnode->position.nXs))+((temp.y)-(pnode->position.nYs))*((temp.y)-(pnode->position.nYs))<
						((end.x)-(pnode->position.nXs))*((end.x)-(pnode->position.nXs))+((end.y)-(pnode->position.nYs))*((end.y)-(pnode->position.nYs)))
					{
						end=temp;
						m=i;
					}

				}
				else
				{
					ALD=1;
					end=m_radarpoint[i];
					m=i;
				}
			}
		}		
		if (m!=-1)
		{
			c[m]++;
			temp_circlematch.circleincam=end;
			temp_circlematch.circleinfile.x=pnode->position.nXs;
			temp_circlematch.circleinfile.y=pnode->position.nYs;
			temp_circlematch.circleinfile.R=d/2;
			temp_circlematch.x_off=end.x-pnode->position.nXs;
			temp_circlematch.y_off=end.y-pnode->position.nYs;
			temp_circlematch.R_off=end.R-d/2;
			m_circlematching.push_back(temp_circlematch);
		}
		pnode=pnode->pnext;
	}

}


void CAnalysisView::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	Mat   cut_2;
	m_circlematching.clear();
	m_radarpoint.clear();
	circlenumincam=pwnd->m_imageprocess.circles.size();

	for (int i=0;i<circlenumincam;i++)
	{
		radarpoint.R=pwnd->m_imageprocess.circles[i].R*matchscale;
		radarpoint.x=pwnd->m_imageprocess.circles[i].x*matchscale+pwnd->m_pOpPaneWnd->m_pF3SubItem1View->xpcbmin;
		radarpoint.y=pwnd->m_imageprocess.circles[i].y*matchscale+pwnd->m_pOpPaneWnd->m_pF3SubItem1View->ypcbmin;
		m_radarpoint.push_back(radarpoint);//m_radarpoint存放图片信息

	}
	circlenuminfile=0;
	if (NULL==theApp.mastprog.m_OriPosition)
		return ;
	HoleInfoNode *pnode;
	pnode = theApp.mastprog.m_OriPosition->pnext;//pnode存放加工文件信息
	int a[100];
	for (int i=0;i<100;i++)
	{
		a[i]=0;
	}
	//---------------------------------------------------------------------
	//精度达到100um即可的条件下已加工文件为基准找对应圆
	while(pnode)
	{
		circlenuminfile++;
		int x0,x1,y0,y1,d,m=-1;
		bool ALD=0;
		d=pnode->position.diameter;
		x0=pnode->position.nXs-2*d;
		x1=pnode->position.nXs+2*d;
		y0=pnode->position.nYs-2*d;
		y1=pnode->position.nYs+2*d;
		circlestruct end,temp;
		for (int i=0;i<circlenumincam;i++)
		{
			if (m_radarpoint[i].x>x0&&m_radarpoint[i].x<x1&&m_radarpoint[i].y>y0&&m_radarpoint[i].y<y1)
			{
				if (ALD==1)
				{
					temp=m_radarpoint[i];
					if (((temp.x)-(pnode->position.nXs))*((temp.x)-(pnode->position.nXs))+((temp.y)-(pnode->position.nYs))*((temp.y)-(pnode->position.nYs))<
						((end.x)-(pnode->position.nXs))*((end.x)-(pnode->position.nXs))+((end.y)-(pnode->position.nYs))*((end.y)-(pnode->position.nYs)))
					{
						end=temp;
						m=i;
					}

				}
				else
				{
					ALD=1;
				    end=m_radarpoint[i];
					m=i;
				}
			}
	    }		
		if (m!=-1)
		{
			a[m]++;
			temp_circlematch.circleincam=pwnd->m_imageprocess.circles[m];
			temp_circlematch.circleinfile.x=pnode->position.nXs;
			temp_circlematch.circleinfile.y=pnode->position.nYs;
			temp_circlematch.circleinfile.R=d/2;
			temp_circlematch.x_off=end.x-pnode->position.nXs;
			temp_circlematch.y_off=end.y-pnode->position.nYs;
			temp_circlematch.R_off=end.R-d/2;
			m_circlematching.push_back(temp_circlematch);
		}
		pnode=pnode->pnext;
	}
	int cnum=m_circlematching.size();
	//**********************************************************
	float sum_matchscale=0,sum_matchangle=0,temp_ang=0,temp_sca=0;
	int sum=0;

	Point2f temp_infile,temp_incam;
	for (int i=0;i<cnum;i++)
	{
		if (m_circlematching[i].circleincam.R==750)
		{
	
			temp_infile.x=m_circlematching[i].circleinfile.x;
		    temp_infile.y=m_circlematching[i].circleinfile.y;
		    temp_incam.x=m_circlematching[i].circleincam.x;
		    temp_incam.y=m_circlematching[i].circleincam.y;
		    infile.push_back(temp_infile);
		    incam.push_back(temp_incam);
			sum++;
		}
	}
	Mat outputA;
	Mat fundamental_matrix=findFundamentalMat(incam,infile,FM_RANSAC,3,0.99,outputA);//求得基础矩阵
	int a1[100];
	for (int i=0;i<sum;i++)
	{
		a1[i]=outputA.at<unsigned char>(i,0);
	}
	Mat m_homography;
	cam_P.clear();
	Point2f temp;
	for (int i=0;i<circlenumincam;i++)
	{
		temp.x=pwnd->m_imageprocess.circles[i].x;
		temp.y=pwnd->m_imageprocess.circles[i].y;
		cam_P.push_back(temp);//m_radarpoint存放图片信息

	}
	m_homography=findHomography(incam,infile,CV_RANSAC,3,m);//返回值为变换矩阵
    perspectiveTransform(cam_P,camOut,m_homography);

	m_radarpoint.clear();
	m_circlematching.clear();
	int camout_num=camOut.size();
	for (int i=0;i<camout_num;i++)
	{
		circlestruct temp_cir;
		temp_cir.x=camOut[i].x;
		temp_cir.y=camOut[i].y;
		temp_cir.R=pwnd->m_imageprocess.circles[i].R*matchscale;
		m_radarpoint.push_back(temp_cir);
	}

	pnode = theApp.mastprog.m_OriPosition->pnext;//pnode存放加工文件信息
	int c[100];
	for (int i=0;i<100;i++)
	{
		c[i]=0;
	}
	//---------------------------------------------------------------------
	//精度达到100um即可的条件下已加工文件为基准找对应圆
	while(pnode)
	{
		int x0,x1,y0,y1,d,m=-1;
		bool ALD=0;
		d=pnode->position.diameter;
		x0=pnode->position.nXs-2*d;
		x1=pnode->position.nXs+2*d;
		y0=pnode->position.nYs-2*d;
		y1=pnode->position.nYs+2*d;
		circlestruct end,temp;
		for (int i=0;i<circlenumincam;i++)
		{
			if (m_radarpoint[i].x>x0&&m_radarpoint[i].x<x1&&m_radarpoint[i].y>y0&&m_radarpoint[i].y<y1)
			{
				if (ALD==1)
				{
					temp=m_radarpoint[i];
					if (((temp.x)-(pnode->position.nXs))*((temp.x)-(pnode->position.nXs))+((temp.y)-(pnode->position.nYs))*((temp.y)-(pnode->position.nYs))<
						((end.x)-(pnode->position.nXs))*((end.x)-(pnode->position.nXs))+((end.y)-(pnode->position.nYs))*((end.y)-(pnode->position.nYs)))
					{
						end=temp;
						m=i;
					}

				}
				else
				{
					ALD=1;
					end=m_radarpoint[i];
					m=i;
				}
			}
		}		
		if (m!=-1)
		{
			c[m]++;
			temp_circlematch.circleincam=end;
			temp_circlematch.circleinfile.x=pnode->position.nXs;
			temp_circlematch.circleinfile.y=pnode->position.nYs;
			temp_circlematch.circleinfile.R=d/2;
			temp_circlematch.x_off=end.x-pnode->position.nXs;
			temp_circlematch.y_off=end.y-pnode->position.nYs;
			temp_circlematch.R_off=end.R-d/2;
			m_circlematching.push_back(temp_circlematch);
		}
		pnode=pnode->pnext;
	}
	//******************************************************************************************************************测试2015.12.21
	 cnum=m_circlematching.size();
	//**********************************************************
/*	float sum_matchscale=0,sum_matchangle=0,temp_ang=0,temp_sca=0;
	int sum=0;

	Point2f temp_infile,temp_incam;
	for (int i=0;i<cnum;i++)
	{
		temp_infile.x=m_circlematching[i].circleinfile.x;
		temp_infile.y=m_circlematching[i].circleinfile.y;
		temp_incam.x=m_circlematching[i].circleincam.x;
		temp_incam.y=m_circlematching[i].circleincam.y;
		infile.push_back(temp_infile);
		incam.push_back(temp_incam);
	}
	Mat outputA;
	Mat fundamental_matrix=findFundamentalMat(infile,incam,FM_RANSAC,3,0.99,outputA);//求得基础矩阵
	int a1[100];
	for (int i=0;i<cnum;i++)
	{
		a1[i]=outputA.at<unsigned char>(i,0);
	}
	Mat m_homography;

	m_homography=findHomography(infile,incam,CV_RANSAC,3,m);//返回值为变换矩阵

	fileP.clear();
	pnode = theApp.mastprog.m_OriPosition->pnext;
	while(pnode)
	{
	   
	   pnode=pnode->pnext;
	}
	perspectiveTransform(pwnd->m_imageprocess.cut_1,pwnd->m_imageprocess.rotateimage2,m_homography);
	imwrite("G:/cut_2.bmp",pwnd->m_imageprocess.rotateimage2);
	pwnd->m_imageprocess.GetHole(pwnd->m_imageprocess.rotateimage2);
	
	//******************************************************************************************************************测试2015.12.21
	
	m_circlematching.clear();
	m_radarpoint.clear();
	circlenumincam=pwnd->m_imageprocess.circles.size();
	int b[100];
	while(pnode)
	{
		circlenuminfile++;
		int x0,x1,y0,y1,d,m=-1;
		bool ALD=0;
		d=pnode->position.diameter;
		x0=pnode->position.nXs-2*d;
		x1=pnode->position.nXs+2*d;
		y0=pnode->position.nYs-2*d;
		y1=pnode->position.nYs+2*d;
		circlestruct end,temp;
		for (int i=0;i<circlenumincam;i++)
		{
			if (m_radarpoint[i].x>x0&&m_radarpoint[i].x<x1&&m_radarpoint[i].y>y0&&m_radarpoint[i].y<y1)
			{
				if (ALD==1)
				{
					temp=m_radarpoint[i];
					if (((temp.x)-(pnode->position.nXs))*((temp.x)-(pnode->position.nXs))+((temp.y)-(pnode->position.nYs))*((temp.y)-(pnode->position.nYs))<
						((end.x)-(pnode->position.nXs))*((end.x)-(pnode->position.nXs))+((end.y)-(pnode->position.nYs))*((end.y)-(pnode->position.nYs)))
					{
						end=temp;
						m=i;
					}

				}
				else
				{
					ALD=1;
					end=m_radarpoint[i];
					m=i;
				}
			}
		}		
		if (m!=-1)
		{
			b[m]++;
			temp_circlematch.circleincam=pwnd->m_imageprocess.circles[m];
			temp_circlematch.circleinfile.x=pnode->position.nXs;
			temp_circlematch.circleinfile.y=pnode->position.nYs;
			temp_circlematch.circleinfile.R=d/2;
			temp_circlematch.x_off=end.x-pnode->position.nXs;
			temp_circlematch.y_off=end.y-pnode->position.nYs;
			temp_circlematch.R_off=end.R-d/2;
			m_circlematching.push_back(temp_circlematch);
		}
		pnode=pnode->pnext;
	}
	 cnum=m_circlematching.size();*/
}


void CAnalysisView::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	m_circlematching.clear();
	m_radarpoint.clear();
	circlenumincam=pwnd->m_imageprocess.circles.size();
	for (int i=0;i<circlenumincam;i++)
	{
		radarpoint.R=pwnd->m_imageprocess.circles[i].R*matchscale;
		radarpoint.x=pwnd->m_imageprocess.circles[i].x*matchscale+pwnd->m_pOpPaneWnd->m_pF3SubItem1View->xpcbmin;
		radarpoint.y=pwnd->m_imageprocess.circles[i].y*matchscale+pwnd->m_pOpPaneWnd->m_pF3SubItem1View->ypcbmin;
		m_radarpoint.push_back(radarpoint);//m_radarpoint存放图片信息

	}

	circlenuminfile=0;
	if (NULL==theApp.mastprog.m_OriPosition)
		return ;
	HoleInfoNode *pnode;
	pnode = theApp.mastprog.m_OriPosition->pnext;//pnode存放加工文件信息
	int a[100];
	for (int i=0;i<100;i++)
	{
		a[i]=0;
	}
	//---------------------------------------------------------------------
	//精度达到100um即可的条件下已加工文件为基准找对应圆
	while(pnode)
	{
		circlenuminfile++;
		int x0,x1,y0,y1,d,m=-1;
		bool ALD=0;
		d=pnode->position.diameter;
		x0=pnode->position.nXs-2*d;
		x1=pnode->position.nXs+2*d;
		y0=pnode->position.nYs-2*d;
		y1=pnode->position.nYs+2*d;
		circlestruct end,temp;
		for (int i=0;i<circlenumincam;i++)
		{
			if (m_radarpoint[i].x>x0&&m_radarpoint[i].x<x1&&m_radarpoint[i].y>y0&&m_radarpoint[i].y<y1)
			{
				if (ALD==1)
				{
					temp=m_radarpoint[i];
					if (((temp.x)-(pnode->position.nXs))*((temp.x)-(pnode->position.nXs))+((temp.y)-(pnode->position.nYs))*((temp.y)-(pnode->position.nYs))<
						((end.x)-(pnode->position.nXs))*((end.x)-(pnode->position.nXs))+((end.y)-(pnode->position.nYs))*((end.y)-(pnode->position.nYs)))
					{
						end=temp;
						m=i;
					}

				}
				else
				{
					ALD=1;
					end=m_radarpoint[i];
					m=i;
				}
			}
		}		
		if (m!=-1)
		{
			a[m]++;
			temp_circlematch.circleincam=pwnd->m_imageprocess.circles[m];
			temp_circlematch.circleinfile.x=pnode->position.nXs;
			temp_circlematch.circleinfile.y=pnode->position.nYs;
			temp_circlematch.circleinfile.R=d/2;
			temp_circlematch.x_off=end.x-pnode->position.nXs;
			temp_circlematch.y_off=end.y-pnode->position.nYs;
			temp_circlematch.R_off=end.R-d/2;
			m_circlematching.push_back(temp_circlematch);
		}
		pnode=pnode->pnext;
	}
}


void CAnalysisView::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	Mat test=imread("F:/bmp图/4点定位剪切图.bmp", CV_LOAD_IMAGE_ANYDEPTH|CV_LOAD_IMAGE_ANYCOLOR);
	m_circlematching.clear();
	m_radarpoint.clear();
	pwnd->m_imageprocess.GetHole(test);
	circlenumincam=pwnd->m_imageprocess.circles.size();
	matchscale=57.000;
	for (int i=0;i<circlenumincam;i++)
	{
		radarpoint.R=pwnd->m_imageprocess.circles[i].R*matchscale;
		radarpoint.x=pwnd->m_imageprocess.circles[i].x*matchscale+pwnd->m_pOpPaneWnd->m_pF3SubItem1View->xpcbmin;
		radarpoint.y=pwnd->m_imageprocess.circles[i].y*matchscale+pwnd->m_pOpPaneWnd->m_pF3SubItem1View->ypcbmin;
		m_radarpoint.push_back(radarpoint);//m_radarpoint存放图片信息

	}
	circlenuminfile=0;
	if (NULL==theApp.mastprog.m_OriPosition)
		return ;
	HoleInfoNode *pnode;
	pnode = theApp.mastprog.m_OriPosition->pnext;//pnode存放加工文件信息
	int a[100];
	for (int i=0;i<100;i++)
	{
		a[i]=0;
	}
	//---------------------------------------------------------------------
	//精度达到100um即可的条件下已加工文件为基准找对应圆
	while(pnode)
	{
		circlenuminfile++;
		if (1500!=pnode->position.diameter)
		{
			pnode=pnode->pnext;
			continue;
		}
		int x0,x1,y0,y1,d,m=-1;
		bool ALD=0;
		d=pnode->position.diameter;
		x0=pnode->position.nXs-2*d;
		x1=pnode->position.nXs+2*d;
		y0=pnode->position.nYs-2*d;
		y1=pnode->position.nYs+2*d;
		circlestruct end,temp;
		for (int i=0;i<circlenumincam;i++)
		{
			if (m_radarpoint[i].x>x0&&m_radarpoint[i].x<x1&&m_radarpoint[i].y>y0&&m_radarpoint[i].y<y1)
			{
				if (ALD==1)
				{
					temp=m_radarpoint[i];
					if (((temp.x)-(pnode->position.nXs))*((temp.x)-(pnode->position.nXs))+((temp.y)-(pnode->position.nYs))*((temp.y)-(pnode->position.nYs))<
						((end.x)-(pnode->position.nXs))*((end.x)-(pnode->position.nXs))+((end.y)-(pnode->position.nYs))*((end.y)-(pnode->position.nYs)))
					{
						end=temp;
						m=i;
					}

				}
				else
				{
					ALD=1;
					end=m_radarpoint[i];
					m=i;
				}
			}
		}		
		if (m!=-1)
		{
			a[m]++;
			temp_circlematch.circleincam=pwnd->m_imageprocess.circles[m];
			temp_circlematch.circleinfile.x=pnode->position.nXs;
			temp_circlematch.circleinfile.y=pnode->position.nYs;
			temp_circlematch.circleinfile.R=d/2;
			temp_circlematch.x_off=end.x-pnode->position.nXs;
			temp_circlematch.y_off=end.y-pnode->position.nYs;
			temp_circlematch.R_off=end.R-d/2;
			m_circlematching.push_back(temp_circlematch);
		}
		pnode=pnode->pnext;
	}
	int cnum=m_circlematching.size();
	pwnd->m_imageprocess.HighQualityLocation2(m_circlematching,matchangle,matchscale);
	Mat test_rotato;
	 pwnd->m_imageprocess.ImageRotate(test,test_rotato,matchangle);

	Point2f  temp_point_incam,temp_point_infile;
	temp_point_incam.x=0;
	temp_point_incam.y=0;
	temp_point_infile.x=0;
	temp_point_infile.y=0;
	for (int i=0;i<cnum;i++)
	{
		temp_point_incam.x+=m_circlematching[i].circleincam.x/cnum;
		temp_point_incam.y+=m_circlematching[i].circleincam.y/cnum;
		temp_point_infile.x+=m_circlematching[i].circleinfile.x/cnum;
		temp_point_infile.y+=m_circlematching[i].circleinfile.y/cnum;
	}

	Point2i location10,location11;//存放中心点
	location10.x=temp_point_incam.x-test_rotato.cols/2;
	location10.y=temp_point_incam.y-test_rotato.rows/2;//相对图片中心点的坐标
	//Point2i location11;//旋转后(6310*6310图片的坐标)
	float sinx=sinf(matchangle*PI/180);
	float cosx=cosf(matchangle*PI/180);
	float m_temp=test_rotato.rows*test_rotato.rows+test_rotato.cols*test_rotato.cols;
	int XY_off=sqrt(m_temp)/2;
	location11.x=(location10.x)*cosx+(location10.y)*sinx+XY_off;//最后项为坐标偏移
	location11.y=(location10.y)*cosx-(location10.x)*sinx+XY_off;
	Rect box;//剪切结果区域
	box.x=location11.x-(int)((temp_point_infile.x-pwnd->m_pOpPaneWnd->m_pF3SubItem1View->xpcbmin)/matchscale);
	box.y=location11.y-(int)((temp_point_infile.y-pwnd->m_pOpPaneWnd->m_pF3SubItem1View->ypcbmin)/matchscale);
	box.width=(pwnd->m_pOpPaneWnd->m_pF3SubItem1View->xpcbmax-pwnd->m_pOpPaneWnd->m_pF3SubItem1View->xpcbmin)/matchscale;
	box.height=(pwnd->m_pOpPaneWnd->m_pF3SubItem1View->ypcbmax-pwnd->m_pOpPaneWnd->m_pF3SubItem1View->ypcbmin)/matchscale;
	Mat cutimageresult(test_rotato,box);
	imwrite("F:/AOID/AOID/750定位剪切图.bmp",cutimageresult);
	pwnd->m_imageprocess.GetHole(cutimageresult);

	Mat test11=imread("G:/750定位剪切图.bmp", CV_LOAD_IMAGE_COLOR );
	Mat test2=imread("G:/750定位剪切图.bmp", CV_LOAD_IMAGE_COLOR );
	for(int i = 0; i < pwnd->m_imageprocess.circles.size(); i++)//把霍夫变换检测出的圆画出来
	{
		Point center(cvRound(pwnd->m_imageprocess.circles[i].x), cvRound(pwnd->m_imageprocess.circles[i].y));
		int radius = cvRound(pwnd->m_imageprocess.circles[i].R);
		circle( test11, center, radius, Scalar(0, 0, 255) );
		circle( test2, center, radius, Scalar(0, 0, 255),-1 );
	}

	imwrite("G:/750定位找圆.bmp",test11);
	imwrite("G:/750定位找圆_论文.bmp",test2);
	Mat test3=imread("G:/750定位剪切图.bmp", CV_LOAD_IMAGE_COLOR );
	Mat test4=imread("G:/750定位剪切图.bmp", CV_LOAD_IMAGE_COLOR );

	HoleInfoNode *curr3=theApp.mastprog.m_OriPosition->pnext;
	while(curr3!=NULL)
	{
		Point center(cvRound((curr3->position.nXs-pwnd->m_pOpPaneWnd->m_pF3SubItem1View->xpcbmin)/matchscale), cvRound((curr3->position.nYs-pwnd->m_pOpPaneWnd->m_pF3SubItem1View->ypcbmin)/matchscale));
		int radius = cvRound(((curr3->position.diameter)/2)/matchscale);
		circle( test3, center, radius, Scalar(0, 0, 255) );
		circle( test4, center, radius, Scalar(0, 0, 255),-1 );
		curr3=curr3->pnext;
	}
	imwrite("G:/750定位与加工文件.bmp",test3);
	imwrite("G:/750定位与加工文件_论文.bmp",test4);



}




void CAnalysisView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	int x,y;
	CPoint p;	
	p = point;
	startpoint = p;
	mouseexflag = true; //鼠标按下标记
	if (p.x>53&&p.x<310&&p.y>52&&p.y<390)
	{
		inrectchart=true;
	}
}


void CAnalysisView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	if(this->mouseexflag == true)
	{
		mouseexflag = false;
		int x,y;	
		float xscalepp,yscalepp;
		//求鼠标所在点在客户去中的坐标
		CPoint p;
		p = point;
		endpoint=p;
		if (true==inrectchart)
		{
			if(p.x>53&&p.x<310&&p.y>52&&p.y<390)
			{
				startpoint.x-=30;
				startpoint.y-=41;
				endpoint.x-=30;
				endpoint.y-=41;
				ProgInChart(startpoint,endpoint);  
			}
		}

	}
}


bool CAnalysisView::ProgInChart(CPoint start,CPoint end)
{
	int wide,height;
	wide = abs(start.x-end.x);
	height = abs(start.y-end.y);
	if (0!=wide&&0!=height)//选择的为区域
	{
		float xscalepp = wide*(1.0)/radarrect.Width();
		float yscalepp = height*(1.0)/radarrect.Height();

		return true;
	}
	return false;
}




