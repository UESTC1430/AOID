// ProgView.cpp : implementation file
//

#include "stdafx.h"
#include "AOID.h"
#include "ProgView.h"
#include "MainFrm.h"
UINT CNCMOVE2(LPVOID pParam);
#define  SW_length 240

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgView

IMPLEMENT_DYNCREATE(CProgView, CFormView)
//HTREEITEM  hitemofF1Sub2;
CProgView::CProgView()
: CFormView(CProgView::IDD)
{
	//{{AFX_DATA_INIT(CProgView)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	this->m_F1button = new CStaticButton(2);
	this->m_F2button = new CStaticButton(2);
	this->m_F3button = new CStaticButton(2);
	this->m_F4button = new CStaticButton(2);
	this->m_F5button = new CStaticButton(2);
	this->m_F6button = new CStaticButton(2);
	this->m_F7button = new CStaticButton(2);
	this->m_F8button = new CStaticButton(2);
	
	fbtnnum=8;
	RefreshTreeState = false;
}

CProgView::~CProgView()
{
	delete this->m_F1button;
	delete this->m_F2button;
	delete this->m_F3button;
	delete this->m_F4button;
	delete this->m_F5button;
	delete this->m_F6button;
	delete this->m_F7button;
	delete this->m_F8button;
	
	
	
}

void CProgView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_F1,*m_F1button);
	DDX_Control(pDX,IDC_F2,*m_F2button);
	DDX_Control(pDX,IDC_F3,*m_F3button);
	DDX_Control(pDX,IDC_F4,*m_F4button);
	DDX_Control(pDX,IDC_F5,*m_F5button);
	DDX_Control(pDX,IDC_F6,*m_F6button);
	DDX_Control(pDX,IDC_F7,*m_F7button);
	DDX_Control(pDX,IDC_F8,*m_F8button);

	CRgn rgn;
	rgn.CreateRectRgn(5,5,95,45);

	m_F1button->AppendBitmap(::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_F1_DOWN)));
	//先加载F1_DOWN位图是因为初始化时F1为按下状态   F1的Up、Down位图和其余的颜色相反
	m_F1button->AppendBitmap(::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_F1)));
	m_F1button->InitRgn(&rgn);

	m_F2button->AppendBitmap(::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_F2)));
	m_F2button->AppendBitmap(::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_F2_DOWN)));
	m_F2button->InitRgn(&rgn);

	m_F3button->AppendBitmap(::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_F3)));
	m_F3button->AppendBitmap(::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_F3_DOWN)));
	m_F3button->InitRgn(&rgn);

	m_F4button->AppendBitmap(::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_F4)));
	m_F4button->AppendBitmap(::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_F4_DOWN)));
	m_F4button->InitRgn(&rgn);

	m_F5button->AppendBitmap(::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_F5)));
	m_F5button->AppendBitmap(::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_F5_DOWN)));
	m_F5button->InitRgn(&rgn);

	m_F6button->AppendBitmap(::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_F6)));
	m_F6button->AppendBitmap(::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_F6_DOWN)));
	m_F6button->InitRgn(&rgn);

	m_F7button->AppendBitmap(::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_F7)));
	m_F7button->AppendBitmap(::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_F7_DOWN)));
	m_F7button->InitRgn(&rgn);

	m_F8button->AppendBitmap(::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_F8)));
	m_F8button->AppendBitmap(::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_F8_DOWN)));
	m_F8button->InitRgn(&rgn);





	//}}AFX_DATA_MAP

	DDX_Control(pDX, IDC_TREEF1, m_TreeF1);
	DDX_Control(pDX, IDC_TREEF2, m_TreeF2);
	DDX_Control(pDX, IDC_TREEF3, m_TreeF3);
	DDX_Control(pDX, IDC_TREEF4, m_TreeF4);
	DDX_Control(pDX, IDC_TREEF5, m_TreeF5);
	DDX_Control(pDX, IDC_TREEF6, m_TreeF6);
	DDX_Control(pDX, IDC_TREEF7, m_TreeF7);
	DDX_Control(pDX, IDC_TREEF8, m_TreeF8);
}


BEGIN_MESSAGE_MAP(CProgView, CFormView)
//{{AFX_MSG_MAP(CProgView)
ON_BN_CLICKED(IDC_F1, OnF1)
ON_BN_CLICKED(IDC_F2, OnF2)
ON_BN_CLICKED(IDC_F3, OnF3)
ON_BN_CLICKED(IDC_F4, OnF4)
ON_BN_CLICKED(IDC_F5, OnF5)
ON_BN_CLICKED(IDC_F6, OnF6)
ON_BN_CLICKED(IDC_F7, OnF7)
ON_BN_CLICKED(IDC_F8, OnF8)


ON_WM_CTLCOLOR()
//}}AFX_MSG_MAP
ON_NOTIFY(TVN_SELCHANGED, IDC_TREEF1, &CProgView::OnSelchangedTreef1)
ON_NOTIFY(TVN_SELCHANGED, IDC_TREEF2, &CProgView::OnSelchangedTreef2)
ON_NOTIFY(TVN_SELCHANGED, IDC_TREEF3, &CProgView::OnSelchangedTreef3)
ON_NOTIFY(TVN_SELCHANGED, IDC_TREEF4, &CProgView::OnSelchangedTreef4)
ON_NOTIFY(TVN_SELCHANGED, IDC_TREEF5, &CProgView::OnSelchangedTreef5)
ON_NOTIFY(TVN_SELCHANGED, IDC_TREEF6, &CProgView::OnSelchangedTreef6)
ON_NOTIFY(TVN_SELCHANGED, IDC_TREEF7, &CProgView::OnSelchangedTreef7)
ON_NOTIFY(TVN_SELCHANGED, IDC_TREEF8, &CProgView::OnSelchangedTreef8)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgView diagnostics

#ifdef _DEBUG
void CProgView::AssertValid() const
{
	CFormView::AssertValid();
}

void CProgView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CProgView message handlers




