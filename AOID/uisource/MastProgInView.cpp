// MastProgInView.cpp : 实现文件
//

#include "stdafx.h"
#include "AOID.h"
#include "MastProgInView.h"
#include "mainfrm.h"
//#include "StyleFormat.h"
#include "FindOrgan.h"
#include "MessageQueue.h"


// CMastProgInView

IMPLEMENT_DYNCREATE(CMastProgInView, CFormView)

CMastProgInView::CMastProgInView()
	: CFormView(CMastProgInView::IDD)
{

	m_filecontentstr = _T("");
	m_pathstr = _T("");
	filetype = _T("");
	filecount = 0;
	pathandname = _T("");
}

CMastProgInView::~CMastProgInView()
{
}

void CMastProgInView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBODRIVE, m_diskdrive);
	DDX_Control(pDX, IDC_COMBOFILENAME, m_mainprofilename);
	DDX_Control(pDX, IDC_COMBOFILETYPE, m_filetype);
	DDX_Text(pDX, IDC_EDITFILECONTENT, m_filecontentstr);
	DDX_Control(pDX, IDC_LISTFILENAME, m_filenamelist);
	DDX_Text(pDX, IDC_STATICPATH, m_pathstr);
}

BEGIN_MESSAGE_MAP(CMastProgInView, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBODRIVE, &CMastProgInView::OnSelchangeCombodrive)
	ON_CBN_SELCHANGE(IDC_COMBOFILETYPE, &CMastProgInView::OnSelchangeComboFileType)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTFILENAME, &CMastProgInView::OnDblclkListfilename)
	ON_STN_CLICKED(IDC_INPORT, &CMastProgInView::OnInport)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTFILENAME, &CMastProgInView::OnLvnItemchangedListfilename)
END_MESSAGE_MAP()


// CMastProgInView 诊断

