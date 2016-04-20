
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
#include "ADIOtype.h"

#pragma once

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
	CCameraImageView m_cameraimageview;
	UserDatastruct  userdatastruct;//��ǰ�û���Ϣ�ṹ��ʵ����
	bool cmdviewflag;
<<<<<<< HEAD
//	Camera m_camera;
	UserMarkFlag  m_usermarkflag;
=======
	Camera m_camera;
	CncControl m_cnccontrol;
>>>>>>> origin/master

// ����
public:

// ����
public:
    void ShowCmdView(bool flag=true);
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