void CProgView::OnF1() 
{
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	//pwnd->m_pMenuPaneWnd->SwitchToView(VIEW_F1);	
	//pwnd->m_pOpPaneWnd->SwitchToView(VIEW_F3DELETEUSER);
	//CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	if(F1State == false)
	{
		return;
	}
	m_TreeF1.ShowWindow(SW_SHOW);
	m_TreeF2.ShowWindow(SW_HIDE);
	m_TreeF3.ShowWindow(SW_HIDE);
	m_TreeF4.ShowWindow(SW_HIDE);
	m_TreeF5.ShowWindow(SW_HIDE);
	m_TreeF6.ShowWindow(SW_HIDE);
	m_TreeF7.ShowWindow(SW_HIDE);
	m_TreeF8.ShowWindow(SW_HIDE);
	
	HTREEITEM hItem ;
	DWORD itemdata;
	hItem = m_TreeF1.GetSelectedItem();
	itemdata= m_TreeF1.GetItemData(hItem);
	m_TreeF1.Select(hItem,TVGN_DROPHILITE);//使选择的菜单项显示为选择状态
	pwnd->m_pOpPaneWnd->SwitchToView(itemdata);
	/*if(itemdata==VIEW_F3SUBITEM1)
	{
	//	pwnd->m_pOpPaneWnd->m_pF3SubItem1View->icopy =1;
	}*/
	fbtnnum=1;//当前在F1菜单下，此变量F4隐藏用
	pwnd->ShowCmdView(false);
}
void CProgView::OnF2() 
{
	//CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	//pwnd->m_pMenuPaneWnd->SwitchToView(VIEW_F2);
	//pwnd->m_pOpPaneWnd->SwitchToView(VIEW_F3CREATEUSER);
	
	if(F2State == false)
	{
		return;
	}
	m_TreeF1.ShowWindow(SW_HIDE);
	m_TreeF2.ShowWindow(SW_SHOW);
	m_TreeF3.ShowWindow(SW_HIDE);
	m_TreeF4.ShowWindow(SW_HIDE);
	m_TreeF5.ShowWindow(SW_HIDE);
	m_TreeF6.ShowWindow(SW_HIDE);
	m_TreeF7.ShowWindow(SW_HIDE);
	m_TreeF8.ShowWindow(SW_HIDE);
	
	HTREEITEM hItem ;
	DWORD itemdata;
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	hItem = m_TreeF2.GetSelectedItem();
	itemdata= m_TreeF2.GetItemData(hItem);
	m_TreeF2.Select(hItem,TVGN_DROPHILITE);//使选择的菜单项显示为选择状态
	pwnd->m_pOpPaneWnd->SwitchToView(itemdata);
	fbtnnum=2;
	pwnd->ShowCmdView(false);
}
void CProgView::OnF3() 
{
	if(F3State == false)
	{
		return;
	}
	m_TreeF1.ShowWindow(SW_HIDE);
	m_TreeF2.ShowWindow(SW_HIDE);
	m_TreeF3.ShowWindow(SW_SHOW);
	m_TreeF4.ShowWindow(SW_HIDE);
	m_TreeF5.ShowWindow(SW_HIDE);
	m_TreeF6.ShowWindow(SW_HIDE);
	m_TreeF7.ShowWindow(SW_HIDE);
	m_TreeF8.ShowWindow(SW_HIDE);
	
	HTREEITEM hItem ;
	DWORD itemdata;
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	hItem = m_TreeF3.GetSelectedItem();
	itemdata= m_TreeF3.GetItemData(hItem);
	m_TreeF3.Select(hItem,TVGN_DROPHILITE);//使选择的菜单项显示为选择状态
	pwnd->m_pOpPaneWnd->SwitchToView(itemdata);
	fbtnnum=3;
	pwnd->ShowCmdView(false);
}
void CProgView::OnF4() 
{
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	pwnd->ShowCmdView();//同键盘按下F4
}
void CProgView::OnF5() 
{
	if(F5State == false)
	{
		return;
	}
	m_TreeF1.ShowWindow(SW_HIDE);
	m_TreeF2.ShowWindow(SW_HIDE);
	m_TreeF3.ShowWindow(SW_HIDE);
	m_TreeF4.ShowWindow(SW_HIDE);
	m_TreeF5.ShowWindow(SW_SHOW);
	m_TreeF6.ShowWindow(SW_HIDE);
	m_TreeF7.ShowWindow(SW_HIDE);
	m_TreeF8.ShowWindow(SW_HIDE);

	HTREEITEM hItem ;
	DWORD itemdata;
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	hItem = m_TreeF5.GetSelectedItem();
	itemdata= m_TreeF5.GetItemData(hItem);
	m_TreeF5.Select(hItem,TVGN_DROPHILITE);//使选择的菜单项显示为选择状态
	pwnd->m_pOpPaneWnd->SwitchToView(itemdata);
	fbtnnum=5;
	pwnd->ShowCmdView(false);
}
void CProgView::OnF6() 
{
	if(F6State == false)
	{
		return;
	}
	m_TreeF1.ShowWindow(SW_HIDE);
	m_TreeF2.ShowWindow(SW_HIDE);
	m_TreeF3.ShowWindow(SW_HIDE);
	m_TreeF4.ShowWindow(SW_HIDE);
	m_TreeF5.ShowWindow(SW_HIDE);
	m_TreeF6.ShowWindow(SW_SHOW);
	m_TreeF7.ShowWindow(SW_HIDE);
	m_TreeF8.ShowWindow(SW_HIDE);
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	fbtnnum=6;
	pwnd->ShowCmdView(false);
}
void CProgView::OnF7() 
{
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	HTREEITEM hItem ;
	DWORD itemdata;
	hItem = m_TreeF3.GetSelectedItem();
	itemdata= m_TreeF3.GetItemData(hItem);
	m_TreeF3.Select(hItem,TVGN_DROPHILITE);
	pwnd->m_pOpPaneWnd->SwitchToView(itemdata);
	fbtnnum=7;
	pwnd->ShowCmdView(false);
	if(false==pwnd->m_camera.GetConnect())
		return;
	CWinThread *showview= AfxBeginThread(CNCMOVE2,(LPVOID)(pwnd));
	pwnd->m_camera.GetPicture();
	pwnd->m_camera.CloseCamera();	
	pwnd->m_cnccontrol.XYMove(-SW_length,0,"REL");
	pwnd->m_cnccontrol.CheckCncState();
	if (pwnd->m_cnccontrol.cnccondition.XD==1&&pwnd->m_cnccontrol.cnccondition.YD==1&&pwnd->m_cnccontrol.cnccondition.YD)
		F7State=true;
}
void CProgView::OnF8() 
{
	if(F8State == false)
	{
		return;
	}
	m_TreeF1.ShowWindow(SW_HIDE);
	m_TreeF2.ShowWindow(SW_HIDE);
	m_TreeF3.ShowWindow(SW_HIDE);
	m_TreeF4.ShowWindow(SW_HIDE);
	m_TreeF5.ShowWindow(SW_HIDE);
	m_TreeF6.ShowWindow(SW_HIDE);
	m_TreeF7.ShowWindow(SW_HIDE);
	m_TreeF8.ShowWindow(SW_SHOW);
	
	HTREEITEM hItem ;
	DWORD itemdata;
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	hItem = m_TreeF8.GetSelectedItem();
	itemdata= m_TreeF8.GetItemData(hItem);
	m_TreeF8.Select(hItem,TVGN_DROPHILITE);//使选择的菜单项显示为选择状态
	pwnd->m_pOpPaneWnd->SwitchToView(itemdata);
	fbtnnum=8;
	pwnd->ShowCmdView(false);
}
void CProgView::GetItemByData(int idata,HTREEITEM * pitem)
{
	switch(idata)
	{
	case VIEW_F1SUBITEM1://	33
		*pitem = hF1SubItem1;
		break;
	case VIEW_F1SUBITEM2://34
		*pitem = hF1SubItem2;
		break;

/*	case VIEW_F1SUBITEM21://	34
		*pitem = hF1SubItem21;
		break;
	case VIEW_F1SUBITEM22://	35
		*pitem = hF1SubItem22;
		break;
	case VIEW_F1SUBITEM23://	36
		*pitem = hF1SubItem23;
		break;*/
	case VIEW_F1SUBITEM3://	37
		*pitem = hF1SubItem3;
		break;
	case VIEW_F1SUBITEM4:	//38
		*pitem = hF1SubItem4;
		break;
	case VIEW_F1SUBITEM5://	39
		*pitem = hF1SubItem5;
		break;
/*	case VIEW_F1SUBITEM51://	39
		*pitem = hF1SubItem51;
		break;
	case VIEW_F1SUBITEM52://	40
		*pitem = hF1SubItem52;
		break;*/
	case VIEW_F1SUBITEM6://		41
		*pitem = hF1SubItem6;
		break;
	
	default: 
		break;
	}
	
}
void CProgView::RefreshTreeByUser()
{		_variant_t var;

RefreshTreeState = true;

RefreshTreeState = false;	

}
void CProgView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	int i;
	HTREEITEM hItem ;
	
	// TODO: Add your specialized code here and/or call the base class
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();	
	_variant_t var;
	//初始化操作权限
	/*	var = theApp.pwnd->m_pRecordUser->GetCollect("CSoftWareInfoView");
	theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F1SUBITEM1-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
	var = theApp.pwnd->m_pRecordUser->GetCollect("CMastAxleTimeView");
	theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F1SUBITEM21-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
	
	  var = theApp.pwnd->m_pRecordUser->GetCollect("CHoleNumView");
	  theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F1SUBITEM22-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
	  
		var = theApp.pwnd->m_pRecordUser->GetCollect("CMerchineRoutView");
		theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F1SUBITEM23-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
		
		  var = theApp.pwnd->m_pRecordUser->GetCollect("CUserAdminView");
		  theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F1SUBITEM3-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
		  
			var = theApp.pwnd->m_pRecordUser->GetCollect("CMerchineRecordView");
			theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F1SUBITEM51-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
			
			  var = theApp.pwnd->m_pRecordUser->GetCollect("CBreakKnifeProgView");
			  theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F1SUBITEM52-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
			  
				var = theApp.pwnd->m_pRecordUser->GetCollect("CLicenseView");
				theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F1SUBITEM6-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
				
				  var = theApp.pwnd->m_pRecordUser->GetCollect("CMastProgInView");
				  theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F2SUBITEM11-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
				  
					var = theApp.pwnd->m_pRecordUser->GetCollect("CSubProgInView");
					theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F2SUBITEM12-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
					
					  var = theApp.pwnd->m_pRecordUser->GetCollect("CATPInView");
					  theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F2SUBITEM13-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
					  
						var = theApp.pwnd->m_pRecordUser->GetCollect("CDiameterInView");
						theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F2SUBITEM14-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
						
						  var = theApp.pwnd->m_pRecordUser->GetCollect("CMastProgOutView");
						  theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F2SUBITEM21-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
						  
							var = theApp.pwnd->m_pRecordUser->GetCollect("CSubProgOutView");
							theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F2SUBITEM22-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
							
							  var = theApp.pwnd->m_pRecordUser->GetCollect("CATPOutView");
							  theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F2SUBITEM23-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
							  
								var = theApp.pwnd->m_pRecordUser->GetCollect("CDiameterOutView");
								theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F2SUBITEM24-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
								
								  var = theApp.pwnd->m_pRecordUser->GetCollect("CF3SubItem1View");
								  theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F3SUBITEM1-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
								  
									//var = theApp.pwnd->m_pRecordUser->GetCollect("CF4SubItem1View");
									//theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F4SUBITEM1-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
									
									  
										
										  var = theApp.pwnd->m_pRecordUser->GetCollect("CUserTokenView");
										  theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F5SUBITEM1-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
										  
											var = theApp.pwnd->m_pRecordUser->GetCollect("COptiParaView");
											theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F5SUBITEM2-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
											
											  var = theApp.pwnd->m_pRecordUser->GetCollect("CInputSigDiagView");
											  theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F5SUBITEM3-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
											  
												//var = theApp.pwnd->m_pRecordUser->GetCollect("CF5SubItem4View");
												//theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F5SUBITEM4-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
												
												  var = theApp.pwnd->m_pRecordUser->GetCollect("CPosDiagnoseView");
												  theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F5SUBITEM5-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
												  
													var = theApp.pwnd->m_pRecordUser->GetCollect("CServeFreqView");
													theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F5SUBITEM6-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
													
													  var = theApp.pwnd->m_pRecordUser->GetCollect("CLocatePosView");
													  theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F5SUBITEM7-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
													  
														
														  
															var = theApp.pwnd->m_pRecordUser->GetCollect("CStaticList1View");
															theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F6SUBITEM1-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
															
															  var = theApp.pwnd->m_pRecordUser->GetCollect("CStaticList2View");
															  theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F6SUBITEM2-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
															  
																var = theApp.pwnd->m_pRecordUser->GetCollect("CDynamicView");
																theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F6SUBITEM3-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
																
																  var = theApp.pwnd->m_pRecordUser->GetCollect("CCutterHeadGraphView");
																  theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F6SUBITEM4-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
																  
																	var = theApp.pwnd->m_pRecordUser->GetCollect("CCutterHeadConnectView");
																	theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F6SUBITEM5-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
																	
																	  var = theApp.pwnd->m_pRecordUser->GetCollect("CCutterChangeView");
																	  theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F6SUBITEM6-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
																	  
																		var = theApp.pwnd->m_pRecordUser->GetCollect("CCutterDifferenceView");
																		theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F6SUBITEM7-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
																		
																		  var = theApp.pwnd->m_pRecordUser->GetCollect("CDifferenceScopeView");
																		  theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F6SUBITEM8-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
																		  
																			var = theApp.pwnd->m_pRecordUser->GetCollect("CDiameterListView");
																			theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F6SUBITEM9-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
																			
																			  var = theApp.pwnd->m_pRecordUser->GetCollect("CSegMentationDrillView");
																			  theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F6SUBITEM10-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
																			  
																				//	var = theApp.pwnd->m_pRecordUser->GetCollect("CF8SubItem1View");
																				//	theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F8SUBITEM1-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
																				
																				  var = theApp.pwnd->m_pRecordUser->GetCollect("CWorkStateView");
																				  theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F8SUBITEM1-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
																				  
																					var = theApp.pwnd->m_pRecordUser->GetCollect("CMFunctionView");
																					theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F8SUBITEM2-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
																					
																					  var = theApp.pwnd->m_pRecordUser->GetCollect("CInchFunctionView");
																					  theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F8SUBITEM3-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
																					  
																						var = theApp.pwnd->m_pRecordUser->GetCollect("CZHeightView");
																						theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F8SUBITEM4-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
																						
																						  var = theApp.pwnd->m_pRecordUser->GetCollect("COrigFunctionView");
																						  theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F8SUBITEM5-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
																						  
																							var = theApp.pwnd->m_pRecordUser->GetCollect("CScanView");
																							theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F8SUBITEM6-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
																							
																							  //var = theApp.pwnd->m_pRecordUser->GetCollect("CScanView");
																							  //theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F8SUBITEM7-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
																							  
																								var = theApp.pwnd->m_pRecordUser->GetCollect("CTestCheckView");
																								theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F8SUBITEM8-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
																								
																								  var = theApp.pwnd->m_pRecordUser->GetCollect("CWorkOrderCheckView");
																								  theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F8SUBITEM9-VIEW_F1SUBITEM1]=atoi((LPCSTR)_bstr_t(var));
*/
//必须修改权限数据库，才能用上面注释的代码，现在所有权限全部打开
for(i=VIEW_F1SUBITEM1;i<VIEW_F8SUBITEM6;i++)
{
	pwnd->userdatastruct.m_OpLevel[i-VIEW_F1SUBITEM1]=1;
}


