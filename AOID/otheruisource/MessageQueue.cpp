#include "stdafx.h"
#include "AOID.h"

#include "MessageQueue.h"
/////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
int MessageDisplay()
{
	CMainFrame *pwnd=(CMainFrame *)AfxGetMainWnd();
	if(!theApp.pwnd->errormsgqueue->IsMsgQueueEmpty())//������Ϣ���в�Ϊ��
	{
		if (theApp.pwnd->m_pProgPaneWnd!=NULL)
			theApp.pwnd->m_pProgPaneWnd->m_pProgressView->WarnMessage(theApp.pwnd->errormsgqueue->GetQueueFront().message,red);//��ʾ������Ϣ���ж���Ԫ��
		return 0;
	}
	if(!theApp.pwnd->warningmsgqueue->IsMsgQueueEmpty())//������Ϣ���в�Ϊ��
	{
		if (theApp.pwnd->m_pProgPaneWnd!=NULL)
			theApp.pwnd->m_pProgPaneWnd->m_pProgressView->WarnMessage(theApp.pwnd->warningmsgqueue->GetQueueFront().message,yellow);//��ʾ������Ϣ���ж���Ԫ��
		return 0;
	}
	if(!theApp.pwnd->operatemsgqueue->IsMsgQueueEmpty())//����������Ϣ���в�Ϊ��
	{
		if (theApp.pwnd->m_pProgPaneWnd!=NULL)
			theApp.pwnd->m_pProgPaneWnd->m_pProgressView->WarnMessage(theApp.pwnd->operatemsgqueue->GetQueueFront().message,green);//��ʾ������Ϣ���ж���Ԫ��
		return 0;
	}
	//--------��Ϣ��������Ϣ����ʾ������Ϣ������ӭ��
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





