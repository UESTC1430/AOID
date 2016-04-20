#include <WinSock2.h>
#include <afxstr.h>


class AOIDControl
{
public:
	AOIDControl(void);
	~AOIDControl(void);
public:
		SOCKET sockClient;
		char recvBuf[100];
		char tempBuf[150];
		SOCKADDR_IN addrSrv;
		AOIDCondition  aoidcondition;
		bool IniAOIDControl();//初始化机床
		bool Home();//机床回原点
		bool XYMove(float nX, float nY,CString asMode);//XY轴运动
		bool ZMove(float nZ,CString asMode);//Z轴运动
		bool CheckAOIDState();//机床状态查询函数
		int  GetAOIDMessage();//机床消息接收函数
        bool SendCommandToAOID(char *command);//机床命令直接发送函数	
        bool SetXYSpeed(float unXYSpeed);//速度设置
		bool SetZSpeed(float uiZSpeed);
		bool SetXPAbs(float nXPAbs);//X\Y\Z绝对位置
		bool SetYPAbs(float nYPAbs);
		bool SetZPAbs(float nZPAbs);
		bool SetXPRel(float nXPRel);//X\Y相对位置
		bool SetYPRel(float nYPRel);
};