//构造F1命令树,如果在数据库中可配置操作权限的需要根据权限来设置
//是否需要添加该操作
hF1Item= m_TreeF1.InsertItem("F1系统",NULL,NULL);
hF1SubItem1= m_TreeF1.InsertItem(_T("结束"),NULL,NULL,hF1Item);
m_TreeF1.SetItemData(hF1SubItem1,VIEW_F1SUBITEM1);
//hF1SubItem2= m_TreeF1.InsertItem(_T("操作资料"),NULL,NULL,hF1Item);
hF1SubItem2= m_TreeF1.InsertItem(_T("统计分析"),NULL,NULL,hF1Item);
m_TreeF1.SetItemData(hF1SubItem2,VIEW_F1SUBITEM2);
//根据数据库权限设置来设置是否添加该选项	
/*if(theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F1SUBITEM21-VIEW_F1SUBITEM1]==1)
{
	hF1SubItem21 =m_TreeF1.InsertItem(_T("主轴运转时间"),NULL,NULL,hF1SubItem2); 
	m_TreeF1.SetItemData(hF1SubItem21,VIEW_F1SUBITEM21);
}
else
{
}

if(theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F1SUBITEM22-VIEW_F1SUBITEM1]==1)
{
	hF1SubItem22 =m_TreeF1.InsertItem(_T("打孔个数"),NULL,NULL,hF1SubItem2); 
	m_TreeF1.SetItemData(hF1SubItem22,VIEW_F1SUBITEM22);
}
else
{
}

if(theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F1SUBITEM23-VIEW_F1SUBITEM1]==1)
{
	hF1SubItem23 =m_TreeF1.InsertItem(_T("机床运动路程"),NULL,NULL,hF1SubItem2);
	m_TreeF1.SetItemData(hF1SubItem23,VIEW_F1SUBITEM23);
}
else
{
}*/
hF1SubItem3= m_TreeF1.InsertItem(_T("用户管理"),NULL,NULL,hF1Item);
m_TreeF1.SetItemData(hF1SubItem3,VIEW_F1SUBITEM3);

