// FindOrgan.cpp : implementation file
//

#include "stdafx.h"
#include "FindOrgan.h"
#include "MainFrm.h"
#include "AOID.h"
#include "MessageQueue.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CFindOrgan dialog

//extern CCncApp theApp;
CFindOrgan::CFindOrgan(CWnd* pParent /*=NULL*/)
	: CDialog(CFindOrgan::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFindOrgan)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFindOrgan::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindOrgan)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFindOrgan, CDialog)
	//{{AFX_MSG_MAP(CFindOrgan)
	ON_BN_CLICKED(IDC_BUTTON1, OnFindOrgan)
	ON_BN_CLICKED(IDC_BUTTON2, Cancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindOrgan message handlers

void CFindOrgan::OnFindOrgan() 
{
	// TODO: Add your control notification handler code here
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	pwnd->m_pProgPaneWnd->m_pProgressView->WarnMessage("等待回机械原点",white);
	pwnd->m_cnccontrol.Home();
	CDialog::OnOK();
}

void CFindOrgan::Cancel() 
{
	// TODO: Add your control notification handler code here
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	//选择不回原点
	MSGID msgid=HOMESTR;
	MsgStruct *node=(MsgStruct*)malloc(sizeof(MsgStruct));
	sprintf(node->message,"机床未执行回原点操作!");
	node->messagegid=msgid;
	node->next=NULL;
	pwnd->errormsgqueue->MessageInsert(node);

	pwnd->MacModeStatus=1;//脱机模式标志
	CDialog::OnCancel();
}
