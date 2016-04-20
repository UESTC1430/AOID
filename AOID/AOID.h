
// AOID.h : AOID 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif
#include "MainFrm.h"

#include "resource.h"       // 主符号
#include "AOID_i.h"
#include "MastProgInOut.h"

// CAOIDApp:
// 有关此类的实现，请参阅 AOID.cpp
//

class CAOIDApp : public CWinAppEx
{
public:
	CAOIDApp();


// 重写
public:
	CMainFrame * pwnd;

	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;
	CMastProgInOut mastprog;//主程序对象

//	CAOIDdatabase AOIDdatabase;//数据库对象
	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CAOIDApp theApp;
