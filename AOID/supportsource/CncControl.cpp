

#include "stdafx.h"
#include "CncControl.h"
#include "MainFrm.h"
#include "AOID.h"

#include<iostream> 
using namespace std; 
#include<fstream>

/*#ifdef _DEBUG
#define new DEBUG_NEW
#endif
*/



unsigned long m_msgID;
unsigned long m_WParam;
unsigned long m_LParam;
//extern CCncApp theApp;
CncControl::CncControl()
{
	// TODO: Add your control notification handler code here
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
	//连接请求
}
CncControl::~CncControl()
{
}
int CncControl::IniCncControl(void * pmainwnd)
{
	if (SOCKET_ERROR==connect(sockClient,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR)))
	{
		MessageBox(NULL,_T("机床连接失败！"),_T("错误"),MB_OK);
		return 0;
	}
	else
	{
		MessageBox(NULL,_T("机床连接成功！"),_T("提示"),MB_OK);
	}
    send(sockClient,"ISOK", strlen("ISOK"), 0);
	
	//send(sockClient,"HOME", strlen("HOME"), 0);

	return 1;
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
	if(asMode == "ABS")    //Abs Coordinate
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
	    SetMASXPAbs(nX);
        SetMASYPAbs(nY);
	}
	else                    //Rel Coordinate
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
		SetMASXPRel(nX);
		SetMASYPRel(nY);
	}
	return TRUE;
}
bool CncControl::SetMASXYSpeed(float unXYSpeed)	//Unit=um/s
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

bool CncControl::SetMASZPAbs(float nZPAbs)
{
	CString ZPAbs;
	CString nZ;
	nZ.Format("%.3f",nZPAbs);
	ZPAbs="ZA";
	ZPAbs+=nZ;
	send(sockClient,ZPAbs, strlen(ZPAbs), 0);
	return TRUE;
}

bool CncControl::SetMASXPAbs(float nXPAbs)
{
	CString XPAbs;
	CString nx;
	nx.Format("%.3f",nXPAbs);
	XPAbs="XA";
	XPAbs+=nx;
	send(sockClient,XPAbs, strlen(XPAbs), 0);
	return TRUE;
}

bool CncControl::SetMASYPAbs(float nYPAbs)
{
	CString YPAbs;
	CString nY;
	nY.Format("%.3f",nYPAbs);
	YPAbs="YA";
	YPAbs+=nY;
	send(sockClient,YPAbs, strlen(YPAbs), 0);	
	return TRUE;
}

bool CncControl:: SetMASYPRel(float nYPRel)
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

bool CncControl::SetMASXPRel(float nXPRel)
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

/*bool CncControl::SetMASZPRel(int nZPRel)//z轴的相对运动
{
	CString ZPRel;
	CString nZ;
	if (nZPRel==0)
	{
		return TRUE;
	}
	int zmove;
	zmove=cnccondition.ZPOS+nZPRel;
	nZ.Format("%d",zmove);
	ZPRel="ZA";
	ZPRel+=nZ;
	send(sockClient,ZPRel, strlen(ZPRel), 0);
	return TRUE;
}*/


bool CncControl::CheckCncState()
{
   send(sockClient,"CHKALL", strlen("CHKALL"), 0);
   return TRUE;
}

