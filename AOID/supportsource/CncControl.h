#include <WinSock2.h>
#include <afxstr.h>

typedef struct CNCCONDITION
{
	int XD;//�ж��˶��Ƿ����
	int YD;
	int ZD;
	float XPOS;//λ��
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
		bool IniCncControl();//��ʼ������
		bool Home();//������ԭ��
		bool XYMove(float nX, float nY,CString asMode);//XY���˶�
		bool ZMove(float nZ,CString asMode);//Z���˶�
		bool CheckCncState();//����״̬��ѯ����
		int  GetCncMessage();//������Ϣ���պ���
        bool SendCommandToCnc(char *command);//��������ֱ�ӷ��ͺ���	
        bool SetXYSpeed(float unXYSpeed);//�ٶ�����
		bool SetZSpeed(float uiZSpeed);
		bool SetXPAbs(float nXPAbs);//X\Y\Z����λ��
		bool SetYPAbs(float nYPAbs);
		bool SetZPAbs(float nZPAbs);
		bool SetXPRel(float nXPRel);//X\Y���λ��
		bool SetYPRel(float nYPRel);
};
