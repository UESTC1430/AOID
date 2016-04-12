#include <WinSock2.h>
#include <afxstr.h>

typedef struct CNCCONDITION
{
	int XD;//判断运动是否完成
	int YD;
	int ZD;
	float XPOS;//位置
	float YPOS;
	float ZPOS;
}CncCondition;

class CncControl
{
public:
	CncControl(void);
	~CncControl(void);
public:
		SOCKET sockClient;
		char recvBuf[100];
		char tempBuf[150];
		SOCKADDR_IN addrSrv;
		CncCondition  cnccondition;
		bool IniCncControl();//初始化机床
		bool Home();//机床回原点
		bool XYMove(float nX, float nY,CString asMode);//XY轴运动
		bool ZMove(float nZ,CString asMode);//Z轴运动
		bool CheckCncState();//机床状态查询函数
		int  GetCncMessage();//机床消息接收函数
        bool SendCommandToCnc(char *command);//机床命令直接发送函数	
        bool SetXYSpeed(float unXYSpeed);//速度设置
		bool SetZSpeed(float uiZSpeed);
		bool SetXPAbs(float nXPAbs);//X\Y\Z绝对位置
		bool SetYPAbs(float nYPAbs);
		bool SetZPAbs(float nZPAbs);
		bool SetXPRel(float nXPRel);//X\Y相对位置
		bool SetYPRel(float nYPRel);
};
