
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "AOID.h"
#include "MainFrm.h"
#include "OpPaneWnd.h"
#include "menupanewnd.h"
#include "progpanewnd.h"
#include "toolpanewnd.h"


float matchscale;
float matchangle;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
END_MESSAGE_MAP()

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
	m_pOpPaneWnd=NULL;
	m_pMenuPaneWnd = NULL; 
	m_pProgPaneWnd = NULL;
	m_pToolPaneWnd = NULL;
	m_pInfoPaneWnd = NULL;
	int a=max(1,2);
	cmdviewflag=false;//初始化不显示cmdview
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2008);
	
	theApp.pwnd=this;
	m_pcncmessage = new CncMessage;
	m_pcnccmdmessage = new CncMessage;
	operatemsgqueue=new CShowMessage;
	warningmsgqueue=new CShowMessage;
	errormsgqueue=new CShowMessage;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}
//设置界面宽度
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	cs.cx= 1024;
	cs.cy=768;
	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	int widecol2=305;//第二列的宽度
	int highrow2=170;//第二行的高度（ infoview ）
	CRect rect;
	GetClientRect(&rect);
	if(m_wndSplitter1.CreateStatic(this,2,1)==NULL)//构建两行一列的切分窗口
		return FALSE;
	if(!m_wndSplitter1.CreateView(1,0,RUNTIME_CLASS(CInfoPaneWnd),CSize(rect.Width(),highrow2),pContext))
		return FALSE;
	m_wndSplitter1.SetRowInfo(0,rect.Height()-highrow2,0);//设置第一行的宽度
	if(NULL==m_wndSplitter2.CreateStatic(&m_wndSplitter1,2,2,WS_CHILD|WS_VISIBLE, m_wndSplitter1.IdFromRowCol(0, 0)))
        return FALSE; //将第0行0列 分成2行2列)
	 if(!m_wndSplitter2.CreateView(0,0,RUNTIME_CLASS(COpPaneWnd),CSize(rect.Width()-widecol2,475),pContext))
		return FALSE;
	
	if(!m_wndSplitter2.CreateView(0,1,RUNTIME_CLASS(CMenuPaneWnd),CSize(widecol2,475),pContext))
		return FALSE;
	
	if(!m_wndSplitter2.CreateView(1,0,RUNTIME_CLASS(CProgPaneWnd),CSize(rect.Width()-widecol2,rect.Height()-480-highrow2),pContext))
		return FALSE;
	
	if(!m_wndSplitter2.CreateView(1,1,RUNTIME_CLASS(CToolPaneWnd),CSize(widecol2,rect.Height()-480-highrow2),pContext))
		return FALSE;
	this->m_pOpPaneWnd   = (COpPaneWnd   *)m_wndSplitter2.GetPane(0,0);
	this->m_pMenuPaneWnd = (CMenuPaneWnd *)m_wndSplitter2.GetPane(0,1);	
	this->m_pProgPaneWnd = (CProgPaneWnd *)m_wndSplitter2.GetPane(1,0);
	this->m_pToolPaneWnd = (CToolPaneWnd *)m_wndSplitter2.GetPane(1,1);
	this->m_pInfoPaneWnd = (CInfoPaneWnd *)m_wndSplitter1.GetPane(1,0);

	this->m_pMenuPaneWnd->GetWindowRect(&rect);
	this->m_pMenuPaneWnd->GetWindowRect(&rect);
	return true;
}


void CMainFrame::ShowCmdView(bool flag)
{
	if(flag==true)
	{
		if(cmdviewflag==false)
		{
			m_CmdView.Create(IDD_CMDVIEW,NULL);
			m_CmdView.ShowWindow(SW_SHOW);
			m_pMenuPaneWnd->m_pProgView->HighLightFnButton(4);
			cmdviewflag=true;
		}		
	}
	else
	{
		if(cmdviewflag==true)
		{
			m_CmdView.DestroyWindow();
			cmdviewflag=false;
		}
		m_pMenuPaneWnd->m_pProgView->HighLightFnButton(m_pMenuPaneWnd->m_pProgView->fbtnnum);
	}
}

void CMainFrame::SPACEKEYDOWN()//空格键 功能   钻孔时暂停待完善
{
	//	SendMessage(WM_KEYDOWN,0,0);
	/*	m_pProgPaneWnd->m_pProgressView->m_pro.SetWindowText("Hello");
	UpdateData(FALSE);
	CString num;
	for(int i=0;i<100;i++)
	{
	m_pProgPaneWnd->m_pProgressView->m_pro.SetPos(i);
	m_pProgPaneWnd->m_pProgressView->m_pro.SetWindowText("初始化过程中");
	::Sleep(25);
	}	
	m_pProgPaneWnd->m_pProgressView->m_pro.SetPos(0);
	m_pProgPaneWnd->m_pProgressView->m_pro.SetWindowText("初始化完毕");
	m_pProgPaneWnd->m_pProgressView->m_pro.SetShowText(TRUE);*/
	// m_pOpPaneWnd->m_pF1SubItem2View->OnPause();//打孔时暂停
	
	
	
	
}

CncMessage::CncMessage()
{
	this->headnode.pnext = NULL;
	this->phead = &headnode;
	InitializeCriticalSection(&m_messageCriticalSection);
}