#ifdef _DEBUG
void CMastProgInView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMastProgInView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void CMastProgInView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	HIMAGELIST himlSmall;
	HIMAGELIST himlLarge;
	SHFILEINFO sfi;
	char cSysDir[MAX_PATH];//允许路径的最大长度  260 个字节
	CString strBuf;
	memset(cSysDir,0,MAX_PATH);
	GetWindowsDirectory(cSysDir,MAX_PATH);
	strBuf = cSysDir;
	himlSmall = (HIMAGELIST)SHGetFileInfo((LPCSTR)cSysDir,0,&sfi,sizeof(SHFILEINFO),SHGFI_SYSICONINDEX|SHGFI_SMALLICON);
	himlLarge = (HIMAGELIST)SHGetFileInfo((LPCSTR)cSysDir,0,&sfi,sizeof(SHFILEINFO),SHGFI_SYSICONINDEX|SHGFI_LARGEICON);
	if(himlSmall && himlLarge)
	{
		::SendMessage(m_filenamelist.m_hWnd,LVM_SETIMAGELIST,(WPARAM)LVSIL_SMALL,(LPARAM)himlSmall);
		::SendMessage(m_filenamelist.m_hWnd,LVM_SETIMAGELIST,(WPARAM)LVSIL_SMALL,(LPARAM)himlLarge);//LVSIL_NORMAL
	}
	
    m_filenamelist.InsertColumn(0, _T("文件名"), LVCFMT_LEFT, 200);//0：第0列，  LVCFMT_LEFT：左对齐， 200：列宽

	m_filetype.AddString("*.*");
	m_filetype.AddString("*.drl");
	m_filetype.AddString("*.rou");
	m_filetype.SetCurSel(0);
    m_filetype.GetLBText(0,filetype);
	//-------------------------------------------------------------------
	//弹出要求回远点的界面框
	/*	if(pwnd->bcnccomok)
	{
	CFindOrgan findorgan;
	findorgan.DoModal();
	}*/
    if(!pwnd->MacModeStatus)//MacModeStatus=0，机床为正常工作模式
	{
		//机床为正常工作模式
		CFindOrgan findorgan;
		findorgan.DoModal();
	}
	
	//添加驱动器
	int DSLength = GetLogicalDriveStrings(0,NULL);//获取所有驱动器字符串信息长度。
	char* DStr = new char[DSLength];//用获取的长度在堆区创建一个c风格的字符串数组
	GetLogicalDriveStrings(DSLength,(LPTSTR)DStr);//将字符串信息复制到堆区数组中,其中保存了当前盘符的信息。
	char *ptemp;
	int j=DSLength;
	int i;
	int iitem=0;
	ptemp = DStr;
	while(j)
	{
		i = strlen(ptemp);
		if(i!=0)
		{
			m_diskdrive.InsertString(iitem,ptemp);
			iitem++;
			ptemp +=i+1;
			j=j-i;
		}
		else
		{
			break;
		}
	}	 
	m_diskdrive.SetCurSel(0);
	delete DStr;
	DStr=NULL;
	CString temppath;//初始化路径 来源：1.环境暂存文件-钻孔文件路径+文件名 2.环境暂存文件-用户设置快捷路径  3.默认C盘根目录 1,2,3按先后顺序
    CString filename;
	CString drive;
	int index;
	temppath=pwnd->m_cnccontrol.Configstruct.FileInfo.cmastprogfilename;//从配置文件获取上一次导入的主程序的路径（此路径包括文件名）
	if (PathFileExists(temppath))
	{
		//钻孔文件路径合法，遍历此路径
		/********读取配置文件信息，并在导入主程序界面显示********************/
		index=temppath.ReverseFind('\\');//逆向查找字符'\'，目的是从保存的包含文件名的路径中去除文件名，用于显示并遍历路径
		m_pathstr=temppath.Left(index);
		filename=temppath.Right(temppath.GetLength()-index-1);
		if ( pwnd->m_pathfuction->IsDrlFile(filename) )
		{
			m_mainprofilename.InsertString(filecount,filename);	
			m_mainprofilename.SetCurSel(filecount);
			filecount++;
			//导入主程序//OpenDrlFile(temppath);
			theApp.mastprog.SetImportFile(temppath);
			theApp.mastprog.ImportExe(&m_filecontentstr);
			//更新显示
	//		pwnd->m_pOpPaneWnd->m_pF2SubItem21View->m_outfilecontentstr=m_filecontentstr;//导出界面
			UpdateData(false);
		}
	}
	else
	{
		//钻孔文件路径不合法,遍历主程序默认路径
		m_pathstr=pwnd->m_cnccontrol.Configstruct.FileInfo.cmastprogpath;	
	}
	pwnd->m_pathfuction->TraverseFolder(m_pathstr,&m_filenamelist,filetype);	

}

// CMastProgInView 消息处理程序


void CMastProgInView::OnSelchangeCombodrive()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMastProgInView::OnSelchangeComboFileType()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMastProgInView::OnDblclkListfilename(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CMastProgInView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	CMainFrame *pwnd=(CMainFrame *)AfxGetMainWnd();
	CString temppath;
	CString drive;
	if (bActivate)
	{
		if (this->m_filecontentstr.IsEmpty()
			&& (!pwnd->m_pOpPaneWnd->m_pF1SubItem4View->m_mastprogpath.IsEmpty()) ) //设置路径不为空且当前没有导入任何加工文件
		{
			temppath=pwnd->m_pOpPaneWnd->m_pF1SubItem4View->m_mastprogpath;
			if (PathFileExists(temppath))
			{
				//用户设置快捷路径合法，遍历此路径
				m_pathstr=temppath;
			}
			else
			{
				//用户设置快捷路径不合法，默认遍历C盘
				m_diskdrive.GetLBText(0,drive);
				m_pathstr=drive;
			}	
			pwnd->m_pathfuction->TraverseFolder(m_pathstr,&m_filenamelist,filetype);
		}
		UpdateData(false);
	}
	//	UpdateData(false);//文件预览 IDC_EDITFILECONTENT控件内容被修改时 需要更新显示
	CFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}




void CMastProgInView::OnInport()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMastProgInView::OnLvnItemchangedListfilename(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
