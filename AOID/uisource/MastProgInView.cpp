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

/********************************************************
Function: OnSelchangeCombodrive
Description: 磁盘选择列表框按键处理
Input:     
Output: 
Return: 
Others: 界面处理函数
* ********************************************************/
void CMastProgInView::OnSelchangeCombodrive()
{
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	CString drive;
	int isel;//选中盘符的索引号
	//根据新的磁盘更新对应的文件
	isel = m_diskdrive.GetCurSel();
	m_diskdrive.GetLBText(isel,drive); //获得当前的盘符
	this->m_pathstr=drive;
	//	pwnd->m_pOpPaneWnd->m_pF2SubItem21View->m_pathstr=drive;//设置主程序导出视图路径
	//	pwnd->m_pOpPaneWnd->m_pF2SubItem21View->m_diskdrive.SetCurSel(isel);//设置主程序导出视图磁盘选择
	this->UpdateData(false);
	pwnd->m_pathfuction->TraverseFolder(drive,&m_filenamelist,filetype);
	//	pwnd->m_pathfuction->TraverseFolder(drive,&(pwnd->m_pOpPaneWnd->m_pF2SubItem21View->m_outfilenamelist),filetype);
}

/********************************************************
Function: OnSelchangeComboFileType
Description: 
Input:     
Output: 
Return: 
Others: 界面处理函数
* ********************************************************/
void CMastProgInView::OnSelchangeComboFileType()
{
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	int num=m_filetype.GetCurSel();//combo box控件 被选中项
	m_filetype.GetLBText(num,filetype);
	pwnd->m_pathfuction->TraverseFolder(m_pathstr,&m_filenamelist,filetype);//m_pathstr 当前路径
	return;
}