int CncControl::GetCncMessage()
{  
//-----------------------------------------------------ZNS0421
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
        // MessageBox(NULL,_T("板卡状态正确!"),_T("提示"),MB_OK);
		 return 11;
	}
    else
	{
		//MessageBox(NULL,_T("板卡状态错误!"),_T("错误"),MB_OK);
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
	/* CString xpos1(recvBuf[3],10);
	 CString ypos1(recvBuf[13],10);
	 CString zpos1(recvBuf[23],10);*/
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
int CncControl::GetAxisDI(CString asAxis)
{
	CString asCmd = asAxis+".IP";
	char *szCmd;
	
	szCmd =(LPTSTR)(LPCTSTR)asCmd; 
	
	if(SendCommand(szCmd) == false)
		return(0);
	return(nMASRV);
}

int CncControl::ReadEnvFileInt(char* Section, char* Ident, char *Default)
{
	int nValue;
	char pszValue[128];
	
	//	TIniFile *EnvFile = new TIniFile(ExtractFilePath(Application->ExeName) + "HiCNC.ini");
	//	nValue = EnvFile->ReadInteger(Section, Ident, Default);
	//	delete(EnvFile);
	GetPrivateProfileString(Section, Ident, Default, pszValue, 128, "./HiCNC.ini");
	
	try
	{
		nValue = atoi(pszValue);
	}
	catch(...)
	{
		nValue = atoi(Default);
	}
	return(nValue);
}



bool CncControl::SendCommand(char *szCommand, bool flagNeedCallback,bool CmdFlag)
{
	MessageType message;
	int istrlen;
	istrlen =strlen(szCommand);
	if(istrlen>0)
	{
		message.messagecode = (char *)malloc(istrlen+1);
		if(message.messagecode!=NULL)
		{//分配成功
			strcpy(message.messagecode,szCommand);	
			message.flagNeedCallback = flagNeedCallback;
			if(!CmdFlag)
			{
				(theApp.pwnd)->m_pcncmessage->SendMessage(message);
			}
			else
			{
				(theApp.pwnd)->m_pcnccmdmessage->SendMessage(message);
			}
			free(message.messagecode);
		}
	}
	
	return(true);
}
bool CncControl::GetMASPass()//获得程序控制器端当前程序执行的状态
{
	
	if(GetMASConStatus() == false)
	{
		MASStatus[3] = 0;
		return false;
	}
	if(MASStatus[0] != 2)
	{
		MASStatus[3] = 0;
		return false;
	}
	if(SendCommand("MASStatus[3]") == false)
	{
		MASStatus[3] = 0;
		return false;
	}
	MASStatus[3] = nMASRV;
	if(MASStatus[3] == 0)
		return(true);
	
	return false;
}
bool CncControl::SetMASINTStatus(int nStatus)
{
	
	
	
	char szCmd[4096] = {0};
	
	
	sprintf(szCmd, "MASStatus[1]=%d", nStatus);
	if(SendCommand(szCmd) == false)
		return false;
	MASStatus[1] = nStatus;
	return(true);
	
}
bool CncControl::GetMASConStatus()
{
	
	if(SendCommand("MASStatus[0]") == false)
		return false;
	MASStatus[0] = nMASRV;
	return(true);
}
bool CncControl::SetMASSysVar()//设置系统环境变量
{
	char szCmd[4096] = {0};
	int i;
	
	
	sprintf(szCmd, "nSPNum=%d", Configstruct.SpindleInfo.nSpindleNumbers);
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nChkSp=%d", Configstruct2.bCheckSpindle==true? 1:0);
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	
	sprintf(szCmd, "fXEGear=%f", Configstruct2.fXEGear);
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "fYEGear=%f", Configstruct2.fYEGear);
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "fZEGear=%f", Configstruct2.fZEGear);
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nXLL=%d", Round(Configstruct.SystemInfo.nXLeftLimit/Configstruct2.fXEGear));	//um->count
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nXRL=%d", Round(Configstruct.SystemInfo.nXRightLimit/Configstruct2.fXEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nYFL=%d", Round(Configstruct.SystemInfo.nYFrontLimit/Configstruct2.fYEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nYBL=%d", Round(Configstruct.SystemInfo.nYBackLimit/Configstruct2.fYEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	
	
	sprintf(szCmd, "nDBot=%d", Round(Configstruct2.nDBot/Configstruct2.fZEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nDWV=%d", Round(Configstruct2.nDWV/Configstruct2.fZEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	
	for(i = 0; i < 6; i++)
	{
		sprintf(szCmd, "nZWZO[%d]=%d", i, Round(Configstruct.SystemInfo.nZWorkZeroOffset[i]/Configstruct2.fZEGear));
		if(SendCommand(szCmd) == false)
			goto Failure;
		
		sprintf(szCmd, "nZStatus[%d]=%d", i, Configstruct2.nZAxesStatus[i]);
		if(SendCommand(szCmd) == false)
			goto Failure;
		
	}
	
	sprintf(szCmd, "nXAC=%d", Round(Configstruct.SystemInfo.unXYAcc/Configstruct2.fXEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nXDC=%d", Round(Configstruct.SystemInfo.unXYDcc/Configstruct2.fXEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nXSpeed=%d", Round(Configstruct2.unXYWorkMoveSpeed/Configstruct2.fXEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nXWKSpeed=%d", Round(Configstruct2.unXYWorkMoveSpeed/Configstruct2.fXEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nYAC=%d", Round(Configstruct.SystemInfo.unXYAcc/Configstruct2.fYEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nYDC=%d", Round(Configstruct.SystemInfo.unXYDcc/Configstruct2.fYEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nYSpeed=%d", Round(Configstruct2.unXYWorkMoveSpeed/Configstruct2.fYEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nYWKSpeed=%d", Round(Configstruct2.unXYWorkMoveSpeed/Configstruct2.fYEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nZAC=%d", Round(Configstruct.SystemInfo.unZAcc/Configstruct2.fZEGear));	//um/s2->count/s2
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nZDC=%d", Round(Configstruct.SystemInfo.unZDcc/Configstruct2.fZEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nZDSpeed=%d", Round(Configstruct2.unZDownSpeed/Configstruct2.fZEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nZUSpeed=%d", Round(Configstruct2.unZUpSpeed/Configstruct2.fZEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nZMaxSpeed=%d", Round(Configstruct.SystemInfo.unZMaxVelocity/Configstruct2.fZEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nXSFTime=%d", Configstruct.SystemInfo.nXSFTime);
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nYSFTime=%d", Configstruct.SystemInfo.nYSFTime);
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nZSFTime=%d", Configstruct.SystemInfo.nZSFTime);
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	
	
	sprintf(szCmd, "nTXSpace=%d", Round(Configstruct.ToolInfo.nXSpace/Configstruct2.fXEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nTYSpace=%d", Round(Configstruct.ToolInfo.nYSpace/Configstruct2.fYEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nTZBP[0]=%d", Round(Configstruct.ToolInfo.nZ1BasePos/Configstruct2.fZEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nTZBP[1]=%d", Round(Configstruct.ToolInfo.nZ2BasePos/Configstruct2.fZEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nTZBP[2]=%d", Round(Configstruct.ToolInfo.nZ3BasePos/Configstruct2.fZEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nTZBP[3]=%d", Round(Configstruct.ToolInfo.nZ4BasePos/Configstruct2.fZEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nTZBP[4]=%d", Round(Configstruct.ToolInfo.nZ5BasePos/Configstruct2.fZEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nTZBP[5]=%d", Round(Configstruct.ToolInfo.nZ6BasePos/Configstruct2.fZEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	if(!strcmp(Configstruct.ToolInfo.cChangeToolMode, "HAND"))
	{
		sprintf(szCmd, "nTCM=%d", 0);
		if(SendCommand(szCmd) == false)
			goto Failure;
		
	}
	else if(!strcmp(Configstruct.ToolInfo.cChangeToolMode ,"HALFAUTO"))
	{
		sprintf(szCmd, "nTCM=%d", 1);
		if(SendCommand(szCmd) == false)
			goto Failure;
		
	}
	else
	{
		sprintf(szCmd, "nTCM=%d", 2);
		if(SendCommand(szCmd) == false)
			goto Failure;
		
	}
	for(i = 0; i < 6; i++)
	{
		sprintf(szCmd, "nACTCmp[%d]=%d", i, Round(Configstruct.ToolInfo.nACTCompensation[i]/Configstruct2.fZEGear));
		if(SendCommand(szCmd) == false)
			goto Failure;
		
	}
	sprintf(szCmd, "nCTMTD=%d", Configstruct2.bCTMATToolDie==true? 1:0);
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	
	sprintf(szCmd, "nACFChkTimeouts=%d", Configstruct.PressureFootInfo.nACFChkTimeouts);
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nFBPChkTimeouts=%d", Configstruct.PressureFootInfo.nFBPChkTimeouts);
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nFTPChkTimeouts=%d", Configstruct.PressureFootInfo.nFTPChkTimeouts);
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	
	sprintf(szCmd, "nQICFBPChkTimeouts=%d", Configstruct.PressureFootInfo.nQICFBPChkTimeouts);
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	
	sprintf(szCmd, "nTDLChkTimeouts=%d", Configstruct.PressureFootInfo.nTDLChkTimeouts);
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	
	
	sprintf(szCmd, "nTRCEnable=%d", Configstruct2.nMode==0?0:1);
	
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nTRCMvSP=%d", Round(Configstruct.InspectInfo.nTableMvSP/Configstruct2.fYEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
/*	if(Round((Configstruct2.nCurTDia/2-TDiaChk.fFChkPos)/Configstruct2.fYEGear) <= 0)
		sprintf(szCmd, "nTRCChkRadius=0");
	else
		sprintf(szCmd, "nTRCChkRadius=%d", Round((Configstruct2.nCurTDia/2-TDiaChk.fFChkPos)/Configstruct2.fYEGear));*///TRC Fast Position 已删
	
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nBlowTime=%d", Configstruct.InspectInfo.unBlowTime);
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	
	sprintf(szCmd, "nGPSPX=%d", Round(Configstruct.ToolInfo.nGPForSPX/Configstruct2.fXEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nGPSPY=%d", Round(Configstruct.ToolInfo.nGPForSPY/Configstruct2.fYEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nGPR1X=%d", Round(Configstruct.ToolInfo.nGPForRoom1X/Configstruct2.fXEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nGPR1Y=%d", Round(Configstruct.ToolInfo.nGPForRoom1Y/Configstruct2.fYEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nGPR81X=%d", Round(Configstruct.ToolInfo.nGPForRoom81X/Configstruct2.fXEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nGPR81Y=%d", Round(Configstruct.ToolInfo.nGPForRoom81Y/Configstruct2.fYEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nGFODT=%d", Configstruct.ToolInfo.unGripFingerOpenDelayTime);
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nGFCDT=%d", Configstruct.ToolInfo.unGripFingerCloseDelayTime);
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nGRDT=%d", Configstruct.ToolInfo.unRaisedGripDelayTime);
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nMaxTRIndex=%d", Configstruct.ToolInfo.nMaxIndexOfToolRoom);
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	
	sprintf(szCmd, "nBTC=%d", Configstruct.InspectInfo.cBTC=="ON"?1:0);
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nPBTNum=%d", Configstruct.FilterInfo.nPmtBTNum);
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	
	sprintf(szCmd, "nTDCStatus=%d", Configstruct.InspectInfo.cTDC=="ON"?1:0);
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nDrlTDC=%d", Configstruct.InspectInfo.cDrilledTDC=="ON"?1:0);
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nATDA=%d", Configstruct.InspectInfo.cATDA=="ON"?1:0);
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	//Ver16.2.1.10
	sprintf(szCmd, "nACFStatus=%d", Configstruct.PressureFootInfo.cACF=="ON"?1:0);
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	
	sprintf(szCmd, "nTDCZSpeed=%d", Round(Configstruct.InspectInfo.unTDCZVelocity/Configstruct2.fZEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nTDCX=%d", Round(Configstruct.InspectInfo.nTDCX/Configstruct2.fXEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nTDCY=%d", Round(Configstruct.InspectInfo.nTDCY/Configstruct2.fYEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nTDCZRef[0]=%d", Round(Configstruct.InspectInfo.nTDCRefDepthZ1/Configstruct2.fZEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nTDCZRef[1]=%d", Round(Configstruct.InspectInfo.nTDCRefDepthZ2/Configstruct2.fZEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nTDCZRef[2]=%d", Round(Configstruct.InspectInfo.nTDCRefDepthZ3/Configstruct2.fZEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nTDCZRef[3]=%d", Round(Configstruct.InspectInfo.nTDCRefDepthZ4/Configstruct2.fZEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nTDCZRef[4]=%d", Round(Configstruct.InspectInfo.nTDCRefDepthZ5/Configstruct2.fZEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nTDCZRef[5]=%d", Round(Configstruct.InspectInfo.nTDCRefDepthZ6/Configstruct2.fZEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nTDCMinE=%d", Round(Configstruct.InspectInfo.nTDCPmtMinErr/Configstruct2.fZEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	sprintf(szCmd, "nTDCMaxE=%d", Round(Configstruct.InspectInfo.nTDCPmtMaxErr/Configstruct2.fZEGear));
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	
	sprintf(szCmd, "nLoopType=%d", Configstruct.SystemInfo.nLoopType);
	if(SendCommand(szCmd) == false)
		goto Failure;
	
	if(MASStatus[0] == 2)
	{
		if(SetMASFC(f_INIT) == false)
			return false;
		_sleep(500);
		if(GetMASPass() == false)
			return false;
		else
		{
			//			OKBtn->Enabled = true;
			//			CancelBtn->Enabled = true;
			return(true);
		}
	}
	else if(SetMASConStatus(2) == false)
		return false;
	else
	{
		//	OKBtn->Enabled = true;
		//	CancelBtn->Enabled = true;
		
		return(true);
	}
Failure:
	SetMASConStatus(3);
	nStart = 2;
	
	return false;
}
bool CncControl::SetMASFC(int nFC)
{
	char szCmd[4096] = {0};
	/*	if(MASStatus[3] != 0)
	{
	if(GetMASPass() == false)
	return false ;
}*/
	sprintf(szCmd, "MASStatus[3]=%d", nFC);
	
	if(SendCommand(szCmd,true,true) == false)
		return false;
	
	
	//	MASStatus[3] = nFC;
	
	return(true);
	
}
bool CncControl::SetMASHostIdleStatus(int nStatus)
{
	char szCmd[4096] = {0};
	
	sprintf(szCmd, "MASStatus[2]=%d", nStatus);
	if(SendCommand(szCmd) == false)
		return false;
	MASStatus[2] = nStatus;
	return(true);
	
}
bool CncControl::SetMASConStatus(int nStatus)//Write MAS's connection status
{
	char szCmd[4096] = {0};
	
	sprintf(szCmd, "MASStatus[0]=%d", nStatus);
	if(SendCommand(szCmd) == false)
		return false;
	MASStatus[0] = nStatus;
	return(true);
}
int CncControl::Round(double dfValue)
{
	if(dfValue < 0)
		return((int)(dfValue-0.5));
	else
		return((int)(dfValue+0.5));
}

bool CncControl::Return_Machine_Zero()//设置机械原点
{
	//	RemoveKeyBoardInput();
	
	if(SetMASFC(f_FMZ) == false)
	{
		//		Application->MessageBox("零位检测失败!", "错误-零位检测", MB_OK|MB_ICONERROR);
		//	MessageBox("零位检测失败!", "错误", MB_ICONERROR);
		return false;
	}
	return(true);
}

CncCom::CncCom()
{
	bMASPERR = false;//控制器端程序错误标志
}
CncCom::~CncCom()
{
	
}
int CncCom::ConnectMaestro()
{
	int nOK;
	int nReturn;
	char szName[32] = {0}, szError[1024] = {0};
	char szOut[4096] = {0};
	nOK = MACInitialize(COM_INIT_MULTITHREADED, TRUE);
	//Ver16.7.4.62-3
	if(nOK >= 1 && nOK <= 3)
	{
		MACUninitialize();
		nOK = MACInitialize(COM_INIT_DISABLE, TRUE);
	}
	if(nOK != 0)
	{
		MACGetLastError(szError, 1024);
		//		MessageBox(szError, "错误", MB_ICONERROR);
	}
	m_hCom = NULL;
	
	int n = MACLocateDevices();
	if(n == 0)
	{
		//		MessageBox("没有Maestro连接到系统!", "错误", MB_ICONERROR);
		return -1;
	}
	else if(n != 1)
	{
		if(n > 1)
		{
			//			MessageBox("多个Maestro连接到系统!", "错误", MB_ICONERROR);
		}
		else if(n < 0)
		{
			MACGetLastError(szError, 1024);
			//	MessageBox(szError, "错误", MB_ICONERROR);
		}
		return -1;
	}
	
	if(MACGetDevice(0, szIP, szName) != 0)
	{
		MACGetLastError(szError, 1024);
		//MessageBox(szError, "错误", MB_ICONERROR);
		return -1;
	}
	
	unsigned long dwIP = 0;
	if(MACIsDevicePresent(szIP, &dwIP) != 0)
	{
		MACGetLastError(szError, 1024);
		//MessageBox(szError, "错误", MB_ICONERROR);
		return -1;
	}
	CString IpCode;
	m_hCom = MACCreateTCPConnection(szIP, 10000, 23);
	if(m_hCom)
	{
		MACRegCloseCallback(m_hCom, OnMACError);	//紧急错误回调函数
		MACRegMessageCallback(m_hCom, OnMACMessage);//正常的消息回调函数
		_sleep(500);	//Wait to Maestro send message
		if(bMASPERR == true)
		{
			CString asMsg = "运动控制器程序错误!错误号:";
			IpCode.Format("%s",nPECode);
			asMsg+=IpCode;
			//		asMsg+=htons(nPECode);
			//		MessageBox(asMsg, "错误", MB_ICONERROR);
			return(-1);
		}
		//Ver16.5.2.27-1:Fix bug
		nReturn = MACSendCommand(m_hCom, "Autoexec.run", szOut, 4096, 2000);
		//if(SendCommand("Autoexec.run") == false)
		if(nReturn !=0 )
		{
			
			//	MessageBox("控制器没有程序!\n\n退出检查!!", "错误", MB_ICONERROR);
			return(-1);
		}
		else if(!strcmp(szOut,"OK"))	//Program start running
		{
			_sleep(1000);
		}
		
		/*		GetMASPass();
		if(MASStatus[3] != 0)
		{
		SetMASINTStatus(1);	//Interrupt Maestro function run
		_sleep(1000);
		GetMASPass();
		if(MASStatus[3] != 0)
		{
		//		MessageBox("控制器程序没有响应!\n\n请关电重试!!", "错误",MB_ICONERROR);
		return -1;
		}
		}
		if(GetMASConStatus() == false)
		return -1;
		if(SetMASSysVar() == false)	//Set envirionment
		return -1;	
		Configstruct2.bMAS = true;
		*/	
	}
	else
	{
		MACGetLastError(szError, 1024);
		//MessageBox(szError, "错误", MB_ICONERROR);
		return -1;
	}
	return 0;
}
void CncCom::OnMACError(const char* szDevice)
{
	//::MessageBox(NULL,"连接失败!", "错误", MB_ICONERROR);
}
//回调函数
void CncCom::OnMACMessage(unsigned long msgID,
						  unsigned long WParam,
						  unsigned long LParam,
						  unsigned long msgTime)
{
	
	m_msgID = msgID;
	m_WParam = WParam;
	m_LParam = LParam;
}

bool CncControl::AddPathNote(char *pathnote)
{
	
	m_pathcurrent=(FilePath*)malloc(sizeof(FilePath));
	if(m_pathfirst==NULL)
		m_pathfirst=m_pathcurrent;
	if(m_pathprevious!=NULL)
		if(NULL!=m_pathprevious->pnext)
		{
			m_pathprevious=m_pathprevious->pnext;
			m_pathprevious->pnext=m_pathcurrent;
		}
		else
		{
			m_pathprevious->pnext=m_pathcurrent;
		}
		strcpy(m_pathcurrent->pathstr,pathnote);
		m_pathcurrent->pnext=NULL;
		if(0==notenum)
		{
			m_pathprevious=m_pathcurrent;		
		}
		notenum++;
		return true;
}
//-----------------------------------------------------------------
//函数功能：完成Z轴的寸动功能
bool CncControl::ZMove(float nZ,CString asMode)
{
	if(asMode == "ABS")    //Abs Coordinate
	{
		if (nZ>0||nZ<-35)
		{
			MessageBox(NULL,_T("Z运动超界！"),_T("错误"),MB_OK);
			return FALSE;
		}
		SetMASZPAbs(nZ);
	}
	else                    //Rel Coordinate
	{
		
		if (cnccondition.ZPOS+nZ>0||cnccondition.ZPOS+nZ<-35)
		{
			MessageBox(NULL,_T("Z运动超界！"),_T("错误"),MB_OK);
			return FALSE;
		}

		SetMASZPAbs(cnccondition.ZPOS+nZ);
	}
	return TRUE;
}
//-----------------------------------------------------------------
//函数功能：完成XY轴的连续运动
bool CncControl::XYJog(int nXJV, int nXJDD, int nYJV, int nYJDD)
{
	SetMASXYJDD(nXJDD, nYJDD);
	SetMASXYJV(nXJV, nYJV);
	SetMASFC(f_XYJG);
	return true;
}
//-----------------------------------------------------------------
//函数功能：完成Z轴的连续运动
bool CncControl::ZJog(int nJV)
{
	SetMASZJV(nJV);
	SetMASFC(f_ZJG);
	return(true);
}
//-------------------------------------------------------------------
//设置下位机的减速点距离
bool CncControl::SetMASXYJDD(int nXJDD, int nYJDD)	//Unit=um
{
	char szCmd[4096] = {0};
	sprintf(szCmd, "nXJDD=%d;nYJDD=%d", Round(nXJDD/Configstruct2.fXEGear), Round(nYJDD/Configstruct2.fYEGear));
	return(SendCommand(szCmd,false,true));
}
//-------------------------------------------------------------------
//设置下位机的速度
bool CncControl::SetMASXYJV(int nXJV, int nYJV)	//Unit=um/s
{
	char szCmd[4096] = {0};
	
	sprintf(szCmd, "nXJV=%d;nYJV=%d", Round(nXJV/Configstruct2.fXEGear), Round(nYJV/Configstruct2.fYEGear));
	return(SendCommand(szCmd,false,true));
}
//-------------------------------------------------------------------
bool CncControl::SetMASZJV(int nJV)	//Unit=um/s
{
	char szCmd[4096] = {0};
	
	sprintf(szCmd, "nZJV=%d", Round(nJV/Configstruct2.fZEGear));
	return(SendCommand(szCmd,false,true));
}
//-------------------------------------------------------------------
double CncControl::calculatespeed(int velocity, int accelerate)
{
	double distance=(0.5*velocity*velocity)/accelerate;
	return distance;
}
//-------------------------------------------------------------------
bool CncControl::SetMASZSpeed(float uiZSpeed)
{
	CString Zspeed;
	CString ZSpeed2;
	if(uiZSpeed<0.1||uiZSpeed>10)
	{
		MessageBox(NULL,_T("Z速度设定超界"),_T("错误"),MB_OK);
		return FALSE;
	}
	ZSpeed2.Format("%.3f",uiZSpeed);
	Zspeed="SPZ";
	Zspeed+=ZSpeed2;
	send(sockClient,Zspeed, strlen(Zspeed), 0);
	return TRUE;
}

int CncControl::WriteConfigFile()
{
	WorkParameterToConfigFileParameter();
	
	FILE *fp;
	if((fp=fopen("HiCNC.ini","w"))==NULL)
		return -1;//文件打开失败
	CString sectionstr;
	char strempty[512]="111111";
	int iempty=11111;//test data
	float fempty=(float)1.111;//test data
  
    fprintf(fp,"%s\n","[SYSTEM]");//[SYSTEM]
	fprintf(fp,"XY Loop Type=%d\n",Configstruct.SystemInfo.nLoopType);
	fprintf(fp,"X Axes Sensor Resolution(P/R)=%d\n",Configstruct.SystemInfo.nXSensorResolution);
	fprintf(fp,"X Axes Screw Pitch(mm)=%d\n",Configstruct.SystemInfo.nXScrewPitch);
	fprintf(fp,"Y Axes Sensor Resolution(P/R)=%d\n",Configstruct.SystemInfo.nYSensorResolution);
	fprintf(fp,"Y Axes Screw Pitch(mm)=%d\n",Configstruct.SystemInfo.nYScrewPitch);
	fprintf(fp,"Z Axes Sensor Resolution(P/R)=%d\n",Configstruct.SystemInfo.nZSensorResolution);
	fprintf(fp,"Z Axes Screw Pitch(mm)=%d\n",Configstruct.SystemInfo.nZScrewPitch);
	fprintf(fp,"X Axis Left Limit Voyage(um)=%d\n",Configstruct.SystemInfo.nXLeftLimit);	
	fprintf(fp,"X Axis Right Limit Voyage(um)=%d\n",Configstruct.SystemInfo.nXRightLimit);
	fprintf(fp,"Y Axis Front Limit Voyage(um)=%d\n",Configstruct.SystemInfo.nYFrontLimit);
	fprintf(fp,"Y Axis Back Limit Voyage(um)=%d\n",Configstruct.SystemInfo.nYBackLimit);
	fprintf(fp,"X Axis Pin Position(um)=%d\n",Configstruct.SystemInfo.nXPinPosition);
	fprintf(fp,"Y Axis Pin Position(um)=%d\n",Configstruct.SystemInfo.nYPinPosition);
	fprintf(fp,"Y Axis Work Table Start Position(um)=%d\n",Configstruct.SystemInfo.nYWTStPos);
	fprintf(fp,"Z Axes Save Voyage(um)=%d\n",Configstruct.SystemInfo.nZSaveVoyage);
	fprintf(fp,"Z1 Axes Work Zero(um)=%d\n",Configstruct.SystemInfo.nZWorkZeroOffset[0]);
	fprintf(fp,"Z2 Axes Work Zero(um)=%d\n",Configstruct.SystemInfo.nZWorkZeroOffset[1]);
	fprintf(fp,"Z3 Axes Work Zero(um)=%d\n",Configstruct.SystemInfo.nZWorkZeroOffset[2]);
	fprintf(fp,"Z4 Axes Work Zero(um)=%d\n",Configstruct.SystemInfo.nZWorkZeroOffset[3]);
	fprintf(fp,"Z5 Axes Work Zero(um)=%d\n",Configstruct.SystemInfo.nZWorkZeroOffset[4]);
	fprintf(fp,"Z6 Axes Work Zero(um)=%d\n",Configstruct.SystemInfo.nZWorkZeroOffset[5]);
	fprintf(fp,"XY Axes Max Move Velocity(mm/min)=%d\n",Configstruct.SystemInfo.unXYMaxSpeed);
	fprintf(fp,"XY Axes Acceleration(mm/s2)=%d\n",Configstruct.SystemInfo.unXYAcc);
	fprintf(fp,"XY Axes Deceleration(mm/s2)=%d\n",Configstruct.SystemInfo.unXYDcc);
	fprintf(fp,"Z Axes Max Move Velocity(mm/min)=%d\n",Configstruct.SystemInfo.unZMaxVelocity);
	fprintf(fp,"Z Axes Acceleration(mm/s2)=%d\n",Configstruct.SystemInfo.unZAcc);
	fprintf(fp,"Z Axes Deceleration(mm/s2)=%d\n",Configstruct.SystemInfo.unZDcc);
	fprintf(fp,"X Axis Smooth Factor(ms)=%d\n",Configstruct.SystemInfo.nXSFTime);
	fprintf(fp,"Y Axis Smooth Factor(ms)=%d\n",Configstruct.SystemInfo.nYSFTime);
	fprintf(fp,"Z Axes Smooth Factor(ms)=%d\n",Configstruct.SystemInfo.nZSFTime);
	fprintf(fp,"X Axis Setting Position Error(um)=%d\n",Configstruct.SystemInfo.nXSPE);
	fprintf(fp,"Y Axis Setting Position Error(um)=%d\n",Configstruct.SystemInfo.nYSPE);
	fprintf(fp,"XY Axes Allowed Position Error(um)=%d\n",Configstruct.SystemInfo.nXYAllowedPE);
	fprintf(fp,"X Axis Distance Of HMI To HMS(um)=%d\n",Configstruct.SystemInfo.nXHMItoS);
	fprintf(fp,"Y Axis Distance Of HMI To HMS(um)=%d\n",Configstruct.SystemInfo.nYHMItoS);
	fprintf(fp,"X Axis Work Zero(um)=%d\n",Configstruct.SystemInfo.nXWorkZero);
	fprintf(fp,"Y Axis Work Zero(um)=%d\n",Configstruct.SystemInfo.nYWorkZero);
	
	fprintf(fp,"%s\n","[SPINDLE]");//[SPINDLE]
	fprintf(fp,"Spindle Numbers=%d\n",Configstruct.SpindleInfo.nSpindleNumbers);
	fprintf(fp,"Z Axes Switch Status=%s\n",Configstruct.SpindleInfo.cZAxesStatus);
	fprintf(fp,"Spindle Type=%s\n",Configstruct.SpindleInfo.cSpindleType);
	fprintf(fp,"Spindle Min Rpm=%d\n",Configstruct.SpindleInfo.unSpindleMinRev);
	fprintf(fp,"Spindle Max Rpm=%d\n",Configstruct.SpindleInfo.unSpindleMaxRev);
	fprintf(fp,"Inverter=%s\n",Configstruct.SpindleInfo.cInverter);
	fprintf(fp,"Last Stop Time=%s\n",Configstruct.SpindleInfo.cLastStopTime);
	fprintf(fp,"Inverter ADcc Time(S)=%.1f\n",Configstruct.SpindleInfo.fADccTime);
	fprintf(fp,"INV Rated Current(A)=%.1f\n",Configstruct.SpindleInfo.fINVRatedCurrent);
	fprintf(fp,"Single Spindle Rated Power(KW)=%.1f\n",Configstruct.SpindleInfo.fRatedPower);
	fprintf(fp,"Single Spindle Full Load Current(A)=%.1f\n",Configstruct.SpindleInfo.fFullLoadCurrent);
	fprintf(fp,"Single Spindle Empty Load Current(A)=%.1f\n",Configstruct.SpindleInfo.fEmptyLoadCurrent);
	fprintf(fp,"Single Spindle Torque Compensate(%%)=%.1f\n",Configstruct.SpindleInfo.fTorqueCompensate);
	fprintf(fp,"Single Spindle Prevent Over Current in Accelerating(%%)=%.1f\n",Configstruct.SpindleInfo.fPOCAcc);
	fprintf(fp,"Single Spindle Prevent Over Current in Running(%%)=%.1f\n",Configstruct.SpindleInfo.fPOCRun);
	fprintf(fp,"Single Spindle Over Torque Check Level(%%)=%.1f\n",Configstruct.SpindleInfo.fPOT);
	fprintf(fp,"Single Spindle DC Brake Level(%%)=%.1f\n",Configstruct.SpindleInfo.fDCBrake);
	fprintf(fp,"Single Spindle Current Limit(A)=%.1f\n",Configstruct.SpindleInfo.fSSCL);
	fprintf(fp,"Single Spindle Rated Current(A)=%.1f\n",Configstruct.SpindleInfo.fSSRC);
	fprintf(fp,"Single Spindle Stall Current(A)=%.1f\n",Configstruct.SpindleInfo.fSSSC);
	fprintf(fp,"Single Spindle DC Brake Current(A)=%.1f\n",Configstruct.SpindleInfo.fSSDBC);
	fprintf(fp,"Low Switching Frequency(KHz)=%.1f\n",Configstruct.SpindleInfo.fPWMLF);
	fprintf(fp,"High Switching Frequency(KHz)=%.1f\n",Configstruct.SpindleInfo.fPWMHF);
	fprintf(fp,"PWM Switch Frequency(Hz)=%.1f\n",Configstruct.SpindleInfo.fPWMSF);
	
	fprintf(fp,"%s\n","[TOOL]");//[TOOL]
	fprintf(fp,"Auto Change Tool System=%s\n",Configstruct.ToolInfo.cACTS);
	fprintf(fp,"Change Tool Mode=%s\n",	Configstruct.ToolInfo.cChangeToolMode);//half auto  todo
	fprintf(fp,"Tool Room Type=%s\n",Configstruct.ToolInfo.cToolRoomType);
	fprintf(fp,"Max Tool Room Index=%d\n",Configstruct.ToolInfo.nMaxIndexOfToolRoom);
	fprintf(fp,"TR Cassette Number=%d\n",Configstruct.ToolInfo.nCassetteNumber);
	fprintf(fp,"1# TR Cassette Status=%s\n",Configstruct.ToolInfo.cTRCassetteStatus1);
	fprintf(fp,"2# TR Cassette Status=%s\n",Configstruct.ToolInfo.cTRCassetteStatus2);
	fprintf(fp,"Change Tool Distance Of Z1 Axis(um)=%d\n",Configstruct.ToolInfo.nZ1BasePos);
	fprintf(fp,"Change Tool Distance Of Z2 Axis(um)=%d\n",Configstruct.ToolInfo.nZ2BasePos);
	fprintf(fp,"Change Tool Distance Of Z3 Axis(um)=%d\n",Configstruct.ToolInfo.nZ3BasePos);
	fprintf(fp,"Change Tool Distance Of Z4 Axis(um)=%d\n",Configstruct.ToolInfo.nZ4BasePos);
	fprintf(fp,"Change Tool Distance Of Z5 Axis(um)=%d\n",Configstruct.ToolInfo.nZ5BasePos);
	fprintf(fp,"Change Tool Distance Of Z6 Axis(um)=%d\n",Configstruct.ToolInfo.nZ6BasePos);
	fprintf(fp,"Tool Room Space Of X Axis(um)=%d\n",Configstruct.ToolInfo.nXSpace);
	fprintf(fp,"Tool Room Space Of Y Axis(um)=%d\n",Configstruct.ToolInfo.nYSpace);
	fprintf(fp,"CTR X Position For Spindle(um)=%d\n",Configstruct.ToolInfo.nGPForSPX);
	fprintf(fp,"CTR Y Position For Spindle(um)=%d\n",Configstruct.ToolInfo.nGPForSPY);
	fprintf(fp,"CTR X Position For 1# Room(um)=%d\n",Configstruct.ToolInfo.nGPForRoom1X);
	fprintf(fp,"CTR Y Position For 1# Room(um)=%d\n",Configstruct.ToolInfo.nGPForRoom1Y);
	fprintf(fp,"CTR X Position For 81# Room(um)=%d\n",Configstruct.ToolInfo.nGPForRoom81X);
	fprintf(fp,"CTR Y Position For 81# Room(um)=%d\n",Configstruct.ToolInfo.nGPForRoom81Y);
	fprintf(fp,"Tool Max Life=%d\n",Configstruct.ToolInfo.unToolMaxLife);
	fprintf(fp,"Change Tool Message At Tool Die=%s\n",Configstruct.ToolInfo.cCTMATToolDie);//todo
	fprintf(fp,"Current Tool Room Index=%d\n",Configstruct.ToolInfo.nCurrentToolRoom);
	fprintf(fp,"Grip Finger Open Delay Time(ms)=%d\n",Configstruct.ToolInfo.unGripFingerOpenDelayTime);
	fprintf(fp,"Grip Finger Close Delay Time(ms)=%d\n",Configstruct.ToolInfo.unGripFingerCloseDelayTime);
	fprintf(fp,"Raised Grip Delay Time(ms)=%d\n",Configstruct.ToolInfo.unRaisedGripDelayTime);
	fprintf(fp,"Change Tool Compensation For Z1 Axis(um)=%d\n",Configstruct.ToolInfo.nACTCompensation[0]);
	fprintf(fp,"Change Tool Compensation For Z2 Axis(um)=%d\n",Configstruct.ToolInfo.nACTCompensation[1]);
	fprintf(fp,"Change Tool Compensation For Z3 Axis(um)=%d\n",Configstruct.ToolInfo.nACTCompensation[2]);
	fprintf(fp,"Change Tool Compensation For Z4 Axis(um)=%d\n",Configstruct.ToolInfo.nACTCompensation[3]);
	fprintf(fp,"Change Tool Compensation For Z5 Axis(um)=%d\n",Configstruct.ToolInfo.nACTCompensation[4]);
	fprintf(fp,"Change Tool Compensation For Z6 Axis(um)=%d\n",Configstruct.ToolInfo.nACTCompensation[5]);

	fprintf(fp,"%s\n","[DRILL]");//[DRILL]
	fprintf(fp,"Min Drill Tool Diameter(um)=%.1f\n",Configstruct.DrillInfo.fMinTDia);
	fprintf(fp,"Tool Deviate Table Height(um)=%d\n",Configstruct.DrillInfo.nTDTH);
	fprintf(fp,"Underlay Thickness(um)=%d\n",Configstruct.DrillInfo.nLT);
	fprintf(fp,"UnderLay Drill Depth(um)=%d\n",Configstruct.DrillInfo.nLDD);
	fprintf(fp,"Workpiece Thickness(um)=%d\n",Configstruct.DrillInfo.nBT);
	fprintf(fp,"Secure Workpiece Thickness(um)=%d\n",Configstruct.DrillInfo.nSecureBT);
	fprintf(fp,"Foot Deviate Board Clearance(um)=%d\n",Configstruct.DrillInfo.nFDBC);
	fprintf(fp,"Tool Deviate Foot Clearance(um)=%d\n",Configstruct.DrillInfo.nTDFC);
	fprintf(fp,"Drill Ajust Of X Axis(um)=%d\n",Configstruct.DrillInfo.nXDrillAjust);
	fprintf(fp,"Drill Ajust Of Y Axis(um)=%d\n",Configstruct.DrillInfo.nYDrillAjust);
	fprintf(fp,"Drill Fixed Compensation Of X Axis(um/mm)=%d\n",Configstruct.DrillInfo.nXDrillFixedCompensation);
	fprintf(fp,"Drill Fixed Compensation Of Y Axis(um/mm)=%d\n",Configstruct.DrillInfo.nYDrillFixedCompensation);
	fprintf(fp,"Drill Down Speed Scale=%.1f\n",Configstruct.DrillInfo.fDnSpdScale);
	fprintf(fp,"QDF Advanced Compensation Of Z Axes(um)=%d\n",Configstruct.DrillInfo.nQDFZAdvCom);
	fprintf(fp,"QDF Z Shift Down Time(ms)=%d\n",Configstruct.DrillInfo.unZShiftDnTime);
	fprintf(fp,"AWZ Offset Of X Axis(um)=%d\n",Configstruct.DrillInfo.nXAWZOffset);
	fprintf(fp,"AWZ Offset Of Y Axis(um)=%d\n",Configstruct.DrillInfo.nYAWZOffset);
	fprintf(fp,"Line Slot Precision(um)=%d\n",Configstruct.DrillInfo.nLSPre);
	fprintf(fp,"Short Line Slot Compensation Of X Axis(um)=%d\n",Configstruct.DrillInfo.nXShortLineSlotCompensation);
	fprintf(fp,"Short Line Slot Compensation Of Y Axis(um)=%d\n",Configstruct.DrillInfo.nYShortLineSlotCompensation);
	fprintf(fp,"Auto Pilot Hole=%s\n",Configstruct.DrillInfo.cAutoPilotHole);
	
	
	fprintf(fp,"%s\n","[INSPECT]");//[INSPECT]
	fprintf(fp,"Break Tool Check=%s\n",Configstruct.InspectInfo.cBTC);
	fprintf(fp,"Tool Depth Check=%s\n",Configstruct.InspectInfo.cTDC);
	fprintf(fp,"Tool Depth Check At Drilled=%s\n",Configstruct.InspectInfo.cDrilledTDC);
	fprintf(fp,"Auto Tool Depth Ajust=%s\n",Configstruct.InspectInfo.cATDA);
	fprintf(fp,"Auto Check Board Thickness=%s\n",Configstruct.InspectInfo.cAutoCheckBoardThickness);//todo 
	fprintf(fp,"ACBT Permit Error(um)=%d\n",Configstruct.InspectInfo.nACLBTErr);
	fprintf(fp,"TDC Position Of X Axis(um)=%d\n",Configstruct.InspectInfo.nTDCX);
	fprintf(fp,"TDC Position Of Y Axis(um)=%d\n",Configstruct.InspectInfo.nTDCY);
	fprintf(fp,"TDC Referenced Depth Of Z1 Axis(um)=%d\n",Configstruct.InspectInfo.nTDCRefDepthZ1);
	fprintf(fp,"TDC Referenced Depth Of Z2 Axis(um)=%d\n",Configstruct.InspectInfo.nTDCRefDepthZ2);
	fprintf(fp,"TDC Referenced Depth Of Z3 Axis(um)=%d\n",Configstruct.InspectInfo.nTDCRefDepthZ3);
	fprintf(fp,"TDC Referenced Depth Of Z4 Axis(um)=%d\n",Configstruct.InspectInfo.nTDCRefDepthZ4);
	fprintf(fp,"TDC Referenced Depth Of Z5 Axis(um)=%d\n",Configstruct.InspectInfo.nTDCRefDepthZ5);
	fprintf(fp,"TDC Referenced Depth Of Z6 Axis(um)=%d\n",Configstruct.InspectInfo.nTDCRefDepthZ6);
    fprintf(fp,"Tool Diameter Measure=%s\n",Configstruct.InspectInfo.cToolDiameterMeasure);	
	fprintf(fp,"TDC Permit Min Error(um)=%d\n",Configstruct.InspectInfo.nTDCPmtMinErr);
	fprintf(fp,"TDC Permit Max Error(um)=%d\n",Configstruct.InspectInfo.nTDCPmtMaxErr);
	fprintf(fp,"TDC Z Axes Move Velocity(mm/min)=%d\n",Configstruct.InspectInfo.unTDCZVelocity);
	fprintf(fp,"TRC Table Move Velocity(um/s)=%d\n",Configstruct.InspectInfo.nTableMvSP);
	fprintf(fp,"TRC Spindle Min RPM=%d\n",Configstruct.InspectInfo.unSPRev);
	fprintf(fp,"TRC Signal Numbers=%d\n",Configstruct.InspectInfo.nSigNum);
	fprintf(fp,"TRC Blow Time(ms)=%d\n",Configstruct.InspectInfo.unBlowTime);
	fprintf(fp,"New Tool Diameter Check=%s\n",Configstruct.InspectInfo.cNewToolDiameterCheck);//todo
	fprintf(fp,"All Tool Diameter Check=%s\n",Configstruct.InspectInfo.cAllToolDiameterCheck);//todo
	fprintf(fp,"DO TMC After Spindle Stop Time(s)=%d\n",Configstruct.InspectInfo.unDoTMSAfterSpindleStop);
	
	fprintf(fp,"%s\n","[PRESSUREFOOT]");//[PRESSUREFOOT]
	fprintf(fp,"Auto Change Foot=%s\n",Configstruct.PressureFootInfo.cACF);
	fprintf(fp,"ACF Check Timeouts(ms)=%d\n",Configstruct.PressureFootInfo.nACFChkTimeouts);
	fprintf(fp,"FBP Check Timeouts(ms)=%d\n",Configstruct.PressureFootInfo.nFBPChkTimeouts);
	fprintf(fp,"FTP Check Timeouts(ms)=%d\n",Configstruct.PressureFootInfo.nFTPChkTimeouts);
	fprintf(fp,"QIC FBP Check Timeouts(ms)=%d\n",Configstruct.PressureFootInfo.nQICFBPChkTimeouts);
	fprintf(fp,"TDL Check Timeouts(ms)=%d\n",Configstruct.PressureFootInfo.nTDLChkTimeouts);
	fprintf(fp,"Max Diameter Of ACFS(um)=%d\n",Configstruct.PressureFootInfo.nACFSMaxDia);
	fprintf(fp,"Diameter Error Of ACFS(um)=%d\n",Configstruct.PressureFootInfo.nACFDiaErr);

	fprintf(fp,"%s\n","[FILTER]");//[FILTER]
	fprintf(fp,"Repeat Number BTC=%d\n",Configstruct.FilterInfo.nPmtBTNum);
	fprintf(fp,"Forbid CBD Under Spindle Rev(rpm)=%d\n",Configstruct.FilterInfo.unInhCBDRev);
	fprintf(fp,"Edge Check For BTC=%s\n",Configstruct.FilterInfo.cEdgeCheckForBTC);//todo  
	fprintf(fp,"Edge Distance For BTC(um)=%d\n",Configstruct.FilterInfo.nBTCEdgeDistance);
	
	fprintf(fp,"%s\n","[OTHER]");//[OTHER]
    fprintf(fp,"COM=%s\n",Configstruct.OtherInfo.cCOM);
	fprintf(fp,"COM Baudrate=%d\n",Configstruct.OtherInfo.nCOMBaudrate);
	fprintf(fp,"COM Data Bits=%d\n",Configstruct.OtherInfo.nCOMDataBits);
	fprintf(fp,"COM Parity Check=%s\n",Configstruct.OtherInfo.cCOMParityCheck);
	fprintf(fp,"COM Data Stop Bits=%d\n",Configstruct.OtherInfo.nCOMDataStopBits);
	fprintf(fp,"COM Transmit Mode=%s\n",Configstruct.OtherInfo.cTransmitMode);
	fprintf(fp,"Machine Debug Mode=%s\n",Configstruct.OtherInfo.cDebugMode);

	fprintf(fp,"%s\n","[FILE]");//[FILE]
	fprintf(fp,"ATPFileName=%s\n",Configstruct.FileInfo.cATPfilename);
	fprintf(fp,"MastProgFileName=%s\n",Configstruct.FileInfo.cmastprogfilename);
	fprintf(fp,"DIAFileName=%s\n",Configstruct.FileInfo.cDIAfilename);
	fprintf(fp,"MastProgDefaultPaths=%s\n",Configstruct.FileInfo.cmastprogpath);
	fprintf(fp,"SubProgDefaultPaths=%s\n",Configstruct.FileInfo.csubprogpath);
	fprintf(fp,"ATPDefaultPaths=%s\n",Configstruct.FileInfo.catppath);

	fprintf(fp,"%s\n","[WORKLIMIT]");//[WORKLIMIT]
	fprintf(fp,"ModefyLeftWorkLimit=%d\n",Configstruct.WorkLimitInfo.modefyLeftWorkLimit);
	fprintf(fp,"ModefyRightWorkLimit=%d\n",Configstruct.WorkLimitInfo.modefyRightWorkLimit);
	fprintf(fp,"ModefyFrontWorkLimit=%d\n",Configstruct.WorkLimitInfo.modefyFrontWorkLimit);
	fprintf(fp,"ModefyBackWorkLimit=%d\n",Configstruct.WorkLimitInfo.modefyBackWorkLimit);
	fprintf(fp,"%s\n","[STRETCH_ROTATE]");//[STRETCH_ROTATE]
	fprintf(fp,"SA_Xpos=%.3f\n",Configstruct.Stretch_RotateInfo.xcenterpos);
	fprintf(fp,"SA_Ypos=%.3f\n",Configstruct.Stretch_RotateInfo.ycenterpos);
	fprintf(fp,"SA_Xscale=%.3f\n",Configstruct.Stretch_RotateInfo.xscale);
	fprintf(fp,"SA_Yscale=%.3f\n",Configstruct.Stretch_RotateInfo.yscale);
	fprintf(fp,"RA_Xpos=%.3f\n",Configstruct.Stretch_RotateInfo.xrapos);
	fprintf(fp,"RA_Ypos=%.3f\n",Configstruct.Stretch_RotateInfo.yrapos);
	fprintf(fp,"%s\n","[CURRENTDRILL]");//[CURRENTDRILL]
	fprintf(fp,"Current ToolNum=%d\n",Configstruct.CurrentDrillInfo.currenttoolnum);
	fprintf(fp,"Current DrillNum=%d\n",Configstruct.CurrentDrillInfo.currentdrillnum);
	fprintf(fp,"Current Work_VER=%d\n",Configstruct.CurrentDrillInfo.currentwork_ver);
	fprintf(fp,"%s\n","[ZAXIS]");//[ZAXIS]
	fprintf(fp,"H Value=%.3f\n",Configstruct.ZaxisInfo.ZaxisH);
	fprintf(fp,"Q Value=%.3f\n",Configstruct.ZaxisInfo.ZaxisQ);
	fprintf(fp,"K Value=%.3f\n",Configstruct.ZaxisInfo.ZaxisK);
	fprintf(fp,"Z Value=%.3f\n",Configstruct.ZaxisInfo.ZaxisZ);
	fprintf(fp,"SUTO Value=%.3f\n",Configstruct.ZaxisInfo.ZaxisSUTO);
	fprintf(fp,"TOTO Value=%.3f\n",Configstruct.ZaxisInfo.ZaxisTOTO);
	fprintf(fp,"%s\n","[INCHINGFUNCTION]");//[INCHINGFUNCTION]
	fprintf(fp,"XY Inching Speed(mm/min)=%.3f\n",Configstruct.InchingFunctionInfo.xyinchingspeed);
	fprintf(fp,"X Inching Step Distance(um)=%d\n",Configstruct.InchingFunctionInfo.xinchingstepdis);
	fprintf(fp,"Y Inching Step Distance(um)=%d\n",Configstruct.InchingFunctionInfo.yinchingstepdis);
	fprintf(fp,"Z Inching Step Distance(um)=%d\n",Configstruct.InchingFunctionInfo.zinchingstepdis);
	
	fprintf(fp,"%s\n","[MFUNCTION]");//[MFUNCTION]
	fprintf(fp,"M Function 1=%s\n",Configstruct.MfunctionInfo.mfun1);
	fprintf(fp,"M Function 2=%s\n",Configstruct.MfunctionInfo.mfun2);
	fprintf(fp,"M Function 3=%s\n",Configstruct.MfunctionInfo.mfun3);
	fprintf(fp,"M Function 4=%s\n",Configstruct.MfunctionInfo.mfun4);
	fprintf(fp,"M Function 5=%s\n",Configstruct.MfunctionInfo.mfun5);
	fprintf(fp,"M Function 6=%s\n",Configstruct.MfunctionInfo.mfun6);
	fprintf(fp,"M Function 7=%s\n",Configstruct.MfunctionInfo.mfun7);
	fprintf(fp,"M Function 8=%s\n",Configstruct.MfunctionInfo.mfun8);
	fprintf(fp,"M Function 9=%s\n",Configstruct.MfunctionInfo.mfun9);
	fprintf(fp,"M Function 10=%s\n",Configstruct.MfunctionInfo.mfun10);
	fprintf(fp,"M Function 11=%s\n",Configstruct.MfunctionInfo.mfun11);
	fprintf(fp,"M Function 12=%s\n",Configstruct.MfunctionInfo.mfun12);
	fprintf(fp,"M Function 13=%s\n",Configstruct.MfunctionInfo.mfun13);		
	fprintf(fp,"M Function 14=%s\n",Configstruct.MfunctionInfo.mfun14);
	fclose(fp);
	return 0;	
}

int CncControl::ReadConfigFileNew()
{
	FILE *fp;
	if((fp=fopen("HiCNC.ini","r"))==NULL)
		return -1;//文件打开失败
	CString sectionstr;

	fscanf(fp,"%s\n",sectionstr);//[SYSTEM]
	fscanf(fp,"XY Loop Type=%d\n",&Configstruct.SystemInfo.nLoopType);
	fscanf(fp,"X Axes Sensor Resolution(P/R)=%d\n",&Configstruct.SystemInfo.nXSensorResolution);
	fscanf(fp,"X Axes Screw Pitch(mm)=%d\n",&Configstruct.SystemInfo.nXScrewPitch);
	fscanf(fp,"Y Axes Sensor Resolution(P/R)=%d\n",&Configstruct.SystemInfo.nYSensorResolution);
	fscanf(fp,"Y Axes Screw Pitch(mm)=%d\n",&Configstruct.SystemInfo.nYScrewPitch);
	fscanf(fp,"Z Axes Sensor Resolution(P/R)=%d\n",&Configstruct.SystemInfo.nZSensorResolution);
	fscanf(fp,"Z Axes Screw Pitch(mm)=%d\n",&Configstruct.SystemInfo.nZScrewPitch);
	fscanf(fp,"X Axis Left Limit Voyage(um)=%d\n",&Configstruct.SystemInfo.nXLeftLimit);	
	fscanf(fp,"X Axis Right Limit Voyage(um)=%d\n",&Configstruct.SystemInfo.nXRightLimit);
	fscanf(fp,"Y Axis Front Limit Voyage(um)=%d\n",&Configstruct.SystemInfo.nYFrontLimit);
	fscanf(fp,"Y Axis Back Limit Voyage(um)=%d\n",&Configstruct.SystemInfo.nYBackLimit);
	fscanf(fp,"X Axis Pin Position(um)=%d\n",&Configstruct.SystemInfo.nXPinPosition);
	fscanf(fp,"Y Axis Pin Position(um)=%d\n",&Configstruct.SystemInfo.nYPinPosition);
	fscanf(fp,"Y Axis Work Table Start Position(um)=%d\n",&Configstruct.SystemInfo.nYWTStPos);
	fscanf(fp,"Z Axes Save Voyage(um)=%d\n",&Configstruct.SystemInfo.nZSaveVoyage);
	fscanf(fp,"Z1 Axes Work Zero(um)=%d\n",&Configstruct.SystemInfo.nZWorkZeroOffset[0]);
	fscanf(fp,"Z2 Axes Work Zero(um)=%d\n",&Configstruct.SystemInfo.nZWorkZeroOffset[1]);
	fscanf(fp,"Z3 Axes Work Zero(um)=%d\n",&Configstruct.SystemInfo.nZWorkZeroOffset[2]);
	fscanf(fp,"Z4 Axes Work Zero(um)=%d\n",&Configstruct.SystemInfo.nZWorkZeroOffset[3]);
	fscanf(fp,"Z5 Axes Work Zero(um)=%d\n",&Configstruct.SystemInfo.nZWorkZeroOffset[4]);
	fscanf(fp,"Z6 Axes Work Zero(um)=%d\n",&Configstruct.SystemInfo.nZWorkZeroOffset[5]);
	fscanf(fp,"XY Axes Max Move Velocity(mm/min)=%d\n",&Configstruct.SystemInfo.unXYMaxSpeed);
	fscanf(fp,"XY Axes Acceleration(mm/s2)=%d\n",&Configstruct.SystemInfo.unXYAcc);
	fscanf(fp,"XY Axes Deceleration(mm/s2)=%d\n",&Configstruct.SystemInfo.unXYDcc);
	fscanf(fp,"Z Axes Max Move Velocity(mm/min)=%d\n",&Configstruct.SystemInfo.unZMaxVelocity);
	fscanf(fp,"Z Axes Acceleration(mm/s2)=%d\n",&Configstruct.SystemInfo.unZAcc);
	fscanf(fp,"Z Axes Deceleration(mm/s2)=%d\n",&Configstruct.SystemInfo.unZDcc);
	fscanf(fp,"X Axis Smooth Factor(ms)=%d\n",&Configstruct.SystemInfo.nXSFTime);
	fscanf(fp,"Y Axis Smooth Factor(ms)=%d\n",&Configstruct.SystemInfo.nYSFTime);
	fscanf(fp,"Z Axes Smooth Factor(ms)=%d\n",&Configstruct.SystemInfo.nZSFTime);
	fscanf(fp,"X Axis Setting Position Error(um)=%d\n",&Configstruct.SystemInfo.nXSPE);
	fscanf(fp,"Y Axis Setting Position Error(um)=%d\n",&Configstruct.SystemInfo.nYSPE);
	fscanf(fp,"XY Axes Allowed Position Error(um)=%d\n",&Configstruct.SystemInfo.nXYAllowedPE);
	fscanf(fp,"X Axis Distance Of HMI To HMS(um)=%d\n",&Configstruct.SystemInfo.nXHMItoS);
	fscanf(fp,"Y Axis Distance Of HMI To HMS(um)=%d\n",&Configstruct.SystemInfo.nYHMItoS);
	fscanf(fp,"X Axis Work Zero(um)=%d\n",&Configstruct.SystemInfo.nXWorkZero);
	fscanf(fp,"Y Axis Work Zero(um)=%d\n",&Configstruct.SystemInfo.nYWorkZero);
	
	fscanf(fp,"%s\n",sectionstr);//[SPINDLE]
	fscanf(fp,"Spindle Numbers=%d\n",&Configstruct.SpindleInfo.nSpindleNumbers);
	fscanf(fp,"Z Axes Switch Status=%s\n",Configstruct.SpindleInfo.cZAxesStatus);
	fscanf(fp,"Spindle Type=%s\n",Configstruct.SpindleInfo.cSpindleType);
	fscanf(fp,"Spindle Min Rpm=%d\n",&Configstruct.SpindleInfo.unSpindleMinRev);
	fscanf(fp,"Spindle Max Rpm=%d\n",&Configstruct.SpindleInfo.unSpindleMaxRev);
	fscanf(fp,"Inverter=%s\n",Configstruct.SpindleInfo.cInverter);//todo
	fscanf(fp,"Last Stop Time=%s\n",Configstruct.SpindleInfo.cLastStopTime);
	fscanf(fp,"Inverter ADcc Time(S)=%f\n",&Configstruct.SpindleInfo.fADccTime);
	fscanf(fp,"INV Rated Current(A)=%f\n",&Configstruct.SpindleInfo.fINVRatedCurrent);
	fscanf(fp,"Single Spindle Rated Power(KW)=%f\n",&Configstruct.SpindleInfo.fRatedPower);
	fscanf(fp,"Single Spindle Full Load Current(A)=%f\n",&Configstruct.SpindleInfo.fFullLoadCurrent);
	fscanf(fp,"Single Spindle Empty Load Current(A)=%f\n",&Configstruct.SpindleInfo.fEmptyLoadCurrent);
	fscanf(fp,"Single Spindle Torque Compensate(%%)=%f\n",&Configstruct.SpindleInfo.fTorqueCompensate);
	fscanf(fp,"Single Spindle Prevent Over Current in Accelerating(%%)=%f\n",&Configstruct.SpindleInfo.fPOCAcc);
	fscanf(fp,"Single Spindle Prevent Over Current in Running(%%)=%f\n",&Configstruct.SpindleInfo.fPOCRun);
	fscanf(fp,"Single Spindle Over Torque Check Level(%%)=%f\n",&Configstruct.SpindleInfo.fPOT);
	fscanf(fp,"Single Spindle DC Brake Level(%%)=%f\n",&Configstruct.SpindleInfo.fDCBrake);
	fscanf(fp,"Single Spindle Current Limit(A)=%f\n",&Configstruct.SpindleInfo.fSSCL);
	fscanf(fp,"Single Spindle Rated Current(A)=%f\n",&Configstruct.SpindleInfo.fSSRC);
	fscanf(fp,"Single Spindle Stall Current(A)=%f\n",&Configstruct.SpindleInfo.fSSSC);
	fscanf(fp,"Single Spindle DC Brake Current(A)=%f\n",&Configstruct.SpindleInfo.fSSDBC);
	fscanf(fp,"Low Switching Frequency(KHz)=%f\n",&Configstruct.SpindleInfo.fPWMLF);
	fscanf(fp,"High Switching Frequency(KHz)=%f\n",&Configstruct.SpindleInfo.fPWMHF);
	fscanf(fp,"PWM Switch Frequency(Hz)=%f\n",&Configstruct.SpindleInfo.fPWMSF);
	
	fscanf(fp,"%s\n",sectionstr);//[TOOL]
	fscanf(fp,"Auto Change Tool System=%s\n",Configstruct.ToolInfo.cACTS);
	fscanf(fp,"Change Tool Mode=%s\n",	Configstruct.ToolInfo.cChangeToolMode);//half auto  todo
	fscanf(fp,"Tool Room Type=%s\n",Configstruct.ToolInfo.cToolRoomType);
	fscanf(fp,"Max Tool Room Index=%d\n",&Configstruct.ToolInfo.nMaxIndexOfToolRoom);
	fscanf(fp,"TR Cassette Number=%d\n",&Configstruct.ToolInfo.nCassetteNumber);
	fscanf(fp,"1# TR Cassette Status=%s\n",Configstruct.ToolInfo.cTRCassetteStatus1);
	fscanf(fp,"2# TR Cassette Status=%s\n",Configstruct.ToolInfo.cTRCassetteStatus2);
	fscanf(fp,"Change Tool Distance Of Z1 Axis(um)=%d\n",&Configstruct.ToolInfo.nZ1BasePos);
	fscanf(fp,"Change Tool Distance Of Z2 Axis(um)=%d\n",&Configstruct.ToolInfo.nZ2BasePos);
	fscanf(fp,"Change Tool Distance Of Z3 Axis(um)=%d\n",&Configstruct.ToolInfo.nZ3BasePos);
	fscanf(fp,"Change Tool Distance Of Z4 Axis(um)=%d\n",&Configstruct.ToolInfo.nZ4BasePos);
	fscanf(fp,"Change Tool Distance Of Z5 Axis(um)=%d\n",&Configstruct.ToolInfo.nZ5BasePos);
	fscanf(fp,"Change Tool Distance Of Z6 Axis(um)=%d\n",&Configstruct.ToolInfo.nZ6BasePos);
	fscanf(fp,"Tool Room Space Of X Axis(um)=%d\n",&Configstruct.ToolInfo.nXSpace);
	fscanf(fp,"Tool Room Space Of Y Axis(um)=%d\n",&Configstruct.ToolInfo.nYSpace);
	fscanf(fp,"CTR X Position For Spindle(um)=%d\n",&Configstruct.ToolInfo.nGPForSPX);
	fscanf(fp,"CTR Y Position For Spindle(um)=%d\n",&Configstruct.ToolInfo.nGPForSPY);
	fscanf(fp,"CTR X Position For 1# Room(um)=%d\n",&Configstruct.ToolInfo.nGPForRoom1X);
	fscanf(fp,"CTR Y Position For 1# Room(um)=%d\n",&Configstruct.ToolInfo.nGPForRoom1Y);
	fscanf(fp,"CTR X Position For 81# Room(um)=%d\n",&Configstruct.ToolInfo.nGPForRoom81X);
	fscanf(fp,"CTR Y Position For 81# Room(um)=%d\n",&Configstruct.ToolInfo.nGPForRoom81Y);
	fscanf(fp,"Tool Max Life=%d\n",&Configstruct.ToolInfo.unToolMaxLife);
	fscanf(fp,"Change Tool Message At Tool Die=%s\n",Configstruct.ToolInfo.cCTMATToolDie);//todo   
	fscanf(fp,"Current Tool Room Index=%d\n",&Configstruct.ToolInfo.nCurrentToolRoom);
	fscanf(fp,"Grip Finger Open Delay Time(ms)=%d\n",&Configstruct.ToolInfo.unGripFingerOpenDelayTime);
	fscanf(fp,"Grip Finger Close Delay Time(ms)=%d\n",&Configstruct.ToolInfo.unGripFingerCloseDelayTime);
	fscanf(fp,"Raised Grip Delay Time(ms)=%d\n",&Configstruct.ToolInfo.unRaisedGripDelayTime);
	fscanf(fp,"Change Tool Compensation For Z1 Axis(um)=%d\n",&Configstruct.ToolInfo.nACTCompensation[0]);
	fscanf(fp,"Change Tool Compensation For Z2 Axis(um)=%d\n",&Configstruct.ToolInfo.nACTCompensation[1]);
	fscanf(fp,"Change Tool Compensation For Z3 Axis(um)=%d\n",&Configstruct.ToolInfo.nACTCompensation[2]);
	fscanf(fp,"Change Tool Compensation For Z4 Axis(um)=%d\n",&Configstruct.ToolInfo.nACTCompensation[3]);
	fscanf(fp,"Change Tool Compensation For Z5 Axis(um)=%d\n",&Configstruct.ToolInfo.nACTCompensation[4]);
	fscanf(fp,"Change Tool Compensation For Z6 Axis(um)=%d\n",&Configstruct.ToolInfo.nACTCompensation[5]);
	
	fscanf(fp,"%s\n",sectionstr);//[DRILL]
	fscanf(fp,"Min Drill Tool Diameter(um)=%f\n",&Configstruct.DrillInfo.fMinTDia);
	fscanf(fp,"Tool Deviate Table Height(um)=%d\n",&Configstruct.DrillInfo.nTDTH);
	fscanf(fp,"Underlay Thickness(um)=%d\n",&Configstruct.DrillInfo.nLT);
	fscanf(fp,"UnderLay Drill Depth(um)=%d\n",&Configstruct.DrillInfo.nLDD);
	fscanf(fp,"Workpiece Thickness(um)=%d\n",&Configstruct.DrillInfo.nBT);
	fscanf(fp,"Secure Workpiece Thickness(um)=%d\n",&Configstruct.DrillInfo.nSecureBT);
	fscanf(fp,"Foot Deviate Board Clearance(um)=%d\n",&Configstruct.DrillInfo.nFDBC);
	fscanf(fp,"Tool Deviate Foot Clearance(um)=%d\n",&Configstruct.DrillInfo.nTDFC);
	fscanf(fp,"Drill Ajust Of X Axis(um)=%d\n",&Configstruct.DrillInfo.nXDrillAjust);
	fscanf(fp,"Drill Ajust Of Y Axis(um)=%d\n",&Configstruct.DrillInfo.nYDrillAjust);
	fscanf(fp,"Drill Fixed Compensation Of X Axis(um/mm)=%d\n",&Configstruct.DrillInfo.nXDrillFixedCompensation);
	fscanf(fp,"Drill Fixed Compensation Of Y Axis(um/mm)=%d\n",&Configstruct.DrillInfo.nYDrillFixedCompensation);
	fscanf(fp,"Drill Down Speed Scale=%f\n",&Configstruct.DrillInfo.fDnSpdScale);
	fscanf(fp,"QDF Advanced Compensation Of Z Axes(um)=%d\n",&Configstruct.DrillInfo.nQDFZAdvCom);
	fscanf(fp,"QDF Z Shift Down Time(ms)=%d\n",&Configstruct.DrillInfo.unZShiftDnTime);
	fscanf(fp,"AWZ Offset Of X Axis(um)=%d\n",&Configstruct.DrillInfo.nXAWZOffset);
	fscanf(fp,"AWZ Offset Of Y Axis(um)=%d\n",&Configstruct.DrillInfo.nYAWZOffset);
	fscanf(fp,"Line Slot Precision(um)=%d\n",&Configstruct.DrillInfo.nLSPre);
	fscanf(fp,"Short Line Slot Compensation Of X Axis(um)=%d\n",&Configstruct.DrillInfo.nXShortLineSlotCompensation);
	fscanf(fp,"Short Line Slot Compensation Of Y Axis(um)=%d\n",&Configstruct.DrillInfo.nYShortLineSlotCompensation);
	fscanf(fp,"Auto Pilot Hole=%s\n",Configstruct.DrillInfo.cAutoPilotHole);
	
	fscanf(fp,"%s\n",sectionstr);//[INSPECT]
	fscanf(fp,"Break Tool Check=%s\n",Configstruct.InspectInfo.cBTC);
	fscanf(fp,"Tool Depth Check=%s\n",Configstruct.InspectInfo.cTDC);
	fscanf(fp,"Tool Depth Check At Drilled=%s\n",Configstruct.InspectInfo.cDrilledTDC);
	fscanf(fp,"Auto Tool Depth Ajust=%s\n",Configstruct.InspectInfo.cATDA);
	fscanf(fp,"Auto Check Board Thickness=%s\n",Configstruct.InspectInfo.cAutoCheckBoardThickness);
	fscanf(fp,"ACBT Permit Error(um)=%d\n",&Configstruct.InspectInfo.nACLBTErr);
	fscanf(fp,"TDC Position Of X Axis(um)=%d\n",&Configstruct.InspectInfo.nTDCX);
	fscanf(fp,"TDC Position Of Y Axis(um)=%d\n",&Configstruct.InspectInfo.nTDCY);
	fscanf(fp,"TDC Referenced Depth Of Z1 Axis(um)=%d\n",&Configstruct.InspectInfo.nTDCRefDepthZ1);
	fscanf(fp,"TDC Referenced Depth Of Z2 Axis(um)=%d\n",&Configstruct.InspectInfo.nTDCRefDepthZ2);
	fscanf(fp,"TDC Referenced Depth Of Z3 Axis(um)=%d\n",&Configstruct.InspectInfo.nTDCRefDepthZ3);
	fscanf(fp,"TDC Referenced Depth Of Z4 Axis(um)=%d\n",&Configstruct.InspectInfo.nTDCRefDepthZ4);
	fscanf(fp,"TDC Referenced Depth Of Z5 Axis(um)=%d\n",&Configstruct.InspectInfo.nTDCRefDepthZ5);
	fscanf(fp,"TDC Referenced Depth Of Z6 Axis(um)=%d\n",&Configstruct.InspectInfo.nTDCRefDepthZ6);
	fscanf(fp,"Tool Diameter Measure=%s\n",Configstruct.InspectInfo.cToolDiameterMeasure);	
	fscanf(fp,"TDC Permit Min Error(um)=%d\n",&Configstruct.InspectInfo.nTDCPmtMinErr);
	fscanf(fp,"TDC Permit Max Error(um)=%d\n",&Configstruct.InspectInfo.nTDCPmtMaxErr);
	fscanf(fp,"TDC Z Axes Move Velocity(mm/min)=%d\n",&Configstruct.InspectInfo.unTDCZVelocity);
	fscanf(fp,"TRC Table Move Velocity(um/s)=%d\n",&Configstruct.InspectInfo.nTableMvSP);
	fscanf(fp,"TRC Spindle Min RPM=%d\n",&Configstruct.InspectInfo.unSPRev);
	fscanf(fp,"TRC Signal Numbers=%d\n",&Configstruct.InspectInfo.nSigNum);
	fscanf(fp,"TRC Blow Time(ms)=%d\n",&Configstruct.InspectInfo.unBlowTime);
	fscanf(fp,"New Tool Diameter Check=%s\n",Configstruct.InspectInfo.cNewToolDiameterCheck);//todo
	fscanf(fp,"All Tool Diameter Check=%s\n",Configstruct.InspectInfo.cAllToolDiameterCheck);//todo
	fscanf(fp,"DO TMC After Spindle Stop Time(s)=%d\n",&Configstruct.InspectInfo.unDoTMSAfterSpindleStop);


	fscanf(fp,"%s\n",sectionstr);//[PRESSUREFOOT]
	fscanf(fp,"Auto Change Foot=%s\n",Configstruct.PressureFootInfo.cACF);
	fscanf(fp,"ACF Check Timeouts(ms)=%d\n",&Configstruct.PressureFootInfo.nACFChkTimeouts);
	fscanf(fp,"FBP Check Timeouts(ms)=%d\n",&Configstruct.PressureFootInfo.nFBPChkTimeouts);
	fscanf(fp,"FTP Check Timeouts(ms)=%d\n",&Configstruct.PressureFootInfo.nFTPChkTimeouts);
	fscanf(fp,"QIC FBP Check Timeouts(ms)=%d\n",&Configstruct.PressureFootInfo.nQICFBPChkTimeouts);
	fscanf(fp,"TDL Check Timeouts(ms)=%d\n",&Configstruct.PressureFootInfo.nTDLChkTimeouts);
	fscanf(fp,"Max Diameter Of ACFS(um)=%d\n",&Configstruct.PressureFootInfo.nACFSMaxDia);
	fscanf(fp,"Diameter Error Of ACFS(um)=%d\n",&Configstruct.PressureFootInfo.nACFDiaErr);
	
	
	fscanf(fp,"%s\n",sectionstr);//[FILTER]
	fscanf(fp,"Repeat Number BTC=%d\n",&Configstruct.FilterInfo.nPmtBTNum);
	fscanf(fp,"Forbid CBD Under Spindle Rev(rpm)=%d\n",&Configstruct.FilterInfo.unInhCBDRev);
	fscanf(fp,"Edge Check For BTC=%s\n",Configstruct.FilterInfo.cEdgeCheckForBTC);
	fscanf(fp,"Edge Distance For BTC(um)=%d\n",&Configstruct.FilterInfo.nBTCEdgeDistance);
	
	fscanf(fp,"%s\n",sectionstr);//[OTHER]
	fscanf(fp,"COM=%s\n",Configstruct.OtherInfo.cCOM);
	fscanf(fp,"COM Baudrate=%d\n",&Configstruct.OtherInfo.nCOMBaudrate);
	fscanf(fp,"COM Data Bits=%d\n",&Configstruct.OtherInfo.nCOMDataBits);
	fscanf(fp,"COM Parity Check=%s\n",Configstruct.OtherInfo.cCOMParityCheck);
	fscanf(fp,"COM Data Stop Bits=%d\n",&Configstruct.OtherInfo.nCOMDataStopBits);
	fscanf(fp,"COM Transmit Mode=%s\n",Configstruct.OtherInfo.cTransmitMode);
	fscanf(fp,"Machine Debug Mode=%s\n",Configstruct.OtherInfo.cDebugMode);
	
	fscanf(fp,"%s\n",sectionstr);//[FILE]
	fscanf(fp,"ATPFileName=%s\n",Configstruct.FileInfo.cATPfilename);
	fscanf(fp,"MastProgFileName=%s\n",Configstruct.FileInfo.cmastprogfilename);
	fscanf(fp,"DIAFileName=%s\n",Configstruct.FileInfo.cDIAfilename);
	fscanf(fp,"MastProgDefaultPaths=%s\n",Configstruct.FileInfo.cmastprogpath);
	fscanf(fp,"SubProgDefaultPaths=%s\n",Configstruct.FileInfo.csubprogpath);
	fscanf(fp,"ATPDefaultPaths=%s\n",Configstruct.FileInfo.catppath);
		
	fscanf(fp,"%s\n",sectionstr);//[WORKLIMIT]
	fscanf(fp,"ModefyLeftWorkLimit=%d\n",&Configstruct.WorkLimitInfo.modefyLeftWorkLimit);
	fscanf(fp,"ModefyRightWorkLimit=%d\n",&Configstruct.WorkLimitInfo.modefyRightWorkLimit);
	fscanf(fp,"ModefyFrontWorkLimit=%d\n",&Configstruct.WorkLimitInfo.modefyFrontWorkLimit);
	fscanf(fp,"ModefyBackWorkLimit=%d\n",&Configstruct.WorkLimitInfo.modefyBackWorkLimit);
	fscanf(fp,"%s\n",sectionstr);//[STRETCH_ROTATE]
	fscanf(fp,"SA_Xpos=%f\n",&Configstruct.Stretch_RotateInfo.xcenterpos);
	fscanf(fp,"SA_Ypos=%f\n",&Configstruct.Stretch_RotateInfo.ycenterpos);
	fscanf(fp,"SA_Xscale=%f\n",&Configstruct.Stretch_RotateInfo.xscale);
	fscanf(fp,"SA_Yscale=%f\n",&Configstruct.Stretch_RotateInfo.yscale);
	fscanf(fp,"RA_Xpos=%f\n",&Configstruct.Stretch_RotateInfo.xrapos);
	fscanf(fp,"RA_Ypos=%f\n",&Configstruct.Stretch_RotateInfo.yrapos);
	fscanf(fp,"%s\n",sectionstr);//[CURRENTDRILL]
	fscanf(fp,"Current ToolNum=%d\n",&Configstruct.CurrentDrillInfo.currenttoolnum);
	fscanf(fp,"Current DrillNum=%d\n",&Configstruct.CurrentDrillInfo.currentdrillnum);
	fscanf(fp,"Current Work_VER=%d\n",&Configstruct.CurrentDrillInfo.currentwork_ver);
	fscanf(fp,"%s\n",sectionstr);//[ZAXIS]
	fscanf(fp,"H Value=%f\n",&Configstruct.ZaxisInfo.ZaxisH);
	fscanf(fp,"Q Value=%f\n",&Configstruct.ZaxisInfo.ZaxisQ);
	fscanf(fp,"K Value=%f\n",&Configstruct.ZaxisInfo.ZaxisK);
	fscanf(fp,"Z Value=%f\n",&Configstruct.ZaxisInfo.ZaxisZ);
	fscanf(fp,"SUTO Value=%f\n",&Configstruct.ZaxisInfo.ZaxisSUTO);
	fscanf(fp,"TOTO Value=%f\n",&Configstruct.ZaxisInfo.ZaxisTOTO);
	fscanf(fp,"%s\n",sectionstr);//[INCHINGFUNCTION]
	fscanf(fp,"XY Inching Speed(mm/min)=%f\n",&Configstruct.InchingFunctionInfo.xyinchingspeed);
	fscanf(fp,"X Inching Step Distance(um)=%d\n",&Configstruct.InchingFunctionInfo.xinchingstepdis);
	fscanf(fp,"Y Inching Step Distance(um)=%d\n",&Configstruct.InchingFunctionInfo.yinchingstepdis);
	fscanf(fp,"Z Inching Step Distance(um)=%d\n",&Configstruct.InchingFunctionInfo.zinchingstepdis);
	fscanf(fp,"%s\n",sectionstr);//[MFUNCTION]
	fscanf(fp,"M Function 1=%s\n",Configstruct.MfunctionInfo.mfun1);
	fscanf(fp,"M Function 2=%s\n",Configstruct.MfunctionInfo.mfun2);
	fscanf(fp,"M Function 3=%s\n",Configstruct.MfunctionInfo.mfun3);
	fscanf(fp,"M Function 4=%s\n",Configstruct.MfunctionInfo.mfun4);
	fscanf(fp,"M Function 5=%s\n",Configstruct.MfunctionInfo.mfun5);
	fscanf(fp,"M Function 6=%s\n",Configstruct.MfunctionInfo.mfun6);
	fscanf(fp,"M Function 7=%s\n",Configstruct.MfunctionInfo.mfun7);
	fscanf(fp,"M Function 8=%s\n",Configstruct.MfunctionInfo.mfun8);
	fscanf(fp,"M Function 9=%s\n",Configstruct.MfunctionInfo.mfun9);
	fscanf(fp,"M Function 10=%s\n",Configstruct.MfunctionInfo.mfun10);
	fscanf(fp,"M Function 11=%s\n",Configstruct.MfunctionInfo.mfun11);
	fscanf(fp,"M Function 12=%s\n",Configstruct.MfunctionInfo.mfun12);
	fscanf(fp,"M Function 13=%s\n",Configstruct.MfunctionInfo.mfun13);
	fscanf(fp,"M Function 14=%s\n",Configstruct.MfunctionInfo.mfun14);	
	fclose(fp);
	return 0;
}

int CncControl::ConfigFileParameterCheck()
{
	int i;
	if(Configstruct.SpindleInfo.nSpindleNumbers < 0 || Configstruct.SpindleInfo.nSpindleNumbers > 6)
    {
		//TODO:添加报警代码
		//MessageBox("HiCNC.INI文件中Spindle Numbers信息没有或错误", "错误", MB_ICONERROR);
		return -1;
	}
	if(strcmp(Configstruct.SpindleInfo.cSpindleType , "Ball") && strcmp(Configstruct.SpindleInfo.cSpindleType , "Air"))
	{
		
		//MessageBox("HiCNC.INI文件中Spindle Type信息错误", "错误", MB_ICONERROR);
		return -1;
	}
	if(Configstruct.SpindleInfo.unSpindleMinRev <= 1000)
	{
		
		//MessageBox("HiCNC.INI文件中Spindle Min Rpm信息没有或错误", "错误", MB_ICONERROR);
		return -1;
	}
	if(Configstruct.SpindleInfo.unSpindleMaxRev < Configstruct.SpindleInfo.unSpindleMinRev)
	{
		
		//MessageBox("HiCNC.INI文件中Spindle Max Rpm信息没有或错误", "错误", MB_ICONERROR);
		return -1;
	}
	
//	int nLength = Configstruct.SpindleInfo.cZAxesStatus.GetLength();
	int nLength = strlen(Configstruct.SpindleInfo.cZAxesStatus);
	if(nLength < 6)
	{
		for(i = 6; i > nLength; i--)
			strcat(Configstruct.SpindleInfo.cZAxesStatus, "0");
	}
	for(i = 1; i <= Configstruct.SpindleInfo.nSpindleNumbers; i++)
	{
		if(Configstruct.SpindleInfo.cZAxesStatus[i-1] != '0' && Configstruct.SpindleInfo.cZAxesStatus[i-1] != '1')
		{
			
			//MessageBox("HiCNC.INI文件中Z Axes Switch Status信息错误", "错误",MB_ICONERROR);
			return -1;
		}
		else
		{
			if(Configstruct.SpindleInfo.cZAxesStatus[i-1] == '0')
				Configstruct2.nZAxesStatus[i-1] = 0;
			else
				Configstruct2.nZAxesStatus[i-1] = 1;
		}
	}
	for(i = 6; i > Configstruct.SpindleInfo.nSpindleNumbers; i--)
	{
	//删	Configstruct.SpindleInfo.cZAxesStatus.SetAt(i-1, '0');
		Configstruct.SpindleInfo.cZAxesStatus[i-1]= '0';
		Configstruct2.nZAxesStatus[i-1] = 0;
	}
	if(Configstruct.SystemInfo.nLoopType != 5 && Configstruct.SystemInfo.nLoopType != 4)
	{
		//MessageBox("HiCNC.INI文件中XY Loop Type信息没有或错误", "错误", MB_ICONERROR);
		return -1;
	}
	
	if(Configstruct.SystemInfo.nXSensorResolution < 2000 || Configstruct.SystemInfo.nXSensorResolution > 131072)
	{
		//MessageBox("HiCNC.INI文件中X Axes Sensor Resolution(P/R)信息没有或错误", "错误", MB_ICONERROR);
		return -1;
	}
	if(Configstruct.SystemInfo.nXScrewPitch < 5 || Configstruct.SystemInfo.nXScrewPitch > 30)
	{
		//MessageBox("HiCNC.INI文件中X Axes Screw Pitch(mm)信息没有或错误", "错误", MB_ICONERROR);
		return -1;
	}
//move	Configstruct2.fXEGear = (float)(Configstruct.SystemInfo.nXScrewPitch*1000.0/((float)Configstruct.SystemInfo.nXSensorResolution*4));
	if(Configstruct.SystemInfo.nYSensorResolution < 2000 || Configstruct.SystemInfo.nYSensorResolution > 131072)
	{
		//MessageBox("HiCNC.INI文件中Y Axes Sensor Resolution(P/R)信息没有或错误", "错误", MB_ICONERROR);
		return -1;
	}
	if(Configstruct.SystemInfo.nYScrewPitch < 5 || Configstruct.SystemInfo.nYScrewPitch > 30)
	{
		//MessageBox("HiCNC.INI文件中Y Axes Screw Pitch(mm)信息没有或错误", "错误", MB_ICONERROR);
		return -1;
	}
//move Configstruct2.fYEGear = (float)(Configstruct.SystemInfo.nYScrewPitch*1000.0/((float)Configstruct.SystemInfo.nYSensorResolution*4));
	if(Configstruct.SystemInfo.nZSensorResolution < 2000 || Configstruct.SystemInfo.nZSensorResolution > 131072)
	{
		//MessageBox("HiCNC.INI文件中Z Axes Sensor Resolution(P/R)信息没有或错误", "错误", MB_ICONERROR);
		return -1;
	}
	if(Configstruct.SystemInfo.nZScrewPitch < 5 || Configstruct.SystemInfo.nZScrewPitch > 30)
	{
		//MessageBox("HiCNC.INI文件中Z Axes Screw Pitch(mm)信息没有或错误", "错误", MB_ICONERROR);
		return -1;
	}
//move	Configstruct2.fZEGear = (float)(Configstruct.SystemInfo.nZScrewPitch*1000.0/((float)Configstruct.SystemInfo.nZSensorResolution*4));
	
   /* Configstruct2.nXLeftWorkLimitMin  = Configstruct2.nXLeftLimit-5000;//安全区域最值，可在此范围内修改
	Configstruct2.nXRightWorkLimitMax = Configstruct2.nXRightLimit+5000;
	Configstruct2.nYFrontWorkLimitMin = Configstruct2.nYFrontLimit-5000;
	Configstruct2.nYBackWorkLimitMax  = Configstruct2.nYBackLimit+5000;*/


	if(Configstruct.SystemInfo.nZSaveVoyage <= 0)
	{
		//MessageBox("HiCNC.INI文件中Z Axes Save Voyage(um)信息没有或错误", "错误", MB_ICONERROR);
		return -1;
	}
	if(Configstruct.SystemInfo.nZWorkZeroOffset[0] < 0 || Configstruct.SystemInfo.nZWorkZeroOffset[0] > 10000)
	{
		//MessageBox("HiCNC.INI文件中Z1 Axes Work Zero(um)信息没有或错误", "错误", MB_ICONERROR);
		return -1;
	}
	if(Configstruct.SystemInfo.nZWorkZeroOffset[1] < 0 || Configstruct.SystemInfo.nZWorkZeroOffset[1] > 10000)
	{
		//MessageBox("HiCNC.INI文件中Z2 Axes Work Zero(um)信息没有或错误", "错误", MB_ICONERROR);
		return -1;
	}
	if(Configstruct.SystemInfo.nZWorkZeroOffset[2] < 0 || Configstruct.SystemInfo.nZWorkZeroOffset[2] > 10000)
	{
		//MessageBox("HiCNC.INI文件中Z3 Axes Work Zero(um)信息没有或错误", "错误", MB_ICONERROR);
		return -1;
	}
	if(Configstruct.SystemInfo.nZWorkZeroOffset[3] < 0 || Configstruct.SystemInfo.nZWorkZeroOffset[3] > 10000)
	{
		//MessageBox("HiCNC.INI文件中Z4 Axes Work Zero(um)信息没有或错误", "错误", MB_ICONERROR);
		return -1;
	}
	if(Configstruct.SystemInfo.nZWorkZeroOffset[4] < 0 || Configstruct.SystemInfo.nZWorkZeroOffset[4] > 10000)
	{
		//MessageBox("HiCNC.INI文件中Z5 Axes Work Zero(um)信息没有或错误", "错误", MB_ICONERROR);
		return -1;
	}
	if(Configstruct.SystemInfo.nZWorkZeroOffset[5] < 0 || Configstruct.SystemInfo.nZWorkZeroOffset[5] > 10000)
	{
		//MessageBox("HiCNC.INI文件中Z6 Axes Work Zero(um)信息没有或错误", "错误", MB_ICONERROR);
		return -1;
	}
	if(Configstruct.SystemInfo.nXSFTime < 0)
		Configstruct.SystemInfo.nXSFTime = 0;
	else if(Configstruct.SystemInfo.nXSFTime > 100)
		Configstruct.SystemInfo.nXSFTime = 100;
	if(Configstruct.SystemInfo.nYSFTime < 0)
		Configstruct.SystemInfo.nYSFTime = 0;
	else if(Configstruct.SystemInfo.nYSFTime > 100)
		Configstruct.SystemInfo.nYSFTime = 100;
	if(Configstruct.SystemInfo.nZSFTime < 0)
		Configstruct.SystemInfo.nZSFTime = 0;
	else if(Configstruct.SystemInfo.nZSFTime > 100)
		Configstruct.SystemInfo.nZSFTime = 100;
	if(Configstruct.SystemInfo.nXSPE < 5)
		Configstruct.SystemInfo.nXSPE = 5;
	else if(Configstruct.SystemInfo.nXSPE > 50)
		Configstruct.SystemInfo.nXSPE = 50;
	if(Configstruct.SystemInfo.nYSPE < 5)
		Configstruct.SystemInfo.nYSPE = 5;
	else if(Configstruct.SystemInfo.nYSPE > 50)
		Configstruct.SystemInfo.nYSPE = 50;
	//Ver16.5.2.27-2:Fix QDF bug
	if(Configstruct.SystemInfo.nXYAllowedPE < 10)
		Configstruct.SystemInfo.nXYAllowedPE = 10;
	else if(Configstruct.SystemInfo.nXYAllowedPE > 50)
		Configstruct.SystemInfo.nXYAllowedPE = 50;
	//Ver16.5.2.27-2:Finish
	//Ver16.7.3.39-1:Add MHM error judge
	if(Configstruct.SystemInfo.nXHMItoS < -3500 || Configstruct.SystemInfo.nXHMItoS > 3500)
	{
		//MessageBox("HiCNC.INI文件中X Axis Distance Of HMI To HMS(um)信息错误", "错误", MB_OK|MB_ICONERROR);
		return -1;
	}
	if(Configstruct.SystemInfo.nYHMItoS < -3500 || Configstruct.SystemInfo.nYHMItoS > 3500)
	{
		//MessageBox("HiCNC.INI文件中Y Axis Distance Of HMI To HMS(um)信息错误", "错误", MB_OK|MB_ICONERROR);
		return -1;
	}
	//Ver16.7.3.39-1:Finish
	if(Configstruct.DrillInfo.fMinTDia < 0.1)
		Configstruct.DrillInfo.fMinTDia = (float)(0.1);
	else if(Configstruct.DrillInfo.fMinTDia > 0.5)
		Configstruct.DrillInfo.fMinTDia = (float)(0.5);
	Configstruct2.nMinLT = 1200;
	if(Configstruct.DrillInfo.nLT < Configstruct2.nMinLT || Configstruct.DrillInfo.nLT > 20000)
	{
		//MessageBox("HiCNC.INI文件中Underlay Thickness(um)信息没有或错误", "错误", MB_ICONERROR);
		return -1;
	}
	if(Configstruct.DrillInfo.nLDD < 100 || Configstruct.DrillInfo.nLDD > 2000)
	{
		//MessageBox("HiCNC.INI文件中Underlay Drill Thickness(um)信息没有或错误", "错误", MB_ICONERROR);
		return -1;
	}
	if(Configstruct.DrillInfo.nBT < 0)
		Configstruct.DrillInfo.nBT = 0;
	else if(Configstruct.DrillInfo.nBT > 10000)
		Configstruct.DrillInfo.nBT = 10000;
	if(Configstruct.DrillInfo.nSecureBT < 10000 || Configstruct.DrillInfo.nSecureBT > 15000)
	{
		//	MessageBox("HiCNC.INI文件中Secure Workpiece Thickness(um)信息没有或错误(<10或>15mm)", "错误", MB_ICONERROR);
		return -1;
	}
	if(Configstruct.DrillInfo.nTDFC < 300 || Configstruct.DrillInfo.nTDFC > 1500)
	{
		//	MessageBox("HiCNC.INI文件中Tool Deviate Foot Clearance(um)信息没有或错误\n\n允许设置范围:0.3-1.5mm", "错误", MB_ICONERROR);
		return -1;
	}
	if(Configstruct.DrillInfo.nFDBC < 300 || Configstruct.DrillInfo.nFDBC > 5000)
	{
		//MsgDlg("HiCNC.INI文件中Foot Deviate Board Clearance(um)信息没有或错误(<0.3或>5mm)", "错误", "确定", "", "", 1, MB_ICONERROR);
		return -1;
	}
	if(Configstruct.DrillInfo.nTDTH < 30000)
	{
		//MsgDlg("HiCNC.INI文件中Tool Deviate Table Height(um)信息没有或错误(<36.5mm)", "错误", "确定", "", "", 1, MB_ICONERROR);
		return -1;
	}
	
	Configstruct2.nDBot = Configstruct.DrillInfo.nTDTH-Configstruct.DrillInfo.nLT+Configstruct.DrillInfo.nLDD;
	Configstruct2.nDWV  = Configstruct.DrillInfo.nLDD+Configstruct.DrillInfo.nBT+Configstruct.DrillInfo.nFDBC+Configstruct.DrillInfo.nTDFC;
	if(Configstruct.DrillInfo.fDnSpdScale < 1.0)
		Configstruct.DrillInfo.fDnSpdScale = 1.0;
	else if(Configstruct.DrillInfo.fDnSpdScale > 1.5)
		Configstruct.DrillInfo.fDnSpdScale = 1.5;
	
	//Ver16.7.3.54-1
	if(Configstruct.DrillInfo.nQDFZAdvCom < -500)
		Configstruct.DrillInfo.nQDFZAdvCom = -500;
	else if(Configstruct.DrillInfo.nQDFZAdvCom > 1500)
		Configstruct.DrillInfo.nQDFZAdvCom = 1500;
	
	//Ver16.7.3.54-1:Finish
	//Ver16.7.5.67-1
	if(Configstruct.DrillInfo.unZShiftDnTime > 3)
		Configstruct.DrillInfo.unZShiftDnTime = 3;
	
	//Ver16.7.5.67-1:Finish
	if(Configstruct.SystemInfo.unXYMaxSpeed <= 0 || Configstruct.SystemInfo.unXYMaxSpeed > 50000)
	{
		//	MessageBox("HiCNC.INI文件中XY Axes Max Move Velocity(mm/min)信息没有或错误", "错误", MB_ICONERROR);
		return -1;
	}
//move	Configstruct.SystemInfo.unXYMaxSpeed = (unsigned int)(Configstruct.SystemInfo.unXYMaxSpeed*1000.0/60);	//mm/min->um/s
	if(Configstruct.SystemInfo.unXYAcc < 50 || Configstruct.SystemInfo.unXYAcc > 13000)
	{
		//	MessageBox("HiCNC.INI文件中XY Axes Acceleration(mm/s2)信息没有或错误", "错误", MB_ICONERROR);
		return -1;
	}
//move	Configstruct.SystemInfo.unXYAcc = (unsigned int)(Configstruct.SystemInfo.unXYAcc*1000.0);	//mm/S2->um/S2
	if(Configstruct.SystemInfo.unXYDcc < 50 || Configstruct.SystemInfo.unXYDcc > 13000)
	{
		//	MessageBox("HiCNC.INI文件中XY Axes Deceleration(mm/s2)信息没有或错误", "错误", MB_ICONERROR);
		return -1;
	}
//move	Configstruct.SystemInfo.unXYDcc = (unsigned int)(Configstruct.SystemInfo.unXYDcc*1000.0);
	
	if(Configstruct.SystemInfo.unZMaxVelocity <= 0 || Configstruct.SystemInfo.unZMaxVelocity > 30000)
	{
		//	MessageBox("HiCNC.INI文件中Z Axes Max Move Velocity(mm/min)信息没有或错误", "错误", MB_ICONERROR);
		return -1;
	}
//move	Configstruct.SystemInfo.unZMaxVelocity = (unsigned int)(Configstruct.SystemInfo.unZMaxVelocity*1000.0/60);
	if(Configstruct.SystemInfo.unZAcc < 50 || Configstruct.SystemInfo.unZAcc > 40000)
	{
		//	MessageBox("HiCNC.INI文件中Z Axes Acceleration(mm/s2)信息没有或错误", "错误", MB_ICONERROR);
		return -1;
	}
//move	Configstruct.SystemInfo.unZAcc = (unsigned int)(Configstruct.SystemInfo.unZAcc*1000.0);
	if(Configstruct.SystemInfo.unZDcc < 50 || Configstruct.SystemInfo.unZDcc > 40000)
	{
		//	MessageBox("HiCNC.INI文件中Z Axes Deceleration(mm/s2)信息没有或错误", "错误", MB_ICONERROR);
		return -1;
	}
//move	Configstruct.SystemInfo.unZDcc = (unsigned int)(Configstruct.SystemInfo.unZDcc*1000.0);
	if(Configstruct2.unZDownSpeedScale < 1)
		Configstruct2.unZDownSpeedScale = 1;
	else if(Configstruct2.unZDownSpeedScale > 3)
		Configstruct2.unZDownSpeedScale = 3;
	
	//---------------------------------------------------------------------------------
	//以下是自动换刀
	if(strcmp(Configstruct.ToolInfo.cACTS , "OFF") && strcmp(Configstruct.ToolInfo.cACTS , "ON"))
		strcpy(Configstruct.ToolInfo.cACTS , "OFF");
	if(strcmp(Configstruct.ToolInfo.cACTS , "OFF"))
		strcpy(Configstruct.ToolInfo.cChangeToolMode , "HAND");
	else
	{
		if(!strcmp(Configstruct.ToolInfo.cChangeToolMode , "HalfAuto"))
			strcpy(Configstruct.ToolInfo.cChangeToolMode , "HALFAUTO");
		else if(!strcmp(Configstruct.ToolInfo.cChangeToolMode , "Auto"))
			strcpy(Configstruct.ToolInfo.cChangeToolMode , "AUTO");
		else
			strcpy(Configstruct.ToolInfo.cChangeToolMode , "HAND");
	}
	
	//----------------------------------------------------------------------------------
	if(strcmp(Configstruct.ToolInfo.cToolRoomType , "A") && strcmp(Configstruct.ToolInfo.cToolRoomType , "B") && strcmp(Configstruct.ToolInfo.cToolRoomType , "C"))
	{
		//	MessageBox("HiCNC.INI文件中Tool Room Tyoe信息错误", "错误", MB_ICONERROR);
		return -1;
	}
	if(Configstruct.ToolInfo.nMaxIndexOfToolRoom < 0)
	{
		//	MessageBox("HiCNC.INI文件中Max Tool Room Index信息没有或错误", "错误", MB_ICONERROR);
		return -1;
	}
	if(Configstruct.ToolInfo.nCassetteNumber < 1 || Configstruct.ToolInfo.nCassetteNumber > 2)
	{
		//	MessageBox("HiCNC.INI文件中TR Cassette Number信息没有或错误", "错误", MB_ICONERROR);
		return -1;
	}
	
	for(i = 0; i < 6; i++)
	{
		if(Configstruct.ToolInfo.nACTCompensation[i] < -500)
			Configstruct.ToolInfo.nACTCompensation[i] = -500;
		else if(Configstruct.ToolInfo.nACTCompensation[i] > 500)
			Configstruct.ToolInfo.nACTCompensation[i] = 500;
	}
	
	if(Configstruct.ToolInfo.unGripFingerOpenDelayTime > 20000)
		Configstruct.ToolInfo.unGripFingerOpenDelayTime = 20000;
	if(Configstruct.ToolInfo.unGripFingerCloseDelayTime > 20000)
		Configstruct.ToolInfo.unGripFingerCloseDelayTime = 20000;
	if(Configstruct.ToolInfo.unRaisedGripDelayTime > 20000)
		Configstruct.ToolInfo.unRaisedGripDelayTime = 20000;
	
	if(strcmp(Configstruct.InspectInfo.cTDC , "OFF") &&strcmp(Configstruct.InspectInfo.cTDC , "ON"))
		strcpy(Configstruct.InspectInfo.cTDC , "OFF");
	if(strcmp(Configstruct.ToolInfo.cToolRoomType , "C"))
		strcpy(Configstruct.InspectInfo.cTDC, "OFF");
	//----------------------------------------------------------------------------------------------
	//允许钻完孔后进行刀具测量
	if(strcmp(Configstruct.InspectInfo.cDrilledTDC , "OFF") && strcmp(Configstruct.InspectInfo.cDrilledTDC, "ON"))
		strcpy(Configstruct.InspectInfo.cDrilledTDC , "OFF");
	if(strcmp(Configstruct.ToolInfo.cToolRoomType , "C"))
		strcpy(Configstruct.InspectInfo.cDrilledTDC , "OFF");
	//Ver16.7.5.74-2
	//----------------------------------------------------------------------------------------------
	if(Configstruct.InspectInfo.unDoTMSAfterSpindleStop > 30)
		Configstruct.InspectInfo.unDoTMSAfterSpindleStop = 30;
	//Ver16.7.5.74-2:Finish
	//----------------------------------------------------------------------------------------------
	//允许刀具长度自动调整
	if(strcmp(Configstruct.InspectInfo.cATDA,"OFF") && strcmp(Configstruct.InspectInfo.cATDA ,"ON"))
		if(strcmp(Configstruct.ToolInfo.cToolRoomType , "C"))
			strcpy(Configstruct.InspectInfo.cATDA,"OFF");
		
		//-----------------------------------------------------------------------------------------------
		if(Configstruct.InspectInfo.nTDCRefDepthZ1 < 0)
		{
			//	MessageBox("HiCNC.INI文件中TDC Referenced Depth Of Z1 Axis(um)信息没有或错误", "错误", MB_ICONERROR);
			return -1;
		}
		if(Configstruct.InspectInfo.nTDCRefDepthZ2 < 0)
		{
			//	MessageBox("HiCNC.INI文件中TDC Referenced Depth Of Z2 Axis(um)信息没有或错误", "错误", MB_ICONERROR);
			return -1;
		}
		if(Configstruct.InspectInfo.nTDCRefDepthZ3 < 0)
		{
			//	MessageBox("HiCNC.INI文件中TDC Referenced Depth Of Z3 Axis(um)信息没有或错误", "错误", MB_ICONERROR);
			return -1;
		}
		if(Configstruct.InspectInfo.nTDCRefDepthZ4 < 0)
		{
			//	MessageBox("HiCNC.INI文件中TDC Referenced Depth Of Z4 Axis(um)信息没有或错误", "错误", MB_ICONERROR);
			return -1;
		}
		if(Configstruct.InspectInfo.nTDCRefDepthZ5 < 0)
		{
			//	MessageBox("HiCNC.INI文件中TDC Referenced Depth Of Z5 Axis(um)信息没有或错误", "错误", MB_ICONERROR);
			return -1;
		}
		if(Configstruct.InspectInfo.nTDCRefDepthZ6 < 0)
		{
			//	MessageBox("HiCNC.INI文件中TDC Referenced Depth Of Z6 Axis(um)信息没有或错误", "错误", MB_ICONERROR);
			return -1;
		}
		if(Configstruct.InspectInfo.nTDCPmtMinErr < 100)
			Configstruct.InspectInfo.nTDCPmtMinErr = 100;
		else if(Configstruct.InspectInfo.nTDCPmtMinErr > 500)
			Configstruct.InspectInfo.nTDCPmtMinErr = 500;
		
		if(Configstruct.InspectInfo.nTDCPmtMaxErr < 1000)
			Configstruct.InspectInfo.nTDCPmtMaxErr = 1000;
		else if(Configstruct.InspectInfo.nTDCPmtMaxErr > 3000)
			Configstruct.InspectInfo.nTDCPmtMaxErr = 3000;
		
		if(Configstruct.InspectInfo.unTDCZVelocity < 100)
			Configstruct.InspectInfo.unTDCZVelocity  = 100;
//move		Configstruct.InspectInfo.unTDCZVelocity = (unsigned int)(Configstruct.InspectInfo.unTDCZVelocity*1000.0/60);
		if(Configstruct.InspectInfo.unTDCZVelocity > Configstruct.SystemInfo.unZMaxVelocity)
			Configstruct.InspectInfo.unTDCZVelocity = Configstruct.SystemInfo.unZMaxVelocity;
		//--------------------------------------------------------------------------------------------------
		//以下是断钻检测
		if(strcmp(Configstruct.InspectInfo.cBTC , "OFF") && strcmp(Configstruct.InspectInfo.cBTC , "ON"))
			strcpy(Configstruct.InspectInfo.cBTC , "OFF");
		if(!strcmp(Configstruct.InspectInfo.cBTC, "OFF"))
		{
			for(i = 0; i < 6; i++)
				Configstruct2.asZBTC[i] = "OFF";
		}
		else
		{
			for(i = 0; i < 6; i++)
				Configstruct2.asZBTC[i] = "ON";
		}
		//Ver16.2.1.10
		
		//----------------------------------------------------------------------------------------------------
		//QIC压脚
		if(strcmp(Configstruct.PressureFootInfo.cACF ,"OFF") && strcmp(Configstruct.PressureFootInfo.cACF ,"ON"))
			strcpy(Configstruct.PressureFootInfo.cACF ,"OFF");
		
		//----------------------------------------------------------------------------------------------------
		if(Configstruct.PressureFootInfo.nACFChkTimeouts < 300 || Configstruct.PressureFootInfo.nACFChkTimeouts > 1500)
		{
			//	MessageBox("HiCNC.INI文件中ACF Check Timeouts(ms)信息错误(<300或>1500)", "错误", MB_ICONERROR);
			return -1;
		}
		if(Configstruct.PressureFootInfo.nFBPChkTimeouts < 500 || Configstruct.PressureFootInfo.nFBPChkTimeouts > 2000)
		{
			//	MessageBox("HiCNC.INI文件中FBP Check Timeouts(ms)信息错误(<500或>2000)", "错误", MB_ICONERROR);
			return -1;
		}
		if(Configstruct.PressureFootInfo.nFTPChkTimeouts < 500 || Configstruct.PressureFootInfo.nFTPChkTimeouts > 2000)
		{
			//	MessageBox("HiCNC.INI文件中FTP Check Timeouts(ms)信息错误(<500或>2000)", "错误", MB_ICONERROR);
			return -1;
		}
		if(Configstruct.PressureFootInfo.nQICFBPChkTimeouts < 500 || Configstruct.PressureFootInfo.nQICFBPChkTimeouts > 2000)
		{
			//	MessageBox("HiCNC.INI文件中QIC FBP Check Timeouts(ms)信息错误(<500或>2000)", "错误", MB_ICONERROR);
			return -1;
		}
		if(Configstruct.PressureFootInfo.nTDLChkTimeouts < 200 || Configstruct.PressureFootInfo.nTDLChkTimeouts > 1500)
		{
			//	MessageBox("HiCNC.INI文件中TDL Check Timeouts(ms)信息错误(<200或>1500)", "错误", MB_ICONERROR);
			return -1;
		}
		if(Configstruct.PressureFootInfo.nACFSMaxDia < 0 || Configstruct.PressureFootInfo.nACFSMaxDia > 1000)
		{
			//	MessageBox("HiCNC.INI文件中Max Diameter Of ACFS(um)信息错误(<0或>1000)", "错误", MB_ICONERROR);
			return -1;
		}
		if(Configstruct.PressureFootInfo.nACFDiaErr < 50 || Configstruct.PressureFootInfo.nACFDiaErr > 300)
		{
			//	MessageBox("HiCNC.INI文件中Diameter Error Of ACFS(um)信息错误(<50或>300)", "错误", MB_ICONERROR);
			return -1;
		}
		if(Configstruct.InspectInfo.nACLBTErr < 0)
			Configstruct.InspectInfo.nACLBTErr = 0;
		else if(Configstruct.InspectInfo.nACLBTErr > 4000)
			Configstruct.InspectInfo.nACLBTErr = 4000;
		if(Configstruct.FilterInfo.nPmtBTNum < 1)
		{
			//	MessageBox("HiCNC.INI文件中Repeat Number BTC信息错误(<1)", "错误", MB_ICONERROR);
			return -1;
		}
		for(i = 0; i < 6; i++)
			Configstruct2.nBTNum[i] = 0;//notuse
		
		if((!strcmp(Configstruct.SpindleInfo.cSpindleType,"Ball" )&& (Configstruct.SpindleInfo.fADccTime < 4 || Configstruct.SpindleInfo.fADccTime > 8)) ||
			(!strcmp(Configstruct.SpindleInfo.cSpindleType, "Air" )&& (Configstruct.SpindleInfo.fADccTime < 10 || Configstruct.SpindleInfo.fADccTime > 30)))
		{
			//	MessageBox("HiCNC.INI文件中Inverter ADcc Time(S)信息错误", "错误", MB_ICONERROR);
			return -1;
		}
		//	Configstruct.SpindleInfo.fSSCL += (float)(0.0001);
		if(Configstruct.SpindleInfo.fSSCL < 1 || Configstruct.SpindleInfo.fSSCL > 5.1)
		{
			//	MessageBox("HiCNC.INI文件中Single Spindle Current Limit(A)信息错误(<1或>6)", "错误", MB_ICONERROR);
			return -1;
		}
		//    Configstruct.SpindleInfo.fSSRC += (float)(0.0001);
		if(Configstruct.SpindleInfo.fSSRC < 0.5 || Configstruct.SpindleInfo.fSSRC > 5.1)
		{
			//	MessageBox("HiCNC.INI文件中Single Spindle Rated Current(A)信息错误(<0.5或>SSCL)", "错误", MB_ICONERROR);
			return -1;
		}
		//    Configstruct.SpindleInfo.fSSSC += (float)(0.0001);
		if(Configstruct.SpindleInfo.fSSSC < Configstruct.SpindleInfo.fSSCL || Configstruct.SpindleInfo.fSSSC > 5.1)
		{
			//	MessageBox("HiCNC.INI文件中Single Spindle Stall Current(A)信息错误(<0.5或>5.2)", "错误", MB_ICONERROR);
			return -1;
		}
		//    Configstruct.SpindleInfo.fSSDBC += (float)(0.0001);
		if(Configstruct.SpindleInfo.fSSDBC < 0 || Configstruct.SpindleInfo.fSSDBC > 2.51)
		{
			//	MessageBox("HiCNC.INI文件中Single Spindle DC Brake Current(A)信息错误(<0或>2.5)", "错误", MB_ICONERROR);
			return -1;
		}
		//    Configstruct.SpindleInfo.fPWMLF += (float)(0.0001);
		if(Configstruct.SpindleInfo.fPWMLF < 6 || Configstruct.SpindleInfo.fPWMLF > 15.1)	//Ver16.5.2.27-Enable Max Low Velocity PWM frequency=15KHz
		{
			//	MessageBox("HiCNC.INI文件中Low Switching Frequency(KHz)信息错误(<6或>15)", "错误", MB_ICONERROR);
			return -1;
		}
		//	Configstruct.SpindleInfo.fPWMHF += (float)(0.0001);
		if(Configstruct.SpindleInfo.fPWMHF < Configstruct.SpindleInfo.fPWMLF || Configstruct.SpindleInfo.fPWMHF > 15.1)
		{
			//	MessageBox("HiCNC.INI文件中High Switching Frequency(KHz)信息错误(<LSF或>15)", "错误", MB_ICONERROR);
			return -1;
		}
		//    Configstruct.SpindleInfo.fPWMSF += (float)(0.0001);
		if(Configstruct.SpindleInfo.fPWMSF < Configstruct.SpindleInfo.unSpindleMinRev/60.0 || Configstruct.SpindleInfo.fPWMSF > Configstruct.SpindleInfo.unSpindleMaxRev/60.0)
		{
			//	MessageBox("HiCNC.INI文件中PWM Switch Frequency(Hz)信息错误(<SMinRev或>SMaxRev)", "错误", MB_ICONERROR);
			return -1;
		}
		Configstruct2.nCLID = 107;//notuse
		Configstruct2.nRCID = 113;//notuse
		Configstruct2.nSCID = 710;//notuse
		Configstruct2.nDBCID = 507;//notuse
		Configstruct2.nSFID = 601;//notuse
		if(Configstruct.SpindleInfo.fFullLoadCurrent < 1 || Configstruct.SpindleInfo.fFullLoadCurrent > 6)
		{
			//	MessageBox("HiCNC.INI文件中Single Spindle Full Load Current(A)信息错误", "错误", MB_ICONERROR);
			return -1;
		}
		if(Configstruct.SpindleInfo.fEmptyLoadCurrent < 0.5 || Configstruct.SpindleInfo.fEmptyLoadCurrent > Configstruct.SpindleInfo.fFullLoadCurrent)
		{
			//	MessageBox("HiCNC.INI文件中Single Spindle Empty Load Current(A)信息错误", "错误", MB_ICONERROR);
			return -1;
		}
		if(Configstruct.SpindleInfo.fTorqueCompensate < 0 || Configstruct.SpindleInfo.fTorqueCompensate > 3)
		{
			//	MessageBox("HiCNC.INI文件中Single Spindle Torque Compensate(%)信息错误", "错误", MB_ICONERROR);
			return -1;
		}
		//Ver16.7.3.59-1
		if(!strcmp(Configstruct.SpindleInfo.cInverter , "VFD-V"))
		{
			if(Configstruct.SpindleInfo.fPOCAcc < 10 || Configstruct.SpindleInfo.fPOCAcc > 50)
			{
				//		MessageBox("HiCNC.INI文件中Single Spindle Prevent Over Current in Accelerating(%)信息错误", "错误", MB_ICONERROR);
				return -1;
			}
		}
		else if(!strcmp(Configstruct.SpindleInfo.cInverter, "VFD-VE"))
		{
			if(Configstruct.SpindleInfo.fPOCAcc < 0 || Configstruct.SpindleInfo.fPOCAcc > 50)
			{
				//		MessageBox("HiCNC.INI文件中Single Spindle Prevent Over Current in Accelerating(%)信息错误", "错误", MB_ICONERROR);
				return -1;
			}
		}
		else if(!strcmp(Configstruct.SpindleInfo.cInverter,"VFD-B"))
		{
			if(Configstruct.SpindleInfo.fPOCAcc < 20 || Configstruct.SpindleInfo.fPOCAcc > 50)
			{
				//		MessageBox("HiCNC.INI文件中Single Spindle Prevent Over Current in Accelerating(%)信息错误", "错误", MB_ICONERROR);
				return -1;
			}
		}
		if(!strcmp(Configstruct.SpindleInfo.cInverter, "VFD-V"))
		{
			if(Configstruct.SpindleInfo.fPOCRun < 10 || Configstruct.SpindleInfo.fPOCRun > 50)
			{
				//		MessageBox("HiCNC.INI文件中Single Spindle Prevent Over Current in Running(%)信息错误", "错误", MB_ICONERROR);
				return -1;
			}
		}
		else if(!strcmp(Configstruct.SpindleInfo.cInverter ,"VFD-VE"))
		{
			if(Configstruct.SpindleInfo.fPOCRun < 0 || Configstruct.SpindleInfo.fPOCRun > 50)
			{
				//		MessageBox("HiCNC.INI文件中Single Spindle Prevent Over Current in Running(%)信息错误", "错误", MB_ICONERROR);
				return -1;
			}
		}
		else if(!strcmp(Configstruct.SpindleInfo.cInverter,"VFD-B"))
		{
			if(Configstruct.SpindleInfo.fPOCRun < 20 || Configstruct.SpindleInfo.fPOCRun > 50)
			{
				//		MessageBox("HiCNC.INI文件中Single Spindle Prevent Over Current in Running(%)信息错误", "错误", MB_ICONERROR);
				return -1;
			}
		}
		if(Configstruct.SpindleInfo.fPOT < 10 || Configstruct.SpindleInfo.fPOT > 50)
		{
			//	MessageBox("HiCNC.INI文件中Single Spindle Over Torque Check Level(%)信息错误", "错误", MB_ICONERROR);
			return -1;
		}
		if(Configstruct.SpindleInfo.fDCBrake < 0 || Configstruct.SpindleInfo.fDCBrake > 20)
		{
			//	MessageBox("HiCNC.INI文件中Single Spindle DC Brake Level(%)信息错误", "错误", MB_ICONERROR);
			return -1;
		}
		if(Configstruct.SpindleInfo.fINVRatedCurrent < 5 || Configstruct.SpindleInfo.fINVRatedCurrent > 30)
		{
			//	MessageBox("HiCNC.INI文件中INV Rated Current(A)信息错误", "错误", MB_ICONERROR);
			return -1;
		}
		if(Configstruct.SpindleInfo.fRatedPower < 0.1 || Configstruct.SpindleInfo.fRatedPower > 1.5)
		{
			//	MessageBox("HiCNC.INI文件中Single Spindle Rated Power(KW)信息错误", "错误", MB_ICONERROR);
			return -1;
		}
		
		if(strcmp(Configstruct.OtherInfo.cDebugMode, "OFF") && strcmp(Configstruct.OtherInfo.cDebugMode, "ON"))
			strcpy(Configstruct.OtherInfo.cDebugMode , "OFF");
		
		Configstruct2.nMode = 0;
		
	/*	if(TDiaChk.nDiaPermitErr < 0)
			TDiaChk.nDiaPermitErr = 0;
		else if(TDiaChk.nDiaPermitErr > 100)
			TDiaChk.nDiaPermitErr = 100;*/  //TRC Permit Error(um)已删
		
	/*	if(	TDiaChk.fMeaErr < 0)
			TDiaChk.fMeaErr = 0.0;
		else if(	TDiaChk.fMeaErr > 10)
			TDiaChk.fMeaErr = (float)(0.1);
		else
			TDiaChk.fMeaErr = (float)(TDiaChk.fMeaErr/100.0);*///TRC Measure Error()=1.1已删
		
	/*	if(TDiaChk.fFChkPos < 300)	//Ver16.7.5.65-1
			TDiaChk.fFChkPos = 300;
		else if(TDiaChk.fFChkPos > 1000)
			TDiaChk.fFChkPos = 1000;*///TRC Fast Position(um)已删
		
		if(Configstruct.InspectInfo.nTableMvSP < 100)
			Configstruct.InspectInfo.nTableMvSP = 100;
		else if(Configstruct.InspectInfo.nTableMvSP > 166666)
			Configstruct.InspectInfo.nTableMvSP = 166666;
		
		Configstruct2.nCurTDia = 0;
		if(Configstruct.InspectInfo.unBlowTime > 3000)
			Configstruct.InspectInfo.unBlowTime = 3000;
		if(Configstruct.InspectInfo.unSPRev < Configstruct.SpindleInfo.unSpindleMinRev)
			Configstruct.InspectInfo.unSPRev = Configstruct.SpindleInfo.unSpindleMinRev;
		else if(Configstruct.InspectInfo.unSPRev > Configstruct.SpindleInfo.unSpindleMaxRev)
			Configstruct.InspectInfo.unSPRev = Configstruct.SpindleInfo.unSpindleMaxRev;
		if(Configstruct.InspectInfo.nSigNum < 1)
			Configstruct.InspectInfo.nSigNum = 1;
		else if(Configstruct.InspectInfo.nSigNum > 10)
			Configstruct.InspectInfo.nSigNum = 10;
		if(Configstruct.DrillInfo.nLSPre < 5)
			Configstruct.DrillInfo.nLSPre = 5;
		else if(Configstruct.DrillInfo.nLSPre > 140)
			Configstruct.DrillInfo.nLSPre = 140;
		
		if (!PathFileExists(Configstruct.FileInfo.cmastprogpath))
		{
			int DSLength = GetLogicalDriveStrings(0,NULL);//获取所有驱动器字符串信息长度。
			char* DStr = new char[DSLength];//用获取的长度在堆区创建一个c风格的字符串数组
			GetLogicalDriveStrings(DSLength,(LPTSTR)DStr);//将字符串信息复制到堆区数组中,其中保存了当前盘符的信息。
			strcpy(Configstruct.FileInfo.cmastprogfilename,DStr);
			delete DStr;
		}
		if (!PathFileExists(Configstruct.FileInfo.csubprogpath))
		{
			int DSLength = GetLogicalDriveStrings(0,NULL);//获取所有驱动器字符串信息长度。
			char* DStr = new char[DSLength];//用获取的长度在堆区创建一个c风格的字符串数组
			GetLogicalDriveStrings(DSLength,(LPTSTR)DStr);//将字符串信息复制到堆区数组中,其中保存了当前盘符的信息
			strcpy(Configstruct.FileInfo.csubprogpath,DStr);
			delete DStr;
		}
		if (!PathFileExists(Configstruct.FileInfo.catppath))
		{
			int DSLength = GetLogicalDriveStrings(0,NULL);//获取所有驱动器字符串信息长度。
			char* DStr = new char[DSLength];//用获取的长度在堆区创建一个c风格的字符串数组
			GetLogicalDriveStrings(DSLength,(LPTSTR)DStr);//将字符串信息复制到堆区数组中,其中保存了当前盘符的信息
			strcpy(Configstruct.FileInfo.catppath,DStr);
			delete DStr;
		}

		if (Configstruct.WorkLimitInfo.modefyLeftWorkLimit>=Configstruct.WorkLimitInfo.modefyRightWorkLimit||
			Configstruct.WorkLimitInfo.modefyFrontWorkLimit>=Configstruct.WorkLimitInfo.modefyBackWorkLimit)
		{
			//范围不合法 左值不小于右值，前值不小于后值
			InitModefyWorkLimit();
		}
        
		if (Configstruct.WorkLimitInfo.modefyLeftWorkLimit<Configstruct.SystemInfo.nXLeftLimit||
			Configstruct.WorkLimitInfo.modefyRightWorkLimit>Configstruct.SystemInfo.nXRightLimit||
            Configstruct.WorkLimitInfo.modefyFrontWorkLimit<Configstruct.SystemInfo.nYFrontLimit||
			Configstruct.WorkLimitInfo.modefyBackWorkLimit>Configstruct.SystemInfo.nYBackLimit)
		{
			//范围不合法，超过最大范围
			InitModefyWorkLimit();
		}

		if (Configstruct.InchingFunctionInfo.xyinchingspeed!=1000||Configstruct.InchingFunctionInfo.xyinchingspeed!=2000
			||Configstruct.InchingFunctionInfo.xyinchingspeed!=5000)
		{
			//XY寸动速度不为1000、2000、5000 mm/mm ，则初始化为 1000mm/mm
			Configstruct.InchingFunctionInfo.xyinchingspeed=1000;//
		}
		if (Configstruct.InchingFunctionInfo.xinchingstepdis<0.002||Configstruct.InchingFunctionInfo.xinchingstepdis>500)
		{
			//X寸动距离范围 (0.002mm---300mm)
			Configstruct.InchingFunctionInfo.xinchingstepdis=(float)0.002;
		}
		if (Configstruct.InchingFunctionInfo.yinchingstepdis<0.002||Configstruct.InchingFunctionInfo.yinchingstepdis>530)
		{
			//Y寸动距离范围 (0.002mm---530mm)
			Configstruct.InchingFunctionInfo.yinchingstepdis=(float)0.002;
		}
		if (Configstruct.InchingFunctionInfo.zinchingstepdis>-0.002||Configstruct.InchingFunctionInfo.zinchingstepdis<-35)
		{
			//Z寸动距离范围 (-0.002mm---(-35)mm)
			Configstruct.InchingFunctionInfo.zinchingstepdis=(float)0.002;
		}
		return 0;
}

int CncControl::ConfigFileParameterToWorkParameter()
{
	Configstruct.SystemInfo.unXYMaxSpeed = (unsigned int)(Configstruct.SystemInfo.unXYMaxSpeed*1000.0/60);	//mm/min->um/s
	Configstruct.SystemInfo.unXYAcc = (unsigned int)(Configstruct.SystemInfo.unXYAcc*1000.0);	//mm/s2->um/s2
	Configstruct.SystemInfo.unXYDcc = (unsigned int)(Configstruct.SystemInfo.unXYDcc*1000.0);
	Configstruct.SystemInfo.unZMaxVelocity = (unsigned int)(Configstruct.SystemInfo.unZMaxVelocity*1000.0/60);
	Configstruct.SystemInfo.unZAcc = (unsigned int)(Configstruct.SystemInfo.unZAcc*1000.0);
	Configstruct.SystemInfo.unZDcc = (unsigned int)(Configstruct.SystemInfo.unZDcc*1000.0);
	Configstruct.InspectInfo.unTDCZVelocity = (unsigned int)(Configstruct.InspectInfo.unTDCZVelocity*1000.0/60);

	Configstruct.InchingFunctionInfo.xyinchingspeed=(int)(Configstruct.InchingFunctionInfo.xyinchingspeed*1000.0/60);//mm/min->um/s

	if(!strcmp(Configstruct.ToolInfo.cACTS,"ON"))
		theApp.pwnd->m_usermarkflag.AUTOCHANGEFLAG=true;
	else
		theApp.pwnd->m_usermarkflag.AUTOCHANGEFLAG=false;
	//---------------------------------------------------------------------------------------
	//刀具寿命到时 有消息提示
	if(!strcmp(Configstruct.ToolInfo.cCTMATToolDie,"ON"))
	{
		Configstruct2.bCTMATToolDie = true;
		theApp.pwnd->m_usermarkflag.AUTOCHANGETOOLLIFE=true;
	}
	else
	{
		Configstruct2.bCTMATToolDie = false;
		theApp.pwnd->m_usermarkflag.AUTOCHANGETOOLLIFE=false;
	}
	//----------------------------------------------------------------------------------------
	//允许测量加工厚度
	if(!strcmp(Configstruct.InspectInfo.cAutoCheckBoardThickness,"ON"))
		theApp.pwnd->m_usermarkflag.MEARUETICKNESS = true;
	else
		theApp.pwnd->m_usermarkflag.MEARUETICKNESS = false;
	//----------------------------------------------------------------------------------------
	//允许引孔加工
	if(!strcmp(Configstruct.DrillInfo.cAutoPilotHole,"ON"))
		theApp.pwnd->m_usermarkflag.DRILLMARCHING=true;
	else
		theApp.pwnd->m_usermarkflag.DRILLMARCHING=false;
	//----------------------------------------------------------------------------------------
	//禁止板子边缘断钻检测
	if(!strcmp(Configstruct.FilterInfo.cEdgeCheckForBTC,"ON"))
		theApp.pwnd->m_usermarkflag.BREAKEDGECHECK=true;
	else
		theApp.pwnd->m_usermarkflag.BREAKEDGECHECK=false;
	//----------------------------------------------------------------------------------------
	//su 	theApp.pwnd->m_usermarkflag.CHECKSPRUNDRILLING=true;/*初始化,默认'下钻前检测电主轴是否打开'=ON*/ 
	theApp.pwnd->m_usermarkflag.CHECKSPRUNDRILLING=false; //Todo 目前测试，将默认值设为false
	theApp.pwnd->m_usermarkflag.RUNSPBEFOREDRILLMTC=false;/*初始化,默认'手动换刀模式下，钻孔前是否自动打开电主轴'=OFF*/	
	if(!strcmp(Configstruct.InspectInfo.cDrilledTDC,"ON"))
		theApp.pwnd->m_usermarkflag.AFTERCHECKTOOLLENGTH=true;
	else
		theApp.pwnd->m_usermarkflag.AFTERCHECKTOOLLENGTH=false;
	//允许刀具长度自动调整
	if(!strcmp(Configstruct.InspectInfo.cATDA,"ON"))
		theApp.pwnd->m_usermarkflag.AUTOAJUESTTOOLLENGH=true;
	else
		theApp.pwnd->m_usermarkflag.AUTOAJUESTTOOLLENGH=false;
	if(!strcmp(Configstruct.InspectInfo.cBTC,"ON"))
		theApp.pwnd->m_usermarkflag.BREAKTOOLCHECK=true;
	else
		theApp.pwnd->m_usermarkflag.BREAKTOOLCHECK=false;
	if(!strcmp(Configstruct.PressureFootInfo.cACF,"ON"))
		theApp.pwnd->m_usermarkflag.QIC=true;
	else
		theApp.pwnd->m_usermarkflag.QIC=false;
	theApp.pwnd->m_usermarkflag.MEARUENEWTOOL=false;
	theApp.pwnd->m_usermarkflag.MEARUEALLTOOL=false;
	if(!strcmp(Configstruct.InspectInfo.cNewToolDiameterCheck,"ON"))
	{
		Configstruct2.nMode = 1;
		theApp.pwnd->m_usermarkflag.MEARUENEWTOOL=true;
	}
	if(!strcmp(Configstruct.InspectInfo.cAllToolDiameterCheck, "ON"))
	{
		Configstruct2.nMode = 2;
		theApp.pwnd->m_usermarkflag.MEARUEALLTOOL=true;
	}

	Configstruct2.fXEGear = (float)(Configstruct.SystemInfo.nXScrewPitch*1000.0/((float)Configstruct.SystemInfo.nXSensorResolution*4));
	Configstruct2.fYEGear = (float)(Configstruct.SystemInfo.nYScrewPitch*1000.0/((float)Configstruct.SystemInfo.nYSensorResolution*4));
	Configstruct2.fZEGear = (float)(Configstruct.SystemInfo.nZScrewPitch*1000.0/((float)Configstruct.SystemInfo.nZSensorResolution*4));

	return 0;
}

int CncControl::WorkParameterToConfigFileParameter()
{
	if(true==theApp.pwnd->m_usermarkflag.AUTOCHANGEFLAG)// 自动换刀
		strcpy(Configstruct.ToolInfo.cACTS,"ON");
	else
		strcpy(Configstruct.ToolInfo.cACTS,"OFF");
	
	if(true==theApp.pwnd->m_usermarkflag.MEARUETICKNESS)//测量加工厚度
		strcpy(Configstruct.InspectInfo.cAutoCheckBoardThickness,"ON");
	else
		strcpy(Configstruct.InspectInfo.cAutoCheckBoardThickness,"OFF");
	
	if(true==theApp.pwnd->m_usermarkflag.DRILLMARCHING)//引孔加工
		strcpy(Configstruct.DrillInfo.cAutoPilotHole,"ON");
	else
	strcpy(Configstruct.DrillInfo.cAutoPilotHole,"OFF");
	// '下钻前打开电主轴'  
	//不记录在.ini文件中
	// 手动换刀模式下，钻孔前是否自动打开电主轴
	//不记录在.ini文件中
	if(true==theApp.pwnd->m_usermarkflag.BREAKTOOLCHECK)//断钻检测
		strcpy(Configstruct.InspectInfo.cBTC,"ON");
	else
		strcpy(Configstruct.InspectInfo.cBTC,"OFF");
	
	if(true==theApp.pwnd->m_usermarkflag.BREAKEDGECHECK)//禁止板子边缘断钻检测
		strcpy(Configstruct.FilterInfo.cEdgeCheckForBTC,"ON");
	else
		strcpy(Configstruct.FilterInfo.cEdgeCheckForBTC,"OFF");

	if(true==theApp.pwnd->m_usermarkflag.AFTERCHECKTOOLLENGTH)//钻完孔后进行刀具长度检测
		strcpy(Configstruct.InspectInfo.cDrilledTDC,"ON");
	else
		strcpy(Configstruct.InspectInfo.cDrilledTDC,"OFF");
	
	if(true==theApp.pwnd->m_usermarkflag.AUTOAJUESTTOOLLENGH)//自动调整刀具长度
		strcpy(Configstruct.InspectInfo.cATDA,"ON");
	else
		strcpy(Configstruct.InspectInfo.cATDA,"OFF");
	
	if(true==theApp.pwnd->m_usermarkflag.MEARUENEWTOOL)//直径检测（只允许测量新刀具直径）
		strcpy(Configstruct.InspectInfo.cNewToolDiameterCheck,"ON");
	else
		strcpy(Configstruct.InspectInfo.cNewToolDiameterCheck,"OFF");
	
	if(true==theApp.pwnd->m_usermarkflag.MEARUEALLTOOL)//测量所有刀具直径
		strcpy(Configstruct.InspectInfo.cAllToolDiameterCheck,"ON");
	else
		strcpy(Configstruct.InspectInfo.cAllToolDiameterCheck,"OFF");

	if(true==theApp.pwnd->m_usermarkflag.AUTOCHANGETOOLLIFE)//自动换刀模式下刀具寿命到有提示
		strcpy(Configstruct.ToolInfo.cCTMATToolDie,"ON");
	else
		strcpy(Configstruct.ToolInfo.cCTMATToolDie,"OFF");
	
	if(true==theApp.pwnd->m_usermarkflag.QIC)//允许QIC
		strcpy(Configstruct.PressureFootInfo.cACF,"ON");
	else
		strcpy(Configstruct.PressureFootInfo.cACF,"OFF");



	//XY Axes Max Move Velocity(mm/min)=416666
	//Configstruct.SpindleInfo.unXYMaxSpeed = (unsigned int)(Configstruct.SpindleInfo.unXYMaxSpeed*1000.0/60);	//mm/min->um/s
	Configstruct.SystemInfo.unXYMaxSpeed = (unsigned int)(Configstruct.SystemInfo.unXYMaxSpeed/1000.0*60);	//um/s->mm/min
	//XY Axes Acceleration(mm/s2)=10000000
	//Configstruct.SpindleInfo.unXYAcc = (unsigned int)(Configstruct.SpindleInfo.unXYAcc*1000.0);	//mm/S2->um/S2
	Configstruct.SystemInfo.unXYAcc = (unsigned int)(Configstruct.SystemInfo.unXYAcc/1000.0);	//um/S2->mm/S2
	
	//XY Axes Deceleration(mm/s2)=10000000
	Configstruct.SystemInfo.unXYDcc = (unsigned int)(Configstruct.SystemInfo.unXYDcc/1000.0);
	
	//Z Axes Max Move Velocity(mm/min)=423333

	Configstruct.SystemInfo.unZMaxVelocity = (unsigned int)(Configstruct.SystemInfo.unZMaxVelocity/1000.0*60);
	
	//Z Axes Acceleration(mm/s2)=25000000
	Configstruct.SystemInfo.unZAcc = (unsigned int)(Configstruct.SystemInfo.unZAcc/1000.0);
	
	//Z Axes Deceleration(mm/s2)=2500000
	Configstruct.SystemInfo.unZDcc = (unsigned int)(Configstruct.SystemInfo.unZDcc/1000.0);
	
	//Tool Max Life
	//Raised Grip Delay Time(ms)
	//Min Drill Tool Diameter(um)
	//TDC Z Axes Move Velocity(mm/min)
	Configstruct.InspectInfo.unTDCZVelocity = (unsigned int)(Configstruct.InspectInfo.unTDCZVelocity/1000.0*60);


	Configstruct.InchingFunctionInfo.xyinchingspeed=ceil(Configstruct.InchingFunctionInfo.xyinchingspeed/1000.0*60);//um/s->mm/min

	return 0;
	
}

void CncControl::InitModefyWorkLimit()
{
	Configstruct.WorkLimitInfo.modefyLeftWorkLimit=Configstruct.SystemInfo.nXLeftLimit;
	Configstruct.WorkLimitInfo.modefyRightWorkLimit=Configstruct.SystemInfo.nXRightLimit;
	Configstruct.WorkLimitInfo.modefyFrontWorkLimit=Configstruct.SystemInfo.nYFrontLimit;
	Configstruct.WorkLimitInfo.modefyBackWorkLimit=Configstruct.SystemInfo.nYBackLimit;
}
