
// AOID.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "AOID.h"
#include "MainFrm.h"

#include "AOIDDoc.h"
#include "AOIDView.h"
#include <initguid.h>
#include "AOID_i.c"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAOIDApp


class CAOIDModule :
	public ATL::CAtlMfcModule
{
public:
	DECLARE_LIBID(LIBID_AOIDLib);
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_AOID, "{96BCE78A-4474-4D78-93DD-4B659B18D630}");};

CAOIDModule _AtlModule;

BEGIN_MESSAGE_MAP(CAOIDApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CAOIDApp::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()


// CAOIDApp 构造

CAOIDApp::CAOIDApp()
{
	m_bHiColorIcons = TRUE;

	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("AOID.AppID.NoVersion"));

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CAOIDApp 对象

CAOIDApp theApp;


// CAOIDApp 初始化

BOOL CAOIDApp::InitInstance()
{
	CWinAppEx::InitInstance();


	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// 使用 RichEdit 控件需要  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// 注册应用程序的文档模板。文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CAOIDDoc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CAOIDView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// 分析标准 shell 命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	#if !defined(_WIN32_WCE) || defined(_CE_DCOM)
	// 通过 CoRegisterClassObject() 注册类工厂。
	if (FAILED(_AtlModule.RegisterClassObjects(CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE)))
		return FALSE;
	#endif // !defined(_WIN32_WCE) || defined(_CE_DCOM)
	// 应用程序是用 /Embedding 或 /Automation 开关启动的。
	// 将应用程序作为自动化服务器运行。
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// 不显示主窗口
		return TRUE;
	}
	// 应用程序是用 /Unregserver 或 /Unregister 开关启动的。
	if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppUnregister)
	{
		_AtlModule.UpdateRegistryAppId(FALSE);
		_AtlModule.UnregisterServer(TRUE);
		return FALSE;
	}
	// 应用程序是用 /Register 或 /Regserver 开关启动的。
	if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppRegister)
	{
		_AtlModule.UpdateRegistryAppId(TRUE);
		_AtlModule.RegisterServer(TRUE);
		return FALSE;
	}



	// 调度在命令行中指定的命令。如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	m_pMainWnd->SetWindowText(_T("AOID"));//在主窗口显示的程序名
	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	
	m_pMainWnd->ShowWindow(SW_SHOW);//SW_SHOWMAXIMIZED);显示应用程序框架窗口
	m_pMainWnd->UpdateWindow();

	//****
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	
	pwnd->m_pOpPaneWnd->SwitchToView(VIEW_F8SUBITEM1);//主界面为工作状态界面
	/*pwnd->m_pMenuPaneWnd->m_pProgView->OnF8();
	pwnd->m_pMenuPaneWnd->m_pProgView->m_TreeF8.Select(pwnd->m_pMenuPaneWnd->m_pProgView->hF8SubItem1,TVGN_DROPHILITE);//使选择的菜单项显示为选择状态
	*/
	// 仅当具有后缀时才调用 DragAcceptFiles
	//  在 SDI 应用程序中，这应在 ProcessShellCommand 之后发生
	return TRUE;
}

int CAOIDApp::ExitInstance()
{
#if !defined(_WIN32_WCE) || defined(_CE_DCOM)
	_AtlModule.RevokeClassObjects();
#endif
	//TODO: 处理可能已添加的附加资源
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CAOIDApp 消息处理程序


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CAOIDApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CAOIDApp 自定义加载/保存方法

void CAOIDApp::PreLoadState()
{
	//BOOL bNameValid;
	//CString strName;
	//bNameValid = strName.LoadString(IDS_EDIT_MENU);
	//ASSERT(bNameValid);
//	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CAOIDApp::LoadCustomState()
{
}

void CAOIDApp::SaveCustomState()
{
}

// CAOIDApp 消息处理程序



