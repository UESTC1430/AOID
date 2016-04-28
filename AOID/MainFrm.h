
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
#include "ADIOtype.h"




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
	

	CCameraImageView m_cameraimageview;
	UserDatastruct  userdatastruct;//当前用户信息结构体实例化
	bool cmdviewflag;

//	Camera m_camera;
	UserMarkFlag  m_usermarkflag;

	Camera m_camera;
	CncControl m_cnccontrol;

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