/********************************************************
Function: OnDblclkListfilename
Description: 双击文件名事件处理
Input:     
Output: 
Return: 
Others: 界面处理函数
* ********************************************************/
void CMastProgInView::OnDblclkListfilename(NMHDR *pNMHDR, LRESULT *pResult)
{
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	CString file;
	CString newpathandname;
	int isel = (int)m_filenamelist.GetFirstSelectedItemPosition();//获取选中行的索引号
	TCHAR szBuf[1024];
	LVITEM lvi;
	lvi.iItem = isel-1;//当前选中行的索引号赋值给行号
	lvi.iSubItem = 0;
	lvi.mask = LVIF_TEXT;
	lvi.pszText = szBuf;
	lvi.cchTextMax = 1024;
	m_filenamelist.GetItem(&lvi);//获取当前选中行的信息 主要需要文件名
	file=lvi.pszText;//选中行的文件名
	pathandname=this->m_pathstr;
	if(file=="..")//返回上一级（..文件夹）
	{
		newpathandname=	pwnd->m_pathfuction->GetLastpath(pathandname);
		this->m_pathstr=newpathandname;
		this->UpdateData(false);
		pwnd->m_pathfuction->TraverseFolder(newpathandname,&m_filenamelist,filetype);
		return;
	}	
	if(pwnd->m_pathfuction->GetLastChar(pathandname)=='\\')
		pathandname = pathandname+file;
	else
		pathandname = pathandname+"\\"+file;
	if(pwnd->m_pathfuction->FileIsDirectory(pathandname))
	{
		//遍历文件，左对齐显示
		this->m_pathstr=pathandname;
		this->UpdateData(false);
		pwnd->m_pathfuction->TraverseFolder(pathandname,&m_filenamelist,filetype);
		return;
	}	
	if(	pwnd->m_pathfuction->IsDrlFile(file))//是.drl/.Drl文件
	{

		int filenum=m_mainprofilename.FindString(-1,file);
		if (filenum==LB_ERR)//当前选则的文件名是否已存在与下拉列表，若存在则显示，不存在则添加
		{
			m_mainprofilename.InsertString(filecount,file);
			m_mainprofilename.SetCurSel(filecount);
			filecount++;
		}
		else
			m_mainprofilename.SetCurSel(filenum);

		theApp.mastprog.SetImportFile(pathandname);
		theApp.mastprog.ImportExe(&m_filecontentstr);
		//更新显示
		//	pwnd->m_pOpPaneWnd->m_pF2SubItem21View->m_outfilecontentstr=m_filecontentstr;//导出界面
		UpdateData(false);
	}
	else
	{
		AfxMessageBox("文件格式不正确!");
	}
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


/********************************************************
Function: OnInport
Description: 导入按键处理函数
Input:     
Output: 
Return: 
Others: 界面处理函数
* ********************************************************/
void CMastProgInView::OnInport()
{
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	//MSGID msgid=DataInMastProg;
	//MessageProcess(msgid);
	if (this->m_filecontentstr.IsEmpty())
	{
		MSGID msgid=DataInMastProg;
		MsgStruct *node=(MsgStruct*)malloc(sizeof(MsgStruct));
		sprintf_s(node->message,"请选择要导入的主程序！");
		node->messagegid=msgid;
		node->next=NULL;
		pwnd->errormsgqueue->MessageInsert(node);
		free(node);
		return;
	}
    
//	msgid=DataInMastProg;
	MsgStruct *node=(MsgStruct*)malloc(sizeof(MsgStruct));
	sprintf_s(node->message,"导入主程序");
//	node->messagegid=msgid;
	node->next=NULL;
	pwnd->operatemsgqueue->MessageInsert(node);
//	pwnd->RecordDrillFile(configinfo.drillfileinfo.pathandfilename,false);


	//pwnd->Record("操作","导入主程序");//数据库记录
	/*MachineRecordStruct merchinerecord;
	merchinerecord.type = "操作";
	merchinerecord.record = "导入主程序";
	merchinerecord.operatorID = pwnd->userdatastruct.m_UserId;
	theApp.cncdatabase.AddMachineRecord(&merchinerecord);*/

	strcpy(pwnd->m_cnccontrol.Configstruct.FileInfo.cmastprogfilename,pathandname);//将路径和文件名保存到配置文件数据结构中
	//新导入文件，更改安全区域为最大区域
	pwnd->m_cnccontrol.InitModefyWorkLimit();
   
   //		dlg.DoModal();//2013.11.13临时关闭LG
   //-------------------------------------------------------------------------------
//0324文件解析	
    theApp.mastprog.ParseAnly(this->m_filecontentstr,pwnd->m_toolparastruct,pwnd->drillnote,&pwnd->specialpoints);
	//char *m_filecontentstr2=this->m_filecontentstr.GetBuffer(0);
	//theApp.mastprog.ProcessT(m_filecontentstr2,&(pwnd->m_toolparastruct));
  //  pwnd->m_cnccontrol.Configstruct.CurrentDrillInfo.currentwork_ver=theApp.mastprog.structdrill.m_DrillEnvPara.STRUCTHOLE_VER;//导入新生产程序后，工作坐标系将更新
	//-------------------------------------------------------------------------------
	if(pwnd->m_firstMessage)//每次导入的时候都要将字符串命令链表做清空
	{
		while(pwnd->m_firstMessage->pnextmessage)
		{
			pwnd->m_tempMessage=pwnd->m_firstMessage->pnextmessage;
			pwnd->m_firstMessage->pnextmessage=pwnd->m_tempMessage->pnextmessage;
			free(pwnd->m_tempMessage);
		}	
		free(pwnd->m_firstMessage);
		pwnd->m_firstMessage=NULL;//释放完占用的空间后将所有指针置空
		pwnd->m_tempMessage=NULL;
		pwnd->m_CurrentMessage=NULL;
		pwnd->m_PreviousMessage=NULL;
	}
	//-------------------------------------------------------------------------------
	int count=0;
//	if(NULL!=m_OriPosition)
	if(NULL!=theApp.mastprog.m_OriPosition)
	{
		//HolePosNode *temp=m_OriPosition;
		HolePosNode *temp;
		temp= (HolePosNode *)theApp.mastprog.m_OriPosition;
//		pwnd->m_pOpPaneWnd->m_pF3SubItem1View->m_toolinAtpFlag=pwnd->FindToolInAtp();//根据刀具直径与ATP中的刀具匹配,匹配失败在程序执行按钮处理
		/*if(pwnd->m_pOpPaneWnd->m_pF3SubItem1View->m_PfirstNoteinBitMap)//若不为空，则清空 （清除以前的位图信息链表）
			pwnd->m_pOpPaneWnd->m_pF3SubItem1View->DeleteBitMapDataLink(pwnd->m_pOpPaneWnd->m_pF3SubItem1View->m_PfirstNoteinBitMap);*/
		//-------------------------------------------------
		//以下部分是对打孔监视界面图形进行重绘
		/*if(theApp.mastprog.m_WorkPosition==NULL)
		{
			theApp.mastprog.m_WorkPosition=(HoleInfoNode *)malloc(sizeof(HolePosNode));//分配内存空间 用于存放复制的链表
		}*/
		///CopyHolePosNode(m_OriPosition,m_WorkPosition);//复制打孔文件链表
	//	theApp.mastprog.CreateAndCopyHolePosNode(theApp.mastprog.m_WorkPosition);//( HolePosNode *)theApp.mastprog.m_OriPosition,( HolePosNode *)theApp.mastprog.m_WorkPosition);//复制打孔文件链表
		////////////////////////////////////////
	
	 /*  pwnd->m_pOpPaneWnd->m_pF3SubItem1View->FVProcessBeforeDraw((HolePosNode *)theApp.mastprog.m_WorkPosition);
		pwnd->m_pOpPaneWnd->m_pF3SubItem1View->m_dcHole.FillSolidRect(0,0,DISPZONEWIDE,DISPZONEHEIGHT,RGB(255,255,255));//更新客户区 1. 黑色变白色 2.覆盖之前的图形*/
		//pwnd->m_pOpPaneWnd->m_pF3SubItem2View->m_dcHole.CreateCompatibleDC(GetDC());
	    //pwnd->m_pOpPaneWnd->m_pF3SubItem2View->m_dcHole.FillSolidRect(0,0,DISPZONEWIDE,DISPZONEHEIGHT,RGB(255,255,255));//更新客户区 1. 黑色变白色 2.覆盖之前的图形*/
	//	pwnd->m_pOpPaneWnd->m_pF3SubItem2View->InitDrawHoleBmp(( HolePosNode *)theApp.mastprog.m_WorkPosition);
		
		/*pwnd->BoundryFlag=pwnd->m_pOpPaneWnd->m_pF3SubItem1View->CompareBoundry(( HolePosNode *)theApp.mastprog.m_WorkPosition);
		if(pwnd->BoundryFlag==false)
		{
			MSGID msgid=BOUNDARY;
			MsgStruct *node=(MsgStruct*)malloc(sizeof(MsgStruct));
			sprintf(node->message,"生产程序超出边界！");
			node->messagegid=msgid;
			node->next=NULL;
			 pwnd->errormsgqueue->MessageInsert(node);
		}
		else
		{		
			MSGID msgid=DRILL;
			MsgStruct *node=(MsgStruct*)malloc(sizeof(MsgStruct));
			sprintf(node->message,"等待钻孔");
			node->messagegid=msgid;
			node->next=NULL;
            pwnd->operatemsgqueue->MessageInsert(node);

		}*/
		//pwnd->m_pInfoPaneWnd->m_pInfoView->SwitchFileName();//显示导入的文件名、格式
		//pwnd->m_pInfoPaneWnd->m_pInfoView->SwitchFV(pwnd->m_cnccontrol.Configstruct.CurrentDrillInfo.currentwork_ver);//主界面显示当前工作坐标系
		//pwnd->m_pInfoPaneWnd->m_pInfoView->SetFVValues_Origin(theApp.mastprog.m_WorkPosition->position.nXs,theApp.mastprog.m_WorkPosition->position.nYs);
		////////////////////////////////////////
		//ProcessMirro(structdrill.m_DrillEnvPara.STRUCTHOLE_VER,m_WorkPosition);	//用复制的孔位信息链表进行坐标变换操作，再用于显示
		//pwnd->m_pOpPaneWnd->m_pF3SubItem1View->m_dcHole.FillSolidRect(0,0,DISPZONEWIDE,DISPZONEHEIGHT,RGB(255,255,255));//更新客户区 1. 黑色变白色 2.覆盖之前的图形
		//pwnd->m_pOpPaneWnd->m_pF3SubItem2View->DrawHoleBmp(pwnd->codeboundary,m_WorkPosition,0,0);
		//////////////////////////////////////////////////
		
		//-------------------------------------------------
		//以下部分是每次导入时删除原来的执行程序窗口中的CListCtrl中所有行，并且将行号清零
	/*	pwnd->m_pOpPaneWnd->m_pF3SubItem1View->FlagNum=0;
		pwnd->m_pOpPaneWnd->m_pF3SubItem1View->m_index=0;
		for(int k=pwnd->m_pOpPaneWnd->m_pF3SubItem1View->m_ListFileContents.GetItemCount();k>=-1;k--)
			pwnd->m_pOpPaneWnd->m_pF3SubItem1View->m_ListFileContents.DeleteItem(k);
	}
	else
	{
		AfxMessageBox("打孔文件内容为空!");
	}
	pwnd->m_pOpPaneWnd->SwitchToView(VIEW_F3SUBITEM1);
	pwnd->m_pMenuPaneWnd->m_pProgView->OnF3();//F3按下状态
	pwnd->m_pOpPaneWnd->m_pF3SubItem1View->icopy =1;*/
	}

}