hF1SubItem4= m_TreeF1.InsertItem(_T("文件与目录设置"),NULL,NULL,hF1Item);
m_TreeF1.SetItemData(hF1SubItem4,VIEW_F1SUBITEM4);

hF1SubItem5= m_TreeF1.InsertItem(_T("履历文件"),NULL,NULL,hF1Item);
m_TreeF1.SetItemData(hF1SubItem5,VIEW_F1SUBITEM5);


/*if(theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F1SUBITEM51-VIEW_F1SUBITEM1]==1)
{
	hF1SubItem51 =m_TreeF1.InsertItem(_T("履历文件"),NULL,NULL,hF1SubItem5); 
	m_TreeF1.SetItemData(hF1SubItem51,VIEW_F1SUBITEM51);
}
else
{
}
*/
/*
if(theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F1SUBITEM52-VIEW_F1SUBITEM1]==1)
{
	hF1SubItem52 =m_TreeF1.InsertItem(_T("断刀情况及分析"),NULL,NULL,hF1SubItem5); 
	m_TreeF1.SetItemData(hF1SubItem52,VIEW_F1SUBITEM52);
}
else
{
}*/
hF1SubItem6= m_TreeF1.InsertItem(_T("授权许可"),NULL,NULL,hF1Item);
m_TreeF1.SetItemData(hF1SubItem6,VIEW_F1SUBITEM6);

m_TreeF1.Expand(hF1Item,TVE_EXPAND);
m_TreeF1.Expand(hF1SubItem2,TVE_EXPAND);
m_TreeF1.Expand(hF1SubItem5,TVE_EXPAND);


for(i=VIEW_F1SUBITEM1;i<=VIEW_F1SUBITEM6;i++)
{
	if(pwnd->userdatastruct.m_OpLevel[i-VIEW_F1SUBITEM1]== 1 )
	{
		GetItemByData(i,&hItem);
		m_TreeF1.SelectItem(hItem);
		//使选择的菜单项显示为选择状态
		break;
	}
}
if(i>VIEW_F1SUBITEM6)
{
	F1State = false;
	m_F1button->SetEnable(false);
}
else
{
	F1State = true;
	m_F1button->SetEnable(true);
}


//构造F2命令树

hF2Item= m_TreeF2.InsertItem("F2数据输入输出",NULL,NULL);
hF2SubItem1= m_TreeF2.InsertItem("DATA IN",NULL,NULL,hF2Item);
hF2SubItem11= m_TreeF2.InsertItem("生产程序",NULL,NULL,hF2SubItem1);
m_TreeF2.SetItemData(hF2SubItem11,VIEW_F2SUBITEM11);
hF2SubItem12= m_TreeF2.InsertItem("副程序",NULL,NULL,hF2SubItem1);
m_TreeF2.SetItemData(hF2SubItem12,VIEW_F2SUBITEM12);


/* 
if(theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F2SUBITEM13-VIEW_F1SUBITEM1]==1)
{
	hF2SubItem13= m_TreeF2.InsertItem("ATP",NULL,NULL,hF2SubItem1);
	m_TreeF2.SetItemData(hF2SubItem13,VIEW_F2SUBITEM13);
}
else
{
}
if(theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F2SUBITEM14-VIEW_F1SUBITEM1]==1)
{
	hF2SubItem14= m_TreeF2.InsertItem("直径表",NULL,NULL,hF2SubItem1);
	m_TreeF2.SetItemData(hF2SubItem14,VIEW_F2SUBITEM14);
}
else
{
}
hF2SubItem2= m_TreeF2.InsertItem("DATA OUT",NULL,NULL,hF2Item);

if(theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F2SUBITEM21-VIEW_F1SUBITEM1]==1)
{
	hF2SubItem21= m_TreeF2.InsertItem("生产程序",NULL,NULL,hF2SubItem2);
	m_TreeF2.SetItemData(hF2SubItem21,VIEW_F2SUBITEM21);
}
else
{
}
if(theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F2SUBITEM22-VIEW_F1SUBITEM1]==1)
{
	hF2SubItem22= m_TreeF2.InsertItem("副程序",NULL,NULL,hF2SubItem2);
	m_TreeF2.SetItemData(hF2SubItem22,VIEW_F2SUBITEM22);
}
else
{
}
if(theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F2SUBITEM23-VIEW_F1SUBITEM1]==1)
{
	hF2SubItem23= m_TreeF2.InsertItem("ATP",NULL,NULL,hF2SubItem2);
	m_TreeF2.SetItemData(hF2SubItem23,VIEW_F2SUBITEM23);
}
else
{
}
if(theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F2SUBITEM24-VIEW_F1SUBITEM1]==1)
{
	hF2SubItem24= m_TreeF2.InsertItem("直径表",NULL,NULL,hF2SubItem2);
	m_TreeF2.SetItemData(hF2SubItem24,VIEW_F2SUBITEM24);
}
else
{
}
*/
m_TreeF2.Expand(hF2Item,TVE_EXPAND);
m_TreeF2.Expand(hF2SubItem1,TVE_EXPAND);

m_TreeF2.Expand(hF2SubItem2,TVE_EXPAND);

