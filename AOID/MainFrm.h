
// MainFrm.h : CMainFrame ��Ľӿ�
//
#include "InfoPaneWnd.h"
//#include "oppanewnd.h"
#include"OpPaneWnd.h"
#include "CmdView.h"
#include "MenuPaneWnd.h"
#include "ProgPaneWnd.h"
#include "ToolPaneWnd.h"
#include "InfoPaneWnd.h"
#include "ImageProcess.h"
#include "Camera.h"
#include "CncControl.h"
#include "CV_picture.h"
#include "CameraImageView.h"
#include "AOIDtype.h"
#include "PathFunction.h"

//#pragma comment(lib,"Shlwapi.lib") 



#define CONTSTAT	0 //����������״̬
#define MOTISTAT	1//�ŷ����״̬
#define POSILIMT	2//������λ
#define AXLETEMP	3//�����¶�
#define AXLEPRES	4//����������ѹ
#define FREQSTAT	5//��Ƶ��״̬
#define KNIFPRES	6//������ѹ
#define HANDUP		7//��е����λ		
#define HANDDOWN	8//��е����λ
#define POSISWIT	9//��λ����
#define ROLLTEST	10//������
#define FOOTPOSI	11//ѹ��λ��
#define MEARSIGN	12//���߲����ź�
#define QICBIG		13//QIC��
#define QICSMALL	14//QICС
#define AXLESPED	15//����ת�� //����

#define InPause     1//��ʾ���������ڹ�����ͣ״̬
#define UnPause     0//��ʾ�������ڴ��״̬
#define IDLE_CNC        2//��ʾ�������ڲ���������״̬

#define red     RGB(255,0,0)
#define green   RGB(0,255,0)
#define blue    RGB(0,0,255)
#define yellow  RGB(255,255,0)
#define	white	RGB(255,255,255)
//--------������ɫ�궨�� (8��)
#define toolcolor1  RGB(220,20,60)   //�Ⱥ�
#define toolcolor2  RGB(255,105,180) //����ķۺ�
#define toolcolor3  RGB(139,0,139)   //������
#define toolcolor4  RGB(0,0,255)     //��
#define toolcolor5  RGB(0,191,255)   //������
#define toolcolor6  RGB(255,255,0)   //��
#define toolcolor7  RGB(128,128,0)   //���
#define toolcolor8  RGB(128,0,0)     //��ɫ
//--------
#define MaxNumber1 4400
#define ininumbers 20
#pragma once

extern float matchscale;
extern float matchangle;


typedef struct
{
	bool flagNeedCallback; //�ص����
	int  messageid;		//��Ϣid
	char *messagecode;//[4096]; //���
	unsigned long imilisecond;//��ʱ����ֵ	
}MessageType;
typedef struct _MessageNode
{
	MessageType message;
	struct _MessageNode *pnext;
}MessageNode;
typedef struct
{
	int ProcessType;//�涨ProcessType=1ָ����ʼ����ֹ��ģʽ ProcessType=2ָ������ѡ��ģʽ
	int ToolArary[20];
	int BeginLinkPos;
	int EndLinkPos;
}DrillLinkStruct;


typedef struct MESSAGELIST
{
	char m_MessageNote[256];
	int FlagCallBack;
	struct MESSAGELIST *pnextmessage;
}MessageList;

typedef struct MESSAGESTRUCT//��������ʾ��Ϣ �ṹ��
{
	int messagegid;//��Ϣid
	char message[256];//����
	struct MESSAGESTRUCT *next;
}MsgStruct;



class CncMessage
{
public: 
	CncMessage();
public:
	MessageNode *phead;
	MessageNode headnode;
	MessageType nextmessage;//��̬���ص���Ϣ
	char nextmessagebuf[4096];
	char returnstr[4096];
	CRITICAL_SECTION m_messageCriticalSection;
public:
	bool SendMessage(MessageType message); 
	bool GetMessage(MessageType * pmessage);
	void EmptyMessage();

public:
	int FindHomeCmdStr(char *finstr);
	~CncMessage();

};


class CShowMessage
{
public: 
	CShowMessage();
public:
	MsgStruct *firstnode;
	int MessagePush(MsgStruct *addnode);	
	MsgStruct MessagePop();	
	bool IsMsgQueueEmpty();
public:


public:
	int MessageInsert(MsgStruct *addnode);
	MsgStruct GetQueueFront();
	int DeleteMsgNode(int id);
	bool IsMsgExist(int id);
	~CShowMessage();

};


class CMainFrame : public CFrameWndEx
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame);
//����
public:
	COpPaneWnd    * m_pOpPaneWnd;
	CCmdView        m_CmdView;
	CMenuPaneWnd  * m_pMenuPaneWnd;//�зִ����°벿��
	CInfoPaneWnd  * m_pInfoPaneWnd;
	CProgPaneWnd  * m_pProgPaneWnd;
	CToolPaneWnd  * m_pToolPaneWnd;
	CImageProcess   m_imageprocess;
	CPathFunction *m_pathfuction;

	//---------------------------------------------------------
	bool ConvertThreadIsSuspend;//�̹߳���̬
	CncMessage *m_pcncmessage;//������õ�����Ϣ����
	CncMessage *m_pcnccmdmessage;//���������е���Ϣ����


	CShowMessage *operatemsgqueue;
	CShowMessage *warningmsgqueue;
	CShowMessage *errormsgqueue;

	CCameraImageView m_cameraimageview;
	UserDatastruct  userdatastruct;//��ǰ�û���Ϣ�ṹ��ʵ����
	bool cmdviewflag;

//	Camera m_camera;
	UserMarkFlag  m_usermarkflag;
	Camera m_camera;
	CncControl m_cnccontrol;

	int MacModeStatus;//�������п���ģʽ��0������ģʽ��1���ѻ�ģʽ��2������ģʽ
	ToolParaStruct m_toolparastruct[ATP_Tool_NUM];
	DrillNote drillnote[128];//ÿ������������Ĳ����ṹ��
	SpecialPoints specialpoints;
	bool AddMessageList(char *p,int num);
	MessageList *m_firstMessage;
	MessageList *m_CurrentMessage;
	MessageList *m_PreviousMessage;
	MessageList *m_tempMessage;//���ڼ�¼��������������ʱָ��
	MessageList *m_temp2Message;//���ڼ�¼������ǰ������λ�õ�ָ��


// ����
public:

// ����
public:
    void ShowCmdView(bool flag=true);
	void SPACEKEYDOWN();

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
//	virtual BOOL LoadFrame(UINT nIDresource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCToolBarImages m_UserImages;
	CSplitterWnd m_wndSplitter1;
	CSplitterWnd m_wndSplitter2;
// ���ɵ���Ϣӳ�亯��


protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//afx_msg void OnViewCustomize();
	//afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	//afx_msg void OnApplicationLook(UINT id);
	//afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

};


