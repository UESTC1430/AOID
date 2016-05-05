
#include "stdafx.h"
#include "macapi.h"

#pragma once
//[SYSTEM]
struct SYSTEMINFO
{
	int nLoopType;
	int nXSensorResolution;
	int nXScrewPitch;
	int nYSensorResolution;
	int nYScrewPitch;
	int nZSensorResolution;
	int nZScrewPitch;
	int nXLeftLimit;	
	int nXRightLimit;
	int nYFrontLimit;
	int nYBackLimit;
	int nXPinPosition;
	int nYPinPosition;
	int nYWTStPos;
	int nZSaveVoyage;
	int nZWorkZeroOffset[6];
	unsigned int unXYMaxSpeed;//(mm/min)
	unsigned int unXYAcc;
	unsigned int unXYDcc;
	unsigned int unZMaxVelocity;
	unsigned int unZAcc;
	unsigned int unZDcc;
	int nXSFTime;
	int nYSFTime;
	int nZSFTime;
	int nXSPE;
	int nYSPE;
	int nXYAllowedPE;
	int nXHMItoS;
	int nYHMItoS;
	int nXWorkZero;
	int nYWorkZero;
};

//[SPINDLE]
struct SPINDLEINFO
{
	int nSpindleNumbers;
	char cZAxesStatus[128];
	char cSpindleType[128];
	unsigned int unSpindleMinRev;
	unsigned int unSpindleMaxRev;
	char cInverter[128];
	char cLastStopTime[128];
	float fADccTime;
	float fINVRatedCurrent;
	float fRatedPower;
	float fFullLoadCurrent;
	float fEmptyLoadCurrent;
	float fTorqueCompensate;
	float fPOCAcc;
	float fPOCRun;
	float fPOT;
	float fDCBrake;
	float fSSCL;
	float fSSRC;
	float fSSSC;
	float fSSDBC;
	float fPWMLF;
	float fPWMHF;
	float fPWMSF;
};

//[TOOL]
struct TOOLINFO1
{
	char cACTS[128];
	char cChangeToolMode[128];//half auto  todo
	char cToolRoomType[128];
	int nMaxIndexOfToolRoom;
	int nCassetteNumber;
	char cTRCassetteStatus1[128];
	char cTRCassetteStatus2[128];
	int nZ1BasePos;
	int nZ2BasePos;
	int nZ3BasePos;
	int nZ4BasePos;
	int nZ5BasePos;
	int nZ6BasePos;
	int nXSpace;
	int nYSpace;
	int nGPForSPX;
	int nGPForSPY;
	int nGPForRoom1X;
	int nGPForRoom1Y;
	int nGPForRoom81X;
	int nGPForRoom81Y;
	unsigned int unToolMaxLife;
	char cCTMATToolDie[128];//todo
	int nCurrentToolRoom;
	unsigned int unGripFingerOpenDelayTime;
	unsigned int unGripFingerCloseDelayTime;
	unsigned int unRaisedGripDelayTime;
	int nACTCompensation[6];
};

//[DRILL]
struct DRILLINFO
{
	float fMinTDia;
	int nTDTH;
	int nLT;
	int nLDD;
	int nBT;
	int nSecureBT;
	int nFDBC;
	int nTDFC;
	int nXDrillAjust;
	int nYDrillAjust;
	int nXDrillFixedCompensation;
	int nYDrillFixedCompensation;
	float fDnSpdScale;
	int nQDFZAdvCom;
	unsigned int unZShiftDnTime;
	int nXAWZOffset;
	int nYAWZOffset;
	int nLSPre;
	int nXShortLineSlotCompensation;
	int nYShortLineSlotCompensation;
	char cAutoPilotHole[128];
};


//[INSPECT]
struct INSPECTINFO
{
	char cBTC[128];
	char cTDC[128];
	char cDrilledTDC[128];
	char cATDA[128];
	char cAutoCheckBoardThickness[128];//todo 
	int nACLBTErr;
	int nTDCX;
	int nTDCY;
	int nTDCRefDepthZ1;
	int nTDCRefDepthZ2;
	int nTDCRefDepthZ3;
	int nTDCRefDepthZ4;
	int nTDCRefDepthZ5;
	int nTDCRefDepthZ6;
	char cToolDiameterMeasure[128];	
	int nTDCPmtMinErr;
	int nTDCPmtMaxErr;
	unsigned int unTDCZVelocity;
	int nTableMvSP;
	unsigned int unSPRev;
	int nSigNum;
	unsigned int unBlowTime;
	char cNewToolDiameterCheck[128];//todo
	char cAllToolDiameterCheck[128];//todo
	unsigned int unDoTMSAfterSpindleStop;
};