for(i=VIEW_F2SUBITEM11;i<=VIEW_F2SUBITEM12;i++)
{
	if(pwnd->userdatastruct.m_OpLevel[i-VIEW_F1SUBITEM1]== 1 )
	{
		GetItemByData(i,&hItem);
		m_TreeF2.SelectItem(hItem);
		m_TreeF2.Select(hItem,TVGN_DROPHILITE);//使选择的菜单项显示为选择状态
		break;
	}
}

if(i>VIEW_F2SUBITEM12)
{
	F2State = false;
	m_F2button->SetEnable(false);
}
else
{
	F2State = true;
	m_F2button->SetEnable(true);
}
//构造F3命令树

hF3Item= m_TreeF3.InsertItem("F3执行程序功能",NULL,NULL);
hF3SubItem1= m_TreeF3.InsertItem(_T("图像对比"),NULL,NULL,hF3Item);
m_TreeF3.SetItemData(hF3SubItem1,VIEW_F3SUBITEM1);


m_TreeF3.Expand(hF3Item,TVE_EXPAND);
m_TreeF3.SelectItem(hF3SubItem1);
m_TreeF3.Select(hF3SubItem1,TVGN_DROPHILITE);//使选择的菜单项显示为选择状态
/*if(theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F3SUBITEM1-VIEW_F1SUBITEM1]==1)
{
	F3State = true;
	m_F3button->SetEnable(true);
}
else
{
	F3State = false;
	m_F3button->SetEnable(false);
}*/

//构造F4命令树

//构造F5命令树

hF5Item= m_TreeF5.InsertItem("F5诊断",NULL,NULL);

if(pwnd->userdatastruct.m_OpLevel[VIEW_F5SUBITEM1-VIEW_F1SUBITEM1]==1)
{
	hF5SubItem1= m_TreeF5.InsertItem("用户标记",NULL,NULL,hF5Item);
	m_TreeF5.SetItemData(hF5SubItem1,VIEW_F5SUBITEM1);
}
else
{
}

/*if(theApp.pwnd->userdatastruct.m_OpLevel[VIEW_F5SUBITEM2-VIEW_F1SUBITEM1]==1)
{
	hF5SubItem2= m_TreeF5.InsertItem("优化参数",NULL,NULL,hF5Item);
	m_TreeF5.SetItemData(hF5SubItem2,VIEW_F5SUBITEM2);
}
else
{
}
*/
if(pwnd->userdatastruct.m_OpLevel[VIEW_F5SUBITEM3-VIEW_F1SUBITEM1]==1)
{
	hF5SubItem3= m_TreeF5.InsertItem("输入端口",NULL,NULL,hF5Item);
	m_TreeF5.SetItemData(hF5SubItem3,VIEW_F5SUBITEM2);
}
else
{
}

hF5SubItem4= m_TreeF5.InsertItem("输出端口",NULL,NULL,hF5Item);
m_TreeF5.SetItemData(hF5SubItem4,VIEW_F5SUBITEM3);
hF5SubItem5= m_TreeF5.InsertItem("伺服器诊断",NULL,NULL,hF5Item);
m_TreeF5.SetItemData(hF5SubItem5,VIEW_F5SUBITEM4);
hF5SubItem6= m_TreeF5.InsertItem("摄像头对焦",NULL,NULL,hF5Item);
m_TreeF6.SetItemData(hF5SubItem6,VIEW_F5SUBITEM5);
//hF5SubItem7= m_TreeF5.InsertItem("定位销钉",NULL,NULL,hF5Item);
//m_TreeF5.SetItemData(hF5SubItem7,VIEW_F5SUBITEM7);




m_TreeF5.Expand(hF5Item,TVE_EXPAND);

for(i=VIEW_F5SUBITEM1;i<=VIEW_F5SUBITEM6;i++)
{
	if(pwnd->userdatastruct.m_OpLevel[i-VIEW_F1SUBITEM1]== 1 )
	{
		GetItemByData(i,&hItem);
		m_TreeF5.SelectItem(hItem);
		m_TreeF5.Select(hItem,TVGN_DROPHILITE);//使选择的菜单项显示为选择状态
		break;
	}
	
}
if(i>VIEW_F5SUBITEM6)
{
	F5State = false;
	m_F5button->SetEnable(false);
}
else
{
	F5State = true;
	m_F5button->SetEnable(true);
}


//构造F6命令树
/*
hF6Item= m_TreeF6.InsertItem("F6刀具",NULL,NULL);
hF6SubItem1= m_TreeF6.InsertItem("刀具列表（静态1）",NULL,NULL,hF6Item);
m_TreeF6.SetItemData(hF6SubItem1,VIEW_F6SUBITEM1);
hF6SubItem2= m_TreeF6.InsertItem("刀具列表（静态2）",NULL,NULL,hF6Item);
m_TreeF6.SetItemData(hF6SubItem2,VIEW_F6SUBITEM2);
hF6SubItem3= m_TreeF6.InsertItem("刀具列表（动态）",NULL,NULL,hF6Item);
m_TreeF6.SetItemData(hF6SubItem3,VIEW_F6SUBITEM3);
hF6SubItem4= m_TreeF6.InsertItem("刀盘",NULL,NULL,hF6Item);
m_TreeF6.SetItemData(hF6SubItem4,VIEW_F6SUBITEM4);
hF6SubItem5= m_TreeF6.InsertItem("刀具转换",NULL,NULL,hF6Item);
m_TreeF6.SetItemData(hF6SubItem5,VIEW_F6SUBITEM5);
hF6SubItem6= m_TreeF6.InsertItem("刀盘连接",NULL,NULL,hF6Item);
m_TreeF6.SetItemData(hF6SubItem6,VIEW_F6SUBITEM6);
hF6SubItem7= m_TreeF6.InsertItem("测量结果",NULL,NULL,hF6Item);
m_TreeF6.SetItemData(hF6SubItem7,VIEW_F6SUBITEM7);
hF6SubItem8= m_TreeF6.InsertItem("刀具公差表",NULL,NULL,hF6Item);
m_TreeF6.SetItemData(hF6SubItem8,VIEW_F6SUBITEM8);
hF6SubItem9= m_TreeF6.InsertItem("直径表",NULL,NULL,hF6Item);
m_TreeF6.SetItemData(hF6SubItem9,VIEW_F6SUBITEM9);
hF6SubItem10= m_TreeF6.InsertItem("分段钻",NULL,NULL,hF6Item);
m_TreeF6.SetItemData(hF6SubItem10,VIEW_F6SUBITEM10);

m_TreeF6.Expand(hF6Item,TVE_EXPAND);
for(i=VIEW_F6SUBITEM1;i<=VIEW_F6SUBITEM10;i++)
{
	if(theApp.pwnd->userdatastruct.m_OpLevel[i-VIEW_F1SUBITEM1]== 1 )
	{
		GetItemByData(i,&hItem);
		m_TreeF6.SelectItem(hItem);
		m_TreeF6.Select(hItem,TVGN_DROPHILITE);//使选择的菜单项显示为选择状态
		break;
	}
	
}
if(i>VIEW_F6SUBITEM10)
{
	F6State = false;
	m_F6button->SetEnable(false);
}
else
{
	F6State = true;
	m_F6button->SetEnable(true);
}*/
//构造F7命令树
hF7Item= m_TreeF7.InsertItem("F7开始选项",NULL,NULL);

