
// AOID.h : AOID Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif
#include "MainFrm.h"

#include "resource.h"       // ������
#include "AOID_i.h"
#include "MastProgInOut.h"

// CAOIDApp:
// �йش����ʵ�֣������ AOID.cpp
//

class CAOIDApp : public CWinAppEx
{
public:
	CAOIDApp();


// ��д
public:
	CMainFrame * pwnd;

	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;
	CMastProgInOut mastprog;//���������

//	CAOIDdatabase AOIDdatabase;//���ݿ����
	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CAOIDApp theApp;
