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
		bool IniAOIDControl();//��ʼ������
		bool Home();//������ԭ��
		bool XYMove(float nX, float nY,CString asMode);//XY���˶�
		bool ZMove(float nZ,CString asMode);//Z���˶�
		bool CheckAOIDState();//����״̬��ѯ����
		int  GetAOIDMessage();//������Ϣ���պ���
        bool SendCommandToAOID(char *command);//��������ֱ�ӷ��ͺ���	
        bool SetXYSpeed(float unXYSpeed);//�ٶ�����
		bool SetZSpeed(float uiZSpeed);
		bool SetXPAbs(float nXPAbs);//X\Y\Z����λ��
		bool SetYPAbs(float nYPAbs);
		bool SetZPAbs(float nZPAbs);
		bool SetXPRel(float nXPRel);//X\Y���λ��
		bool SetYPRel(float nYPRel);
};