hF7SubItem1= m_TreeF7.InsertItem("选项",NULL,NULL,hF7Item);
m_TreeF7.SetItemData(hF7SubItem1,VIEW_F7SUBITEM1);

m_TreeF7.Expand(hF7Item,TVE_EXPAND);
for(i=VIEW_F7SUBITEM1;i<=VIEW_F7SUBITEM1;i++)
{
	if(pwnd->userdatastruct.m_OpLevel[i-VIEW_F1SUBITEM1]== 1 )
	{
		GetItemByData(i,&hItem);
		m_TreeF7.SelectItem(hItem);
		m_TreeF7.Select(hItem,TVGN_DROPHILITE);//使选择的菜单项显示为选择状态
		break;
	}
	
}
if(i>VIEW_F7SUBITEM1)
{
	F7State = false;
	m_F7button->SetEnable(false);
}
else
{
	F7State = true;
	m_F7button->SetEnable(true);

}

//构造F8命令树
hF8Item= m_TreeF8.InsertItem("F8工作",NULL,NULL);
hF8SubItem1= m_TreeF8.InsertItem("灯光",NULL,NULL,hF8Item);
m_TreeF8.SetItemData(hF8SubItem1,VIEW_F8SUBITEM1);
hF8SubItem2= m_TreeF8.InsertItem("M功能",NULL,NULL,hF8Item);
m_TreeF8.SetItemData(hF8SubItem2,VIEW_F8SUBITEM2);
hF8SubItem3= m_TreeF8.InsertItem("寸动",NULL,NULL,hF8Item);
m_TreeF8.SetItemData(hF8SubItem3,VIEW_F8SUBITEM3);
//hF8SubItem4= m_TreeF8.InsertItem("Z轴",NULL,NULL,hF8Item);
//m_TreeF8.SetItemData(hF8SubItem4,VIEW_F8SUBITEM4);
hF8SubItem5= m_TreeF8.InsertItem("零点",NULL,NULL,hF8Item);
m_TreeF8.SetItemData(hF8SubItem5,VIEW_F8SUBITEM4);
hF8SubItem6= m_TreeF8.InsertItem("摄像头设置",NULL,NULL,hF8Item);
m_TreeF8.SetItemData(hF8SubItem6,VIEW_F8SUBITEM5);
/*hF8SubItem7= m_TreeF8.InsertItem("安全区域",NULL,NULL,hF8Item);
m_TreeF8.SetItemData(hF8SubItem7,VIEW_F8SUBITEM7);
hF8SubItem8= m_TreeF8.InsertItem("检查",NULL,NULL,hF8Item);
m_TreeF8.SetItemData(hF8SubItem8,VIEW_F8SUBITEM8);
hF8SubItem9= m_TreeF8.InsertItem("工序列表",NULL,NULL,hF8Item);
m_TreeF8.SetItemData(hF8SubItem9,VIEW_F8SUBITEM9);
*/



m_TreeF8.Expand(hF8Item,TVE_EXPAND);
for(i=VIEW_F8SUBITEM1;i<=VIEW_F8SUBITEM6;i++)
{
	if(pwnd->userdatastruct.m_OpLevel[i-VIEW_F1SUBITEM1]== 1 )
	{
		GetItemByData(i,&hItem);
		m_TreeF8.SelectItem(hItem);
		m_TreeF8.Select(hItem,TVGN_DROPHILITE);//使选择的菜单项显示为选择状态
		break;
	}
}
if(i>VIEW_F8SUBITEM6)
{
	F8State = false;
	m_F8button->SetEnable(false);
	
}
else
{
	F8State = true;
	m_F8button->SetEnable(true);
}



m_TreeF1.ShowWindow(SW_SHOW);
m_TreeF2.ShowWindow(SW_HIDE);
m_TreeF3.ShowWindow(SW_HIDE);
m_TreeF4.ShowWindow(SW_HIDE);
m_TreeF5.ShowWindow(SW_HIDE);
m_TreeF6.ShowWindow(SW_HIDE);
m_TreeF7.ShowWindow(SW_HIDE);
m_TreeF8.ShowWindow(SW_HIDE);






}
void CProgView::OnSelchangedTreef1(NMHDR *pNMHDR, LRESULT *pResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	HTREEITEM hItem ;
	DWORD itemdata;
	if(RefreshTreeState == true)
	{
		return;
	}
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	hItem = m_TreeF1.GetSelectedItem();
	itemdata= m_TreeF1.GetItemData(hItem);
	m_TreeF1.Select(hItem,TVGN_DROPHILITE);//使选择的菜单项显示为选择状态
	switch(itemdata)
	{
	case VIEW_F1SUBITEM1:
		pwnd->m_pOpPaneWnd->SwitchToView(VIEW_F1SUBITEM1);
		break;
	case VIEW_F1SUBITEM2:
		pwnd->m_pOpPaneWnd->SwitchToView(VIEW_F1SUBITEM2);
		break;
	/*case VIEW_F1SUBITEM21:
		pwnd->m_pOpPaneWnd->SwitchToView(VIEW_F1SUBITEM21);
		break;
	case VIEW_F1SUBITEM22:
		pwnd->m_pOpPaneWnd->SwitchToView(VIEW_F1SUBITEM22);
		break;
	case VIEW_F1SUBITEM23:
		pwnd->m_pOpPaneWnd->SwitchToView(VIEW_F1SUBITEM23);
		break;*/
	case VIEW_F1SUBITEM3:
		pwnd->m_pOpPaneWnd->SwitchToView(VIEW_F1SUBITEM3);
		break;
	case VIEW_F1SUBITEM4:
		pwnd->m_pOpPaneWnd->SwitchToView(VIEW_F1SUBITEM4);
		break;

	case VIEW_F1SUBITEM5:
		pwnd->m_pOpPaneWnd->SwitchToView(VIEW_F1SUBITEM5);
		break;

/*	case VIEW_F1SUBITEM51:
		pwnd->m_pOpPaneWnd->SwitchToView(VIEW_F1SUBITEM51);
		break;
	case VIEW_F1SUBITEM52:
		pwnd->m_pOpPaneWnd->SwitchToView(VIEW_F1SUBITEM52);
		break;*/
	case VIEW_F1SUBITEM6:
		pwnd->m_pOpPaneWnd->SwitchToView(VIEW_F1SUBITEM6);
		//	pwnd->m_pOpPaneWnd->m_pF1SubItem2View->icopy =1;
		break;
		
		
	}
	*pResult = 0;
}