//[PRESSUREFOOT]
struct PRESSUREFOOTINFO
{
	char cACF[128];
	int nACFChkTimeouts;
	int nFBPChkTimeouts;
	int nFTPChkTimeouts;
	int nQICFBPChkTimeouts;
	int nTDLChkTimeouts;
	int nACFSMaxDia;
	int nACFDiaErr;
};

//[FILTER]
struct FILTERINFO
{
	int nPmtBTNum;
	unsigned int unInhCBDRev;
	char cEdgeCheckForBTC[128];//todo  
	int nBTCEdgeDistance;
};

//[OTHER]
struct OTHERINFO
{
	char cCOM[128];
	int nCOMBaudrate;
	int nCOMDataBits;
	char cCOMParityCheck[128];
	int nCOMDataStopBits;
	char cTransmitMode[128];
	char cDebugMode[128];
};

//[FILE]
struct FILEINFO
{
	char cATPfilename[128];
	char cmastprogfilename[128];
	char cDIAfilename[128];
	char cmastprogpath[128];
	char csubprogpath[128];
	char catppath[128];
};

//[WORKLIMIT]
struct  WORKLIMITINFO
{
	int modefyLeftWorkLimit;
	int modefyRightWorkLimit;
	int modefyFrontWorkLimit;
	int modefyBackWorkLimit;
};
struct STRETCH_ROTATEINFO
{
	float xcenterpos;//保存设置的中心位置横坐标   
	float ycenterpos;//保存设置的中心位置纵坐标
	float xscale;//保存输入的x方向伸缩比例
	float yscale;//保存输入的y方向伸缩比例
	float xrapos;//旋转变换 x坐标
	float yrapos;//旋转变换 y坐标
};
struct CURRENTDRILLINFO
{
	int currenttoolnum;
	int currentdrillnum;
	int currentwork_ver;
};
struct ZAXISINFO
{
	float ZaxisH;
	float ZaxisQ;
	float ZaxisK;
	float ZaxisZ;
	float ZaxisSUTO;
	float ZaxisTOTO;
};
struct INCHINGFUNCTIONINFO
{
	float xyinchingspeed;
	int xinchingstepdis;
	int yinchingstepdis;
	int zinchingstepdis;
};

//[MFUNCTION]
struct MFUNCTIONINFO
{
	char mfun1[128];
	char mfun2[128];
	char mfun3[128];
	char mfun4[128];
	char mfun5[128];
	char mfun6[128];
	char mfun7[128];
	char mfun8[128];
	char mfun9[128];
	char mfun10[128];
	char mfun11[128];
	char mfun12[128];
	char mfun13[128];
	char mfun14[128];
};

struct CONFIGSTRUCT
{	
	struct SYSTEMINFO SystemInfo;
	struct SPINDLEINFO SpindleInfo;
	struct TOOLINFO1 ToolInfo;
	struct DRILLINFO DrillInfo;
	struct INSPECTINFO InspectInfo;
	struct PRESSUREFOOTINFO PressureFootInfo;
	struct FILTERINFO FilterInfo;
	struct OTHERINFO OtherInfo;
	struct FILEINFO FileInfo;
	struct WORKLIMITINFO WorkLimitInfo;
	struct STRETCH_ROTATEINFO Stretch_RotateInfo;
	struct CURRENTDRILLINFO CurrentDrillInfo;
	struct ZAXISINFO ZaxisInfo;
	struct INCHINGFUNCTIONINFO InchingFunctionInfo;
	struct MFUNCTIONINFO MfunctionInfo;
};
struct CONFIGSTRUCT2//HICNC文件以外的初始化变量
{
   	unsigned int unZDownSpeed, unZUpSpeed,  unZDownSpeedScale;
	float fXEGear, fYEGear, fZEGear;
	unsigned int unXYVelocity;
	int nXPark, nYPark;
	int nXYStep, nZStep;
	unsigned int unSpindleRevBuf;	//Ver16.7.5.65-1
	unsigned int unSpindleRev;
    int nStopFactors;
	bool bCheckSpindle;
	int nZAxesStatus[6];
	int nSecureBT, nMinLT;
	unsigned int unXYWorkMoveSpeed;
	int nMode;	//0:不测量; 1:测量新刀; 2:测量所有
	int nCurTDia;
	int nDBot, nDWV, nTCmp;
	bool  bONLine;
	bool bMAS;
	unsigned int unMASZDnSP;
	int nCLID, nRCID, nSCID, nDBCID, nSFID;
	int nMaxTCmp;
	bool bCTMATToolDie;
	CString	asZBTC[6];
	int nBTNum[6];

};

