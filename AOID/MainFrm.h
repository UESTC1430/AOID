
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

#pragma once

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
<<<<<<< HEAD
//	Camera m_camera;
	UserMarkFlag  m_usermarkflag;
=======
	Camera m_camera;
	CncControl m_cnccontrol;
>>>>>>> origin/master

// 特性
public:

// 操作
public:
    void ShowCmdView(bool flag=true);
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