void CProgView::OnSelchangedTreef2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	HTREEITEM hItem ;
	DWORD itemdata;
	if(RefreshTreeState == true)
	{
		return;
	}
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	hItem = m_TreeF2.GetSelectedItem();
	itemdata= m_TreeF2.GetItemData(hItem);
	m_TreeF2.Select(hItem,TVGN_DROPHILITE);//使选择的菜单项显示为选择状态
	switch(itemdata)
	{
	case VIEW_F2SUBITEM11:
		pwnd->m_pOpPaneWnd->SwitchToView(VIEW_F2SUBITEM11);
		break;
	case VIEW_F2SUBITEM12:
		pwnd->m_pOpPaneWnd->SwitchToView(VIEW_F2SUBITEM12);
		break;
/*	case VIEW_F2SUBITEM13:
		pwnd->m_pOpPaneWnd->SwitchToView(VIEW_F2SUBITEM13);
		break;
	case VIEW_F2SUBITEM14:
		pwnd->m_pOpPaneWnd->SwitchToView(VIEW_F2SUBITEM14);
		break;
	case VIEW_F2SUBITEM21:
		pwnd->m_pOpPaneWnd->SwitchToView(VIEW_F2SUBITEM21);
		break;
	case VIEW_F2SUBITEM22:
		pwnd->m_pOpPaneWnd->SwitchToView(VIEW_F2SUBITEM22);
		break;
	case VIEW_F2SUBITEM23:
		pwnd->m_pOpPaneWnd->SwitchToView(VIEW_F2SUBITEM23);
		break;
	case VIEW_F2SUBITEM24:
		pwnd->m_pOpPaneWnd->SwitchToView(VIEW_F2SUBITEM24);
		break;
		
	*/	
	}
	*pResult = 0;
}

void CProgView::OnSelchangedTreef3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	HTREEITEM hItem ;
	DWORD itemdata;
	if(RefreshTreeState == true)
	{
		return;
	}
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	hItem = m_TreeF3.GetSelectedItem();
	itemdata= m_TreeF3.GetItemData(hItem);
	m_TreeF3.Select(hItem,TVGN_DROPHILITE);//使选择的菜单项显示为选择状态
	switch(itemdata)
	{
	case VIEW_F3SUBITEM1:
		pwnd->m_pOpPaneWnd->SwitchToView(VIEW_F3SUBITEM1);
		break;
	}
	*pResult = 0;
}

void CProgView::OnSelchangedTreef4(NMHDR* pNMHDR, LRESULT* pResult) 
{

}

void CProgView::OnSelchangedTreef5(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	HTREEITEM hItem ;
	DWORD itemdata;
	//	bool switchflag=TRUE;
	if(RefreshTreeState == true)
	{
		return;
	}
	
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	hItem = m_TreeF5.GetSelectedItem();
	itemdata= m_TreeF5.GetItemData(hItem);
	m_TreeF5.Select(hItem,TVGN_DROPHILITE);//使选择的菜单项显示为选择状态
	pwnd->m_pOpPaneWnd->SwitchToView(itemdata);
	*pResult = 0;
}

void CProgView::OnSelchangedTreef6(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	HTREEITEM hItem ;
	DWORD itemdata;
	if(RefreshTreeState == true)
	{
		return;
	}
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	hItem = m_TreeF6.GetSelectedItem();
	itemdata= m_TreeF6.GetItemData(hItem);
	m_TreeF6.Select(hItem,TVGN_DROPHILITE);//使选择的菜单项显示为选择状态
	pwnd->m_pOpPaneWnd->SwitchToView(itemdata);
	*pResult = 0;
}

void CProgView::OnSelchangedTreef7(NMHDR* pNMHDR, LRESULT* pResult) 
{
	
}

void CProgView::OnSelchangedTreef8(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	HTREEITEM hItem ;
	DWORD itemdata;
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	hItem = m_TreeF8.GetSelectedItem();
	itemdata= m_TreeF8.GetItemData(hItem);
	if(RefreshTreeState == true)
	{
		return;
	}
	m_TreeF8.Select(hItem,TVGN_DROPHILITE);//使选择的菜单项显示为选择状态
	switch(itemdata)
	{
	case VIEW_F8SUBITEM1:
		pwnd->m_pOpPaneWnd->SwitchToView(VIEW_F8SUBITEM1);
		break;
	case VIEW_F8SUBITEM2:
		pwnd->m_pOpPaneWnd->SwitchToView(VIEW_F8SUBITEM2);
		break;
	case VIEW_F8SUBITEM3:
		pwnd->m_pOpPaneWnd->SwitchToView(VIEW_F8SUBITEM3);
		break;
	case VIEW_F8SUBITEM4:
		pwnd->m_pOpPaneWnd->SwitchToView(VIEW_F8SUBITEM4);
		break;
	case VIEW_F8SUBITEM5:
		pwnd->m_pOpPaneWnd->SwitchToView(VIEW_F8SUBITEM5);
		break;
/*	case VIEW_F8SUBITEM6:
		pwnd->m_pOpPaneWnd->SwitchToView(VIEW_F8SUBITEM6);
		TRACE("VIEW_F8SUBITEM6=%d",VIEW_F8SUBITEM6);
		break;
	case VIEW_F8SUBITEM7:
		pwnd->m_pOpPaneWnd->SwitchToView(VIEW_F8SUBITEM7);
        TRACE("VIEW_F8SUBITEM7=%d",VIEW_F8SUBITEM7);
		break;
	case VIEW_F8SUBITEM8:
		pwnd->m_pOpPaneWnd->SwitchToView(VIEW_F8SUBITEM8);
		break;
	case VIEW_F8SUBITEM9:
		pwnd->m_pOpPaneWnd->SwitchToView(VIEW_F8SUBITEM9);
		break;	
	*/		
	}
	*pResult = 0;
}




