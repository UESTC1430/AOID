// ProgressView.cpp : 实现文件
//

#include "stdafx.h"
#include "AOID.h"
#include "ProgressView.h"


// CProgressView

IMPLEMENT_DYNCREATE(CProgressView, CFormView)

CProgressView::CProgressView()
	: CFormView(CProgressView::IDD)
{

}

CProgressView::~CProgressView()
{
}

void CProgressView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CProgressView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_SPACE, &CProgressView::OnButtonSpace)
END_MESSAGE_MAP()


// CProgressView 诊断

#ifdef _DEBUG
void CProgressView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CProgressView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


void CProgressView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	//m_pro.SetWindowText(progressstr);
	m_pro.SetBkColour(progresscol);
	m_pro.SetShowText(TRUE);}

// CProgressView 消息处理程序


void CProgressView::OnButtonSpace()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	pwnd->SPACEKEYDOWN();
}

bool CProgressView::WarnMessage(CString str,COLORREF col)
{
	if(m_pro)//窗口建立前已经产生报警信息，不通过此函数设置
	{
		m_pro.SetBkColour(col);
		//m_pro.SetWindowText(str);
		m_pro.SetShowText(TRUE);
	}
	else
	{
		progressstr=str;
		progresscol=col;
	}
	return true;
}


void CProgressView::DrillProgress(int currentnum,int totalnum)//打孔进度显示，参数 currentnum:当前正在打第几个孔；totalnum要执行打孔操作的总孔数
{
/*	int currentpos;
   	CString text;
	if(currentnum<totalnum)
	{
		currentpos=(currentnum*100)/totalnum;//当前进度条应在的位置
		m_pro.SetPos(currentpos);
		text.Format("%d",currentpos);
		text="打孔中"+text+"%";
	}
	else if(currentnum==totalnum)
	{
		currentpos=(currentnum*100)/totalnum;//当前进度条应在的位置
		m_pro.SetPos(currentpos);
		text="打孔结束";
	}
	else
		TRACE("已打孔数超过总孔数\n");*/ //su

  	CString text;
    text.Format("当前打了%d个孔",currentnum);
	m_pro.SetWindowText(text);	
	m_pro.SetShowText(TRUE);	
}
