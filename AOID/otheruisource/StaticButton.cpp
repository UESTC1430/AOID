// StaticButton.cpp : implementation file
//

#include "stdafx.h"
//#include "ReStart.h"
#include "StaticButton.h"
#include <winuser.h>
#include ".\staticbutton.h"
#include "mainfrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStaticButton


CRect CStaticButton::rect;

CStaticButton::CStaticButton(UINT iopnum)
{
	Enable = TRUE;

//	Select = CreateCursor(AfxGetInstanceHandle(), 4, 1, 32, 32, aaa, aaa);
	Select = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	No  = AfxGetApp()->LoadStandardCursor(IDC_NO);
	Region = new CRgn;
	//cTool = new CToolTipCtrl;
	ioptionbmpnum = iopnum;
	ieoptionbmpnum = iopnum;
	icuroptionnum = 0;
	iecuroptionnum = 0;

	icurbmpoption = 0;
	icuroption = 0;
	ipopsel = 0;
	m_phbitmap = new HBITMAP[ioptionbmpnum];
	m_phebitmap = new HBITMAP[ieoptionbmpnum];
	m_bgrey = FALSE;
	idelay = 0;


}

CStaticButton::~CStaticButton()
{
	delete Region;
//	delete cTool;
	delete m_phbitmap;
	delete m_phebitmap;
}


BEGIN_MESSAGE_MAP(CStaticButton, CStatic)
	//{{AFX_MSG_MAP(CStaticButton)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStaticButton message handlers

void CStaticButton::wSetBitmap(HBITMAP hBitmapUP, HBITMAP hBitmapDOWN, BOOL bAct, CRgn* rgn)
{
	Up		  = hBitmapUP;
	Down	  = hBitmapDOWN;
	bActive = bAct;

	if(bActive)
		SetBitmap(Up);
	else
		SetBitmap(Down);

	GetClientRect(rect);
	Region->CreateRectRgn(rect.left, rect.top, rect.right, rect.bottom);

	if(rgn)
		Region->CombineRgn(Region, rgn, RGN_AND);

//	if(cTool->Create(this, TTS_ALWAYSTIP | WS_POPUP | WS_EX_TOOLWINDOW))
//		SetToolTip("");

//	cTool->SetMaxTipWidth(150);
//	cTool->SetDelayTime(100);
}

HBITMAP CStaticButton::GetBitmapUp()
{
	return Up;
}
HBITMAP CStaticButton::GetBitmapDown()
{
	return Down;
}

BOOL CStaticButton::ChangeCursor(CPoint point)
{
	if(Region->PtInRegion((POINT)point))
	{
		if(Enable)
			::SetCursor(Select);
		else
			::SetCursor(No);
		return TRUE;
	}
	return FALSE;
}

void CStaticButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	/*if(ChangeCursor(point) && !bActive && Enable)
	{
		SetTimer(1, 50, NULL);
		SetBitmap(Up);
		bActive = TRUE;
	}
	else if(!ChangeCursor(point) && bActive)
	{
		KillTimer(1);
		SetBitmap(Down);
		bActive = FALSE;
	}

	CStatic::OnMouseMove(nFlags, point);
	*/
}

void CStaticButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if(nFlags == 1)
	{
		m_mousedown = 1;//鼠标按下此键
	}
	else
	{
		m_mousedown = 0;//按钮按下此键
	}
	if(m_bgrey == TRUE)
	{
		CStatic::OnLButtonDown(nFlags, point);
		return;
	}
	//if(((CMainFrame *)::AfxGetMainWnd())->iLangFlag == PUTILCH)
	//{
		//if(ipopsel<6)
		//{
   	//su	icuroption = ((icurbmpoption+2)%ioptionbmpnum)/2;
	//su		SetBitmap(m_phbitmap[icurbmpoption+1]);
	
		//}
