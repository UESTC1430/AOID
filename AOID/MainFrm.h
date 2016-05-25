
// MainFrm.h : CMainFrame 类的接口
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



#define CONTSTAT	0 //控制器程序状态
#define MOTISTAT	1//伺服电机状态
#define POSILIMT	2//正负限位
#define AXLETEMP	3//主轴温度
#define AXLEPRES	4//主轴气浮气压
#define FREQSTAT	5//变频器状态
#define KNIFPRES	6//换刀气压
#define HANDUP		7//机械手上位		
#define HANDDOWN	8//机械手下位
#define POSISWIT	9//零位开关
#define ROLLTEST	10//断钻检测
#define FOOTPOSI	11//压脚位置
#define MEARSIGN	12//刀具测量信号
#define QICBIG		13//QIC大
#define QICSMALL	14//QIC小
#define AXLESPED	15//主轴转速 //串口

#define InPause     1//表示机床正处于工作暂停状态
#define UnPause     0//表示机床处于打孔状态
#define IDLE_CNC        2//表示机床处于不工作空闲状态

#define red     RGB(255,0,0)
#define green   RGB(0,255,0)
#define blue    RGB(0,0,255)
#define yellow  RGB(255,255,0)
#define	white	RGB(255,255,255)
//--------刀具颜色宏定义 (8种)
#define toolcolor1  RGB(220,20,60)   //腥红
#define toolcolor2  RGB(255,105,180) //热情的粉红
#define toolcolor3  RGB(139,0,139)   //深洋紫
#define toolcolor4  RGB(0,0,255)     //蓝
#define toolcolor5  RGB(0,191,255)   //深天蓝
#define toolcolor6  RGB(255,255,0)   //黄
#define toolcolor7  RGB(128,128,0)   //橄榄
#define toolcolor8  RGB(128,0,0)     //粟色
//--------
#define MaxNumber1 4400
#define ininumbers 20
#pragma once

extern float matchscale;
extern float matchangle;


typedef struct
{
	bool flagNeedCallback; //回调标记
	int  messageid;		//消息id
	char *messagecode;//[4096]; //命令串
	unsigned long imilisecond;//定时毫秒值	
}MessageType;
typedef struct _MessageNode
{
	MessageType message;
	struct _MessageNode *pnext;
}MessageNode;
typedef struct
{
	int ProcessType;//规定ProcessType=1指定起始和终止点模式 ProcessType=2指定刀具选择模式
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

typedef struct MESSAGESTRUCT//进度条显示消息 结构体
{
	int messagegid;//消息id
	char message[256];//内容
	struct MESSAGESTRUCT *next;
}MsgStruct;



class CncMessage
{
public: 
	CncMessage();
public:
	MessageNode *phead;
	MessageNode headnode;
	MessageType nextmessage;//动态返回的消息
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
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame);
//属性
public:
	COpPaneWnd    * m_pOpPaneWnd;
	CCmdView        m_CmdView;
	CMenuPaneWnd  * m_pMenuPaneWnd;//切分窗体下半部分
	CInfoPaneWnd  * m_pInfoPaneWnd;
	CProgPaneWnd  * m_pProgPaneWnd;
	CToolPaneWnd  * m_pToolPaneWnd;
	CImageProcess   m_imageprocess;
	CPathFunction *m_pathfuction;

	//---------------------------------------------------------
	bool ConvertThreadIsSuspend;//线程挂起态
	CncMessage *m_pcncmessage;//程序处理得到的消息队列
	CncMessage *m_pcnccmdmessage;//基于命令行的消息队列


	CShowMessage *operatemsgqueue;
	CShowMessage *warningmsgqueue;
	CShowMessage *errormsgqueue;

	CCameraImageView m_cameraimageview;
	UserDatastruct  userdatastruct;//当前用户信息结构体实例化
	bool cmdviewflag;

//	Camera m_camera;
	UserMarkFlag  m_usermarkflag;
	Camera m_camera;
	CncControl m_cnccontrol;

	int MacModeStatus;//机床运行控制模式。0：正常模式、1：脱机模式、2：检修模式
	ToolParaStruct m_toolparastruct[ATP_Tool_NUM];
	DrillNote drillnote[128];//每个刀具所保存的参数结构体
	SpecialPoints specialpoints;
	bool AddMessageList(char *p,int num);
	MessageList *m_firstMessage;
	MessageList *m_CurrentMessage;
	MessageList *m_PreviousMessage;
	MessageList *m_tempMessage;//用于记录命令队列链表的临时指针
	MessageList *m_temp2Message;//用于记录换刀后当前的链表位置的指针


// 特性
public:

// 操作
public:
    void ShowCmdView(bool flag=true);
	void SPACEKEYDOWN();

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
//	virtual BOOL LoadFrame(UINT nIDresource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCToolBarImages m_UserImages;
	CSplitterWnd m_wndSplitter1;
	CSplitterWnd m_wndSplitter2;
// 生成的消息映射函数


protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//afx_msg void OnViewCustomize();
	//afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	//afx_msg void OnApplicationLook(UINT id);
	//afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

};