class CncControl
{
public:
	CncControl();
	struct CONFIGSTRUCT Configstruct;
	struct CONFIGSTRUCT2 Configstruct2;
	typedef struct WORKPOSITION
	{
		float XPOS;//位置
		float YPOS;
		float ZPOS;
	}WorkPosition;

	//----------------------------------------zns
	CncCondition  cnccondition;
	WorkPosition  workposition;//当前工作位置
	int MASStatus[5];
	int nMASRV;
	int nStart;
	void * pwnd;
	public:
		//********************************************zns
		SOCKET sockClient;
		char recvBuf[100];
		char tempBuf[150];
		SOCKADDR_IN addrSrv;
		int IniCncControl(void * pmainwnd);
		bool Home();
		bool SetMASXYSpeed(float unXYSpeed);//速度设置
		bool SetMASZSpeed(float uiZSpeed);
		bool SetMASXPAbs(float nXPAbs);//绝对位置
		bool SetMASYPAbs(float nYPAbs);
		bool SetMASZPAbs(float nZPAbs);
		bool SetMASXPRel(float nXPRel);//相对位置
		bool SetMASYPRel(float nYPRel);
		bool ZMove(float nZ,CString asMode);//设置Z轴寸动
		bool XYMove(float nX, float nY,CString asMode);//设置XY轴寸动
		bool CheckCncState();//发送
		int GetCncMessage();//接收函数
		bool SendCommandToCnc(char *command);
		//********************************************zns	
		
		//----------------------------------------------------------------------------------------------------------------suxia
		int ReadEnvFileInt(char* Section, char* Ident, char *Default);
		bool SendCommand(char *szCommand,bool Flag=false,bool CmdFlag=false);//此处默认打孔文件发送指令而非直接向下传送命令
		int Round(double dfValue);
		bool GetMASPass();//获得程序控制器端当前程序执行的状态	
		bool SetMASINTStatus(int nStatus);	
		bool SetMASSysVar();//设置系统环境变量
		bool SetMASFC(int nFC);
		bool SetMASHostIdleStatus(int nStatus);
		bool SetMASConStatus(int nStatus);//Write MAS's connection status
		bool GetMASConStatus();

		bool SetMASXYJDD(int nXJDD, int nYJDD);//设置XY轴的减速点
		bool SetMASXYJV(int nXJV, int nYJV);//设置XY轴的减速距离
		bool SetMASZJV(int nJV);//设置Z轴的减速距离
		double CncControl::calculatespeed(int velocity, int accelerate);//计算由速度和加速度得到减速距离
		int GetAxisDI(CString asAxis);
		bool Return_Machine_Zero();//设置机械原点
		
		
	public:
		void InitModefyWorkLimit();
		int WorkParameterToConfigFileParameter();
		int ConfigFileParameterToWorkParameter();
		int ConfigFileParameterCheck();
		int ReadConfigFileNew();
		int WriteConfigFile();
		bool XYJog(int XV,int XJD,int YV,int YJD);//XY轴连续运动
		bool ZJog(int nJV);//Z轴连续运动
		int notenum;
		FilePath   *m_pathprevious;
		FilePath   *m_pathfirst;
		FilePath	*m_pathcurrent;
		bool AddPathNote(char *pathnote);
		//------------------------------------------------------------------------------suxia
		~CncControl();
};

class CncCom
{
public:
	CncCom();
public:
	COMMUNICATION_HANDLE m_hCom;
	char szIP[32];
	bool bMASPERR;
	int nPECode;
	CString asMASOut;
	
	int ConnectMaestro();
	static void OnMACError(const char* szDevice);	//Ver16.7.3.48-2
	static void OnMACMessage(unsigned long msgID,
							 unsigned long WParam,
							 unsigned long LParam,
							 unsigned long msgTime);
	
	
public:
	~CncCom();
};