//void CProgView::HighLightFnButton(int num)//num=4单独处理
//{
//	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
//	switch(num)
//	{
//	case 1:
//		m_F1button->SetBitmap(m_F1button->Up);//此处为F1按下（位图按钮显示蓝色背景）
//		//注：由于初始化的关系，F1和其余按钮Up，Down所对应的背景颜色正好相反
//		//F1 Up位图按钮背景色：蓝色；   F1 Down位图按钮背景色：灰色
//		//F2-9 Up位图按钮背景色：灰色； F2-9 Down位图按钮背景色：蓝色
//		m_F2button->SetBitmap(m_F2button->Up);
//		m_F3button->SetBitmap(m_F3button->Up);
//		m_F4button->SetBitmap(m_F4button->Up);
//		m_F5button->SetBitmap(m_F5button->Up);
//		m_F6button->SetBitmap(m_F6button->Up);
//		m_F7button->SetBitmap(m_F7button->Up);
//		m_F8button->SetBitmap(m_F8button->Up);
//		break;
//	case 2:
//		m_F1button->SetBitmap(m_F1button->Down);//此处为F1弹起（位图按钮显示灰色背景）
//		m_F2button->SetBitmap(m_F2button->Down);
//		m_F3button->SetBitmap(m_F3button->Up);
//		m_F4button->SetBitmap(m_F4button->Up);
//		m_F5button->SetBitmap(m_F5button->Up);
//		m_F6button->SetBitmap(m_F6button->Up);
//		m_F7button->SetBitmap(m_F7button->Up);
//		m_F8button->SetBitmap(m_F8button->Up);
//		break;
//	case 3:m_F1button->SetBitmap(m_F1button->Down);
//		m_F2button->SetBitmap(m_F2button->Up);
//		m_F3button->SetBitmap(m_F3button->Down);
//		m_F4button->SetBitmap(m_F4button->Up);
//		m_F5button->SetBitmap(m_F5button->Up);
//		m_F6button->SetBitmap(m_F6button->Up);
//		m_F7button->SetBitmap(m_F7button->Up);
//		m_F8button->SetBitmap(m_F8button->Up);
//		break;
//	case 4:m_F1button->SetBitmap(m_F1button->Down);
//		m_F2button->SetBitmap(m_F2button->Up);
//		m_F3button->SetBitmap(m_F3button->Up);
//		m_F4button->SetBitmap(m_F4button->Down);
//		m_F5button->SetBitmap(m_F5button->Up);
//		m_F6button->SetBitmap(m_F6button->Up);
//		m_F7button->SetBitmap(m_F7button->Up);
//		m_F8button->SetBitmap(m_F8button->Up);
//		break;
//	case 5:	
//		m_F1button->SetBitmap(m_F1button->Down);
//		m_F2button->SetBitmap(m_F2button->Up);
//		m_F3button->SetBitmap(m_F3button->Up);
//		m_F4button->SetBitmap(m_F4button->Up);
//		m_F5button->SetBitmap(m_F5button->Down);
//		m_F6button->SetBitmap(m_F6button->Up);
//		m_F7button->SetBitmap(m_F7button->Up);
//		m_F8button->SetBitmap(m_F8button->Up);
//		break;
//	case 6:
//		m_F1button->SetBitmap(m_F1button->Down);
//		m_F2button->SetBitmap(m_F2button->Up);
//		m_F3button->SetBitmap(m_F3button->Up);
//		m_F4button->SetBitmap(m_F4button->Up);
//		m_F5button->SetBitmap(m_F5button->Up);
//		m_F6button->SetBitmap(m_F6button->Down);
//		m_F7button->SetBitmap(m_F7button->Up);
//		m_F8button->SetBitmap(m_F8button->Up);
//		break;
//	case 7:		
//		m_F1button->SetBitmap(m_F1button->Down);
//		m_F2button->SetBitmap(m_F2button->Up);
//		m_F3button->SetBitmap(m_F3button->Up);
//		m_F4button->SetBitmap(m_F4button->Up);
//		m_F5button->SetBitmap(m_F5button->Up);
//		m_F6button->SetBitmap(m_F6button->Up);
//		m_F7button->SetBitmap(m_F7button->Down);
//		m_F8button->SetBitmap(m_F8button->Up);
//		break;
//	case 8:
//		m_F1button->SetBitmap(m_F1button->Down);
//		m_F2button->SetBitmap(m_F2button->Up);
//		m_F3button->SetBitmap(m_F3button->Up);
//		m_F4button->SetBitmap(m_F4button->Up);
//		m_F5button->SetBitmap(m_F5button->Up);
//		m_F6button->SetBitmap(m_F6button->Up);
//		m_F7button->SetBitmap(m_F7button->Up);
//		m_F8button->SetBitmap(m_F8button->Down);
//		break;
//	default:
//		break;
//	}
//}


void CProgView::HighLightFnButton(int num)
{
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	switch(num)
	{
	case 1:
		m_F1button->SetBitmap(m_F1button->Up);//此处为F1按下（位图按钮显示蓝色背景）
		//注：由于初始化的关系，F1和其余按钮Up，Down所对应的背景颜色正好相反
		//F1 Up位图按钮背景色：蓝色；   F1 Down位图按钮背景色：灰色
		//F2-9 Up位图按钮背景色：灰色； F2-9 Down位图按钮背景色：蓝色
		m_F2button->SetBitmap(m_F2button->Up);
		m_F3button->SetBitmap(m_F3button->Up);
		m_F4button->SetBitmap(m_F4button->Up);
		m_F5button->SetBitmap(m_F5button->Up);
		m_F6button->SetBitmap(m_F6button->Up);
		m_F7button->SetBitmap(m_F7button->Up);
		m_F8button->SetBitmap(m_F8button->Up);
		break;
	case 2:
		m_F1button->SetBitmap(m_F1button->Down);//此处为F1弹起（位图按钮显示灰色背景）
		m_F2button->SetBitmap(m_F2button->Down);
		m_F3button->SetBitmap(m_F3button->Up);
		m_F4button->SetBitmap(m_F4button->Up);
		m_F5button->SetBitmap(m_F5button->Up);
		m_F6button->SetBitmap(m_F6button->Up);
		m_F7button->SetBitmap(m_F7button->Up);
		m_F8button->SetBitmap(m_F8button->Up);
		break;
	case 3:
		m_F1button->SetBitmap(m_F1button->Down);
		m_F2button->SetBitmap(m_F2button->Up);
		m_F3button->SetBitmap(m_F3button->Down);
		m_F4button->SetBitmap(m_F4button->Up);
		m_F5button->SetBitmap(m_F5button->Up);
		m_F6button->SetBitmap(m_F6button->Up);
		m_F7button->SetBitmap(m_F7button->Up);
		m_F8button->SetBitmap(m_F8button->Up);
		break;
	case 4:
		m_F1button->SetBitmap(m_F1button->Down);
		m_F2button->SetBitmap(m_F2button->Up);
		m_F3button->SetBitmap(m_F3button->Up);
		m_F4button->SetBitmap(m_F4button->Down);
		m_F5button->SetBitmap(m_F5button->Up);
		m_F6button->SetBitmap(m_F6button->Up);
		m_F7button->SetBitmap(m_F7button->Up);
		m_F8button->SetBitmap(m_F8button->Up);
		break;
	case 5:	
		m_F1button->SetBitmap(m_F1button->Down);
		m_F2button->SetBitmap(m_F2button->Up);
		m_F3button->SetBitmap(m_F3button->Up);
		m_F4button->SetBitmap(m_F4button->Up);
		m_F5button->SetBitmap(m_F5button->Down);
		m_F6button->SetBitmap(m_F6button->Up);
		m_F7button->SetBitmap(m_F7button->Up);
		m_F8button->SetBitmap(m_F8button->Up);
		break;
	case 6:
		m_F1button->SetBitmap(m_F1button->Down);
		m_F2button->SetBitmap(m_F2button->Up);
		m_F3button->SetBitmap(m_F3button->Up);
		m_F4button->SetBitmap(m_F4button->Up);
		m_F5button->SetBitmap(m_F5button->Up);
		m_F6button->SetBitmap(m_F6button->Down);
		m_F7button->SetBitmap(m_F7button->Up);
		m_F8button->SetBitmap(m_F8button->Up);
		break;
	case 7:		
		m_F1button->SetBitmap(m_F1button->Down);
		m_F2button->SetBitmap(m_F2button->Up);
		m_F3button->SetBitmap(m_F3button->Up);
		m_F4button->SetBitmap(m_F4button->Up);
		m_F5button->SetBitmap(m_F5button->Up);
		m_F6button->SetBitmap(m_F6button->Up);
		m_F7button->SetBitmap(m_F7button->Down);
		m_F8button->SetBitmap(m_F8button->Up);
		break;
	case 8:
		m_F1button->SetBitmap(m_F1button->Down);
		m_F2button->SetBitmap(m_F2button->Up);
		m_F3button->SetBitmap(m_F3button->Up);
		m_F4button->SetBitmap(m_F4button->Up);
		m_F5button->SetBitmap(m_F5button->Up);
		m_F6button->SetBitmap(m_F6button->Up);
		m_F7button->SetBitmap(m_F7button->Up);
		m_F8button->SetBitmap(m_F8button->Down);
		break;
	default:
		break;
	}
}

UINT CNCMOVE2(LPVOID pParam)
{
	CMainFrame * pwnd=(CMainFrame *)pParam;	
	pwnd->m_cnccontrol.XYMove(SW_length,0,"REL");
	return TRUE;
}