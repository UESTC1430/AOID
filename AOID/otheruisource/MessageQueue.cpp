#include "stdafx.h"
#include "AOID.h"

#include "MessageQueue.h"
/////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
int MessageDisplay()
{
	CMainFrame *pwnd=(CMainFrame *)AfxGetMainWnd();
	if(!theApp.pwnd->errormsgqueue->IsMsgQueueEmpty())//报警信息队列不为空
	{
		if (theApp.pwnd->m_pProgPaneWnd!=NULL)
			theApp.pwnd->m_pProgPaneWnd->m_pProgressView->WarnMessage(theApp.pwnd->errormsgqueue->GetQueueFront().message,red);//显示报警信息队列队首元素
		return 0;
	}
	if(!theApp.pwnd->warningmsgqueue->IsMsgQueueEmpty())//警告信息队列不为空
	{
		if (theApp.pwnd->m_pProgPaneWnd!=NULL)
			theApp.pwnd->m_pProgPaneWnd->m_pProgressView->WarnMessage(theApp.pwnd->warningmsgqueue->GetQueueFront().message,yellow);//显示警告信息队列队首元素
		return 0;
	}
	if(!theApp.pwnd->operatemsgqueue->IsMsgQueueEmpty())//正常操作信息队列不为空
	{
		if (theApp.pwnd->m_pProgPaneWnd!=NULL)
			theApp.pwnd->m_pProgPaneWnd->m_pProgressView->WarnMessage(theApp.pwnd->operatemsgqueue->GetQueueFront().message,green);//显示警告信息队列队首元素
		return 0;
	}
	//--------消息队列无消息，显示正常信息：“欢迎”
	if (theApp.pwnd->m_pProgPaneWnd!=NULL)
		theApp.pwnd->m_pProgPaneWnd->m_pProgressView->WarnMessage("Welcome to CNC",white);		
	return 0;
}

int MessageProcess(int id)
{
	if (theApp.pwnd->errormsgqueue->IsMsgExist(id))
	{
		theApp.pwnd->errormsgqueue->DeleteMsgNode(id);
	}
	if (theApp.pwnd->warningmsgqueue->IsMsgExist(id))
	{
		theApp.pwnd->warningmsgqueue->DeleteMsgNode(id);
	}
	if (theApp.pwnd->operatemsgqueue->IsMsgExist(id))
	{
		theApp.pwnd->operatemsgqueue->DeleteMsgNode(id);
	}
	return 0;
}