//	}
	/*else
	{
			icuroption = ((icurbmpoption+2)%ioptionbmpnum)/2;
			SetBitmap(m_phebitmap[icurbmpoption+1]);
	}*/
	CStatic::OnLButtonDown(nFlags, point);	
}

void CStaticButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(this->m_mousedown==1&&this->idelay!=0)
	{
		return;
	}

	if(m_bgrey == TRUE)
	{
		m_bgrey = FALSE;
		CStatic::OnLButtonUp(nFlags, point);
		return;
	}
//	if(((CMainFrame *)::AfxGetMainWnd())->iLangFlag == PUTILCH)

	//su	icurbmpoption = (icurbmpoption+2)%ioptionbmpnum;
	//su	SetBitmap(m_phbitmap[icurbmpoption]);

/*	else
	{
		icurbmpoption = (icurbmpoption+2)%ioptionbmpnum;
		SetBitmap(m_phebitmap[icurbmpoption]);
	}
*/
	CStatic::OnLButtonUp(nFlags, point);
}



void CStaticButton::SetRegion(CRgn* rgn)
{
	if(Region)
	{
		delete Region;
		Region = new CRgn;
		Region->CreateRectRgn(rect.left, rect.top, rect.right, rect.bottom);
		Region->CombineRgn(Region, rgn, RGN_AND);
	}
}

CRgn* CStaticButton::GetRegion()
{
	return Region;
}

void CStaticButton::SetToolTip(LPSTR lpToolTip)
{
	//cTool->Activate(TRUE);
	//cTool->AddTool(this, lpToolTip);
}

BOOL CStaticButton::PreTranslateMessage(MSG* pMsg) 
{
//	cTool->RelayEvent(pMsg);	
	return CStatic::PreTranslateMessage(pMsg);
}

void CStaticButton::SetCursor(BOOL bSel, HCURSOR hCur)
{
	if(bSel)
		Select = hCur;
	else
		No = hCur;
}

HCURSOR CStaticButton::GetCursor(BOOL bSel)
{
	if(bSel)
		return Select;
	else
		return No;
}

void CStaticButton::SetEnable(BOOL B)
{ 
	Enable = B; 
	if(Enable)
		SetBitmap(Up);
	else
		SetBitmap(Down);
};

void CStaticButton::AppendBitmap(HBITMAP hBitmap)
{
	if(icuroptionnum<ioptionbmpnum)
	{
		icuroptionnum++;
		m_phbitmap[icuroptionnum-1] = hBitmap;
	}
	//for cnc add op
	if(ioptionbmpnum==2)
	{
		switch(icuroptionnum)
		{
		case 1:
			Up = hBitmap;
			break;
		case 2:
			Down = hBitmap;
			break;
		}
	}
	if(ioptionbmpnum==7)//add by su
	{
		switch(icuroptionnum)
		{
		case 1:
			FV1 = hBitmap;
			break;
		case 2:
			FV2 = hBitmap;
			break;
		case 3:
			FV3 = hBitmap;
			break;
		case 4:
			FV4 = hBitmap;
			break;
		case 5:
			FV5 = hBitmap;
			break;
		case 6:
			FV6 = hBitmap;
			break;
		case 7:
			FV7 = hBitmap;
			break;
		}
	}

}
void CStaticButton::AppendEBitmap(HBITMAP hBitmap)
{
	if(iecuroptionnum<ieoptionbmpnum)
	{
		iecuroptionnum++;
		m_phebitmap[iecuroptionnum-1] = hBitmap;
	}

	
}
void CStaticButton::InitRgn(CRgn * rgn)
{
	
	GetClientRect(&rect);
	
	Region->CreateRectRgn(rect.left, rect.top, rect.right, rect.bottom);

	if(rgn)
		Region->CombineRgn(Region, rgn, RGN_AND);

//	if(cTool->Create(this, TTS_ALWAYSTIP | WS_POPUP | WS_EX_TOOLWINDOW))
//	SetToolTip("");
//	cTool->SetMaxTipWidth(150);
//	cTool->SetDelayTime(100);
	
}