CncMessage::~CncMessage()
{
	MessageNode *pnode;
	while(phead->pnext)//释放未处理的结点
	{
		pnode = phead->pnext;
		phead->pnext = pnode->pnext;
		free(pnode);
		pnode=NULL;//0811
	}
}

bool CncMessage::SendMessage(MessageType message)
{
	MessageNode * psendnode;
	MessageNode * pnode;//链表指针的临时变量
	psendnode =(MessageNode *) malloc(sizeof(MessageNode));
	if(psendnode!=NULL)
	{
		psendnode->message = message;//？
		psendnode->message.messagecode = (char *)malloc(strlen(message.messagecode)+1);
		if(psendnode->message.messagecode!=NULL)
		{
			strcpy(psendnode->message.messagecode,message.messagecode);
			psendnode->pnext = NULL;
			pnode = phead;
			EnterCriticalSection(&m_messageCriticalSection);
			while(pnode->pnext)//找最后一个结点
			{
				pnode = pnode->pnext;
			}
			pnode->pnext = psendnode;
			LeaveCriticalSection(&m_messageCriticalSection);
		}
	}

	return true;

}

bool CncMessage::GetMessage(MessageType * pmessage)
{
	if(phead==NULL)
	{
		return false;
	}
	MessageNode *pnode=phead->pnext;
	if(pnode!=NULL)
	{

		EnterCriticalSection(&m_messageCriticalSection);
		(*pmessage).flagNeedCallback = pnode->message.flagNeedCallback;//将队首节点返回给传入的消息参数
		strcpy(pmessage->messagecode,pnode->message.messagecode);
		(*pmessage).imilisecond = pnode->message.imilisecond;
		(*pmessage).messageid = pnode->message.messageid;
		phead->pnext = pnode->pnext; //删除第一个结点
		LeaveCriticalSection(&m_messageCriticalSection);
		free(pnode->message.messagecode);
		pnode->message.messagecode=NULL;//0810
		free(pnode);
		pnode=NULL;//0810
		return true;
	}
	else
	{
		return false;
	}

}

void CncMessage::EmptyMessage()//删除了一个节点里面的内容
{
	//--------------------------------------------------
	MessageNode *pnode;
	MessageNode *pdeletenode;
	pnode = phead;
	//清空所有消息
	EnterCriticalSection(&m_messageCriticalSection);
	while(pnode->pnext)
	{
		pdeletenode = pnode->pnext;
		pnode->pnext = pdeletenode->pnext;		
		free(pdeletenode->message.messagecode);
		pdeletenode->message.messagecode=NULL;//0810
		free(pdeletenode);
		pdeletenode=NULL;//0810

	}
	LeaveCriticalSection(&m_messageCriticalSection);		
	phead->pnext = NULL;
	//	pdeletenode=NULL;
}

CShowMessage::CShowMessage()
{
	//this->headnode.pnext = NULL;
	this->firstnode = NULL;
}

CShowMessage::~CShowMessage()
{

}

int CShowMessage::MessagePush(MsgStruct *addnode)
{
	if (NULL==firstnode)
	{
		firstnode=addnode;
	}
	else
	{
		MsgStruct *tempnode=firstnode;
		while (tempnode->next!=NULL)
		{
			tempnode=tempnode->next;
		}
		tempnode->next=addnode;
	}	
	return 0;
}

MsgStruct CShowMessage::MessagePop()
{
	MsgStruct msgnode=*firstnode;
	firstnode=firstnode->next;
	return msgnode;
}

bool CShowMessage::IsMsgQueueEmpty()
{
	if (NULL==firstnode)
		return true;
	return false;
}

bool CShowMessage::IsMsgExist(int id)
{
	if (IsMsgQueueEmpty())
		return false;
	MsgStruct *tempnode=firstnode;
	while (tempnode!=NULL)
	{
		if (tempnode->messagegid==id)
		{
			return true;
		}
		tempnode=tempnode->next;
	}
	return false;
}

int CShowMessage::DeleteMsgNode(int id)
{
	if (IsMsgQueueEmpty())
		return -1;
	MsgStruct *curnode=firstnode;
	MsgStruct *prenode=NULL;
	MsgStruct *tempnode=NULL;
	while (curnode!=NULL)
	{
		if (curnode->messagegid==id)
		{
			if(prenode==NULL)
			{
				tempnode=firstnode;
				firstnode=firstnode->next;
			}
			else
			{
				prenode->next=curnode->next;
				tempnode=curnode;	
			}
			curnode=curnode->next;
			free(tempnode);
			tempnode=NULL;
		}
		else
		{
			prenode=curnode;
			curnode=curnode->next;
		}

	}
	return 0;
}

MsgStruct CShowMessage::GetQueueFront()
{
	MsgStruct msgnode=*firstnode;
	return msgnode;
}

int CShowMessage::MessageInsert(MsgStruct *addnode)
{
	if (NULL==addnode)
	{
		return -1;
	}
	if (NULL==firstnode)
	{
		firstnode=addnode;
	}
	else
	{
		addnode->next=firstnode;
		firstnode=addnode;
	}	
	return 0;

}
