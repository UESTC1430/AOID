#include "stdafx.h"
#include "CncControl.h"
#include<iostream> 
#include<fstream>
using namespace std; 

unsigned long m_msgID;
unsigned long m_WParam;
unsigned long m_LParam;

CncControl::CncControl(void)
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested=MAKEWORD(1,1);//
	err=WSAStartup(wVersionRequested,&wsaData);
	if(err!=0)
	{
		return;
	}

	if (LOBYTE(wsaData.wVersion)!=1||HIBYTE(wsaData.wVersion)!=1)
	{
		WSACleanup();
		return;
	}


	//创建套接字
	sockClient=socket(AF_INET, SOCK_STREAM, 0);
	if(INVALID_SOCKET == sockClient)	
	{
		MessageBox(NULL,_T("套接字创建失败！"),_T("错误"),MB_OK);
		return ;
	}	
	addrSrv.sin_addr.S_un.S_addr = inet_addr("192.168.1.200");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(4000);
}


CncControl::~CncControl(void)
{
}


bool CncControl::IniCncControl()
{
	if (SOCKET_ERROR==connect(sockClient,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR)))
	{
		MessageBox(NULL,_T("机床连接失败！"),_T("错误"),MB_OK);
		return FALSE;
	}
	else
	{
		MessageBox(NULL,_T("机床连接成功！"),_T("提示"),MB_OK);
	}
	send(sockClient,"ISOK", strlen("ISOK"), 0);
	return TRUE;
}

bool CncControl::Home()
{
	send(sockClient,"HOME", strlen("HOME"), 0);
	cnccondition.XPOS=0;
	cnccondition.YPOS=0;
	cnccondition.ZPOS=0;
	return TRUE;
}

bool CncControl::XYMove(float nX, float nY, CString asMode)
{
	if(asMode == "ABS")    //相对运动
	{
		if (nX<0||nX>500)
		{
			MessageBox(NULL,_T("X绝对运动超界！"),_T("错误"),MB_OK);
			return FALSE;
		}
		if (nY<0||nY>530)
		{
			MessageBox(NULL,_T("Y绝对运动超界！"),_T("错误"),MB_OK);
			return FALSE;
		}
		SetXPAbs(nX);
		SetYPAbs(nY);
	}
	else                   //绝对运动
	{
		if (cnccondition.XPOS+nX<0||cnccondition.XPOS+nX>500)
		{
			MessageBox(NULL,_T("X相对运动超界！"),_T("错误"),MB_OK);
			return FALSE;
		}
		if (cnccondition.YPOS+nY<0||cnccondition.YPOS+nY>500)
		{
			MessageBox(NULL,_T("Y相对运动超界！"),_T("错误"),MB_OK);
			return FALSE;
		}
		SetXPRel(nX);
		SetYPRel(nY);
	}
	return TRUE;
}


bool CncControl::SetXYSpeed(float unXYSpeed)	
{
	CString XYspeed;
	CString XYSpeed2;
	if(unXYSpeed<0.1||unXYSpeed>10)
	{
		MessageBox(NULL,_T("速度设定超界"),_T("错误"),MB_OK);
		return FALSE;
	}
	XYSpeed2.Format("%.3f",unXYSpeed);
	XYspeed="SPXY";
	XYspeed+=XYSpeed2;
	send(sockClient,XYspeed, strlen(XYspeed), 0);
	return TRUE;
}

bool CncControl::SetZPAbs(float nZPAbs)
{
	CString ZPAbs;
	CString nZ;
	nZ.Format("%.3f",nZPAbs);
	ZPAbs="ZA";
	ZPAbs+=nZ;
	send(sockClient,ZPAbs, strlen(ZPAbs), 0);
	return TRUE;
}

bool CncControl::SetXPAbs(float nXPAbs)
{
	CString XPAbs;
	CString nx;
	nx.Format("%.3f",nXPAbs);
	XPAbs="XA";
	XPAbs+=nx;
	send(sockClient,XPAbs, strlen(XPAbs), 0);
	return TRUE;
}

bool CncControl::SetYPAbs(float nYPAbs)
{
	CString YPAbs;
	CString nY;
	nY.Format("%.3f",nYPAbs);
	YPAbs="YA";
	YPAbs+=nY;
	send(sockClient,YPAbs, strlen(YPAbs), 0);	
	return TRUE;
}
bool CncControl:: SetYPRel(float nYPRel)
{
	CString YPRel;
	CString nY;
	if (nYPRel==0)
	{
		return TRUE;
	}
	nY.Format("%.3f",nYPRel);
	YPRel="YI";
	YPRel+=nY;
	send(sockClient,YPRel, strlen(YPRel), 0);
	return TRUE;
}

bool CncControl::SetXPRel(float nXPRel)
{
	CString XPRel;
	CString nX;
	if (nXPRel==0)
	{
		return TRUE;
	}
	nX.Format("%.3f",nXPRel);
	XPRel="XI";
	XPRel+=nX;
	send(sockClient,XPRel, strlen(XPRel), 0);	
	return TRUE;
}

bool CncControl::CheckCncState()
{
	send(sockClient,"CHKALL", strlen("CHKALL"), 0);
	return TRUE;
}


int  CncControl::GetCncMessage()
{
  int i,j;
  int ret=recv(sockClient,recvBuf,sizeof(recvBuf),0);
  if(SOCKET_ERROR == ret)	
  {
	  return 0;
  }
 if(!strncmp(recvBuf, "ISOK=", 5))
  {
	for(i = 5,j = 0; i <= strlen(recvBuf); i++,j++)
	tempBuf[j] = recvBuf[i];
	if(!stricmp(tempBuf, "Ok"))
	{	
		 return 11;
	}
    else
	{
		return 10;

	}
  }
 if(!strncmp(recvBuf, "Home ", 5))
 {
	 for(i = 5,j = 0; i <= strlen(recvBuf); i++,j++)
		 tempBuf[j] = recvBuf[i];
	 if(!stricmp(tempBuf, "successed"))
	 {	
		// MessageBox(NULL,_T("回原点正确!"),_T("提示"),MB_OK);
		 return 21;
	 }
	 else
	 {
		// MessageBox(NULL,_T("回原点错误!"),_T("错误"),MB_OK);
		 return 20;

	 }
 }
 //-----------------------------------------------------------checkall返回数据
 if ( !strncmp(recvBuf, "1", 1)|| !strncmp(recvBuf, "0", 1))
 {
	 CString xd(recvBuf[0],1);
	 CString yd(recvBuf[1],1);
	 CString zd(recvBuf[2],1);
	 char xpos2[9];
	 memcpy(xpos2,recvBuf+3,9);
	 char ypos2[9];
	 xpos2;
	 memcpy(ypos2,recvBuf+12,9);
	 char zpos2[9];
	 memcpy(zpos2,recvBuf+21,9);
	 cnccondition.XD=atoi(xd);
	 cnccondition.XPOS=atof(xpos2);
     cnccondition.YD=atoi(yd);
	 cnccondition.YPOS=atof(ypos2);
	 cnccondition.ZD=atoi(zd);
	 cnccondition.ZPOS=atof(zpos2);
	 return 3;
 }
   CheckCncState();
	return 0;
}

bool CncControl::SendCommandToCnc(char *command)
{
	CString message=command;
	send(sockClient,message, strlen(message), 0);
	return TRUE;
}