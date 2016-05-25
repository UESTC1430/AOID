// MastProgInView.cpp : ʵ���ļ�
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


// CMastProgInView ���

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
	char cSysDir[MAX_PATH];//����·������󳤶�  260 ���ֽ�
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
	
    m_filenamelist.InsertColumn(0, _T("�ļ���"), LVCFMT_LEFT, 200);//0����0�У�  LVCFMT_LEFT������룬 200���п�

	m_filetype.AddString("*.*");
	m_filetype.AddString("*.drl");
	m_filetype.AddString("*.rou");
	m_filetype.SetCurSel(0);
    m_filetype.GetLBText(0,filetype);
	//-------------------------------------------------------------------
	//����Ҫ���Զ��Ľ����
	/*	if(pwnd->bcnccomok)
	{
	CFindOrgan findorgan;
	findorgan.DoModal();
	}*/
    if(!pwnd->MacModeStatus)//MacModeStatus=0������Ϊ��������ģʽ
	{
		//����Ϊ��������ģʽ
		CFindOrgan findorgan;
		findorgan.DoModal();
	}
	
	//���������
	int DSLength = GetLogicalDriveStrings(0,NULL);//��ȡ�����������ַ�����Ϣ���ȡ�
	char* DStr = new char[DSLength];//�û�ȡ�ĳ����ڶ�������һ��c�����ַ�������
	GetLogicalDriveStrings(DSLength,(LPTSTR)DStr);//���ַ�����Ϣ���Ƶ�����������,���б����˵�ǰ�̷�����Ϣ��
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
	CString temppath;//��ʼ��·�� ��Դ��1.�����ݴ��ļ�-����ļ�·��+�ļ��� 2.�����ݴ��ļ�-�û����ÿ��·��  3.Ĭ��C�̸�Ŀ¼ 1,2,3���Ⱥ�˳��
    CString filename;
	CString drive;
	int index;
	temppath=pwnd->m_cnccontrol.Configstruct.FileInfo.cmastprogfilename;//�������ļ���ȡ��һ�ε�����������·������·�������ļ�����
	if (PathFileExists(temppath))
	{
		//����ļ�·���Ϸ���������·��
		/********��ȡ�����ļ���Ϣ�����ڵ��������������ʾ********************/
		index=temppath.ReverseFind('\\');//��������ַ�'\'��Ŀ���Ǵӱ���İ����ļ�����·����ȥ���ļ�����������ʾ������·��
		m_pathstr=temppath.Left(index);
		filename=temppath.Right(temppath.GetLength()-index-1);
		if ( pwnd->m_pathfuction->IsDrlFile(filename) )
		{
			m_mainprofilename.InsertString(filecount,filename);	
			m_mainprofilename.SetCurSel(filecount);
			filecount++;
			//����������//OpenDrlFile(temppath);
			theApp.mastprog.SetImportFile(temppath);
			theApp.mastprog.ImportExe(&m_filecontentstr);
			//������ʾ
	//		pwnd->m_pOpPaneWnd->m_pF2SubItem21View->m_outfilecontentstr=m_filecontentstr;//��������
			UpdateData(false);
		}
	}
	else
	{
		//����ļ�·�����Ϸ�,����������Ĭ��·��
		m_pathstr=pwnd->m_cnccontrol.Configstruct.FileInfo.cmastprogpath;	
	}
	pwnd->m_pathfuction->TraverseFolder(m_pathstr,&m_filenamelist,filetype);	

}

// CMastProgInView ��Ϣ�������

/********************************************************
Function: OnSelchangeCombodrive
Description: ����ѡ���б�򰴼�����
Input:     
Output: 
Return: 
Others: ���洦����
* ********************************************************/
void CMastProgInView::OnSelchangeCombodrive()
{
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	CString drive;
	int isel;//ѡ���̷���������
	//�����µĴ��̸��¶�Ӧ���ļ�
	isel = m_diskdrive.GetCurSel();
	m_diskdrive.GetLBText(isel,drive); //��õ�ǰ���̷�
	this->m_pathstr=drive;
	//	pwnd->m_pOpPaneWnd->m_pF2SubItem21View->m_pathstr=drive;//���������򵼳���ͼ·��
	//	pwnd->m_pOpPaneWnd->m_pF2SubItem21View->m_diskdrive.SetCurSel(isel);//���������򵼳���ͼ����ѡ��
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
Others: ���洦����
* ********************************************************/
void CMastProgInView::OnSelchangeComboFileType()
{
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	int num=m_filetype.GetCurSel();//combo box�ؼ� ��ѡ����
	m_filetype.GetLBText(num,filetype);
	pwnd->m_pathfuction->TraverseFolder(m_pathstr,&m_filenamelist,filetype);//m_pathstr ��ǰ·��
	return;
}

/********************************************************
Function: OnDblclkListfilename
Description: ˫���ļ����¼�����
Input:     
Output: 
Return: 
Others: ���洦����
* ********************************************************/
void CMastProgInView::OnDblclkListfilename(NMHDR *pNMHDR, LRESULT *pResult)
{
	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	CString file;
	CString newpathandname;
	int isel = (int)m_filenamelist.GetFirstSelectedItemPosition();//��ȡѡ���е�������
	TCHAR szBuf[1024];
	LVITEM lvi;
	lvi.iItem = isel-1;//��ǰѡ���е������Ÿ�ֵ���к�
	lvi.iSubItem = 0;
	lvi.mask = LVIF_TEXT;
	lvi.pszText = szBuf;
	lvi.cchTextMax = 1024;
	m_filenamelist.GetItem(&lvi);//��ȡ��ǰѡ���е���Ϣ ��Ҫ��Ҫ�ļ���
	file=lvi.pszText;//ѡ���е��ļ���
	pathandname=this->m_pathstr;
	if(file=="..")//������һ����..�ļ��У�
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
		//�����ļ����������ʾ
		this->m_pathstr=pathandname;
		this->UpdateData(false);
		pwnd->m_pathfuction->TraverseFolder(pathandname,&m_filenamelist,filetype);
		return;
	}	
	if(	pwnd->m_pathfuction->IsDrlFile(file))//��.drl/.Drl�ļ�
	{

		int filenum=m_mainprofilename.FindString(-1,file);
		if (filenum==LB_ERR)//��ǰѡ����ļ����Ƿ��Ѵ����������б�����������ʾ�������������
		{
			m_mainprofilename.InsertString(filecount,file);
			m_mainprofilename.SetCurSel(filecount);
			filecount++;
		}
		else
			m_mainprofilename.SetCurSel(filenum);

		theApp.mastprog.SetImportFile(pathandname);
		theApp.mastprog.ImportExe(&m_filecontentstr);
		//������ʾ
		//	pwnd->m_pOpPaneWnd->m_pF2SubItem21View->m_outfilecontentstr=m_filecontentstr;//��������
		UpdateData(false);
	}
	else
	{
		AfxMessageBox("�ļ���ʽ����ȷ!");
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
			&& (!pwnd->m_pOpPaneWnd->m_pF1SubItem4View->m_mastprogpath.IsEmpty()) ) //����·����Ϊ���ҵ�ǰû�е����κμӹ��ļ�
		{
			temppath=pwnd->m_pOpPaneWnd->m_pF1SubItem4View->m_mastprogpath;
			if (PathFileExists(temppath))
			{
				//�û����ÿ��·���Ϸ���������·��
				m_pathstr=temppath;
			}
			else
			{
				//�û����ÿ��·�����Ϸ���Ĭ�ϱ���C��
				m_diskdrive.GetLBText(0,drive);
				m_pathstr=drive;
			}	
			pwnd->m_pathfuction->TraverseFolder(m_pathstr,&m_filenamelist,filetype);
		}
		UpdateData(false);
	}
	//	UpdateData(false);//�ļ�Ԥ�� IDC_EDITFILECONTENT�ؼ����ݱ��޸�ʱ ��Ҫ������ʾ
	CFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}


/********************************************************
Function: OnInport
Description: ���밴��������
Input:     
Output: 
Return: 
Others: ���洦����
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
		sprintf_s(node->message,"��ѡ��Ҫ�����������");
		node->messagegid=msgid;
		node->next=NULL;
		pwnd->errormsgqueue->MessageInsert(node);
		free(node);
		return;
	}
    
//	msgid=DataInMastProg;
	MsgStruct *node=(MsgStruct*)malloc(sizeof(MsgStruct));
	sprintf_s(node->message,"����������");
//	node->messagegid=msgid;
	node->next=NULL;
	pwnd->operatemsgqueue->MessageInsert(node);
//	pwnd->RecordDrillFile(configinfo.drillfileinfo.pathandfilename,false);


	//pwnd->Record("����","����������");//���ݿ��¼
	/*MachineRecordStruct merchinerecord;
	merchinerecord.type = "����";
	merchinerecord.record = "����������";
	merchinerecord.operatorID = pwnd->userdatastruct.m_UserId;
	theApp.cncdatabase.AddMachineRecord(&merchinerecord);*/

	strcpy(pwnd->m_cnccontrol.Configstruct.FileInfo.cmastprogfilename,pathandname);//��·�����ļ������浽�����ļ����ݽṹ��
	//�µ����ļ������İ�ȫ����Ϊ�������
	pwnd->m_cnccontrol.InitModefyWorkLimit();
   
   //		dlg.DoModal();//2013.11.13��ʱ�ر�LG
   //-------------------------------------------------------------------------------
//0324�ļ�����	
    theApp.mastprog.ParseAnly(this->m_filecontentstr,pwnd->m_toolparastruct,pwnd->drillnote,&pwnd->specialpoints);
	//char *m_filecontentstr2=this->m_filecontentstr.GetBuffer(0);
	//theApp.mastprog.ProcessT(m_filecontentstr2,&(pwnd->m_toolparastruct));
  //  pwnd->m_cnccontrol.Configstruct.CurrentDrillInfo.currentwork_ver=theApp.mastprog.structdrill.m_DrillEnvPara.STRUCTHOLE_VER;//��������������󣬹�������ϵ������
	//-------------------------------------------------------------------------------
	if(pwnd->m_firstMessage)//ÿ�ε����ʱ��Ҫ���ַ����������������
	{
		while(pwnd->m_firstMessage->pnextmessage)
		{
			pwnd->m_tempMessage=pwnd->m_firstMessage->pnextmessage;
			pwnd->m_firstMessage->pnextmessage=pwnd->m_tempMessage->pnextmessage;
			free(pwnd->m_tempMessage);
		}	
		free(pwnd->m_firstMessage);
		pwnd->m_firstMessage=NULL;//�ͷ���ռ�õĿռ������ָ���ÿ�
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
//		pwnd->m_pOpPaneWnd->m_pF3SubItem1View->m_toolinAtpFlag=pwnd->FindToolInAtp();//���ݵ���ֱ����ATP�еĵ���ƥ��,ƥ��ʧ���ڳ���ִ�а�ť����
		/*if(pwnd->m_pOpPaneWnd->m_pF3SubItem1View->m_PfirstNoteinBitMap)//����Ϊ�գ������ �������ǰ��λͼ��Ϣ����
			pwnd->m_pOpPaneWnd->m_pF3SubItem1View->DeleteBitMapDataLink(pwnd->m_pOpPaneWnd->m_pF3SubItem1View->m_PfirstNoteinBitMap);*/
		//-------------------------------------------------
		//���²����ǶԴ�׼��ӽ���ͼ�ν����ػ�
		/*if(theApp.mastprog.m_WorkPosition==NULL)
		{
			theApp.mastprog.m_WorkPosition=(HoleInfoNode *)malloc(sizeof(HolePosNode));//�����ڴ�ռ� ���ڴ�Ÿ��Ƶ�����
		}*/
		///CopyHolePosNode(m_OriPosition,m_WorkPosition);//���ƴ���ļ�����
	//	theApp.mastprog.CreateAndCopyHolePosNode(theApp.mastprog.m_WorkPosition);//( HolePosNode *)theApp.mastprog.m_OriPosition,( HolePosNode *)theApp.mastprog.m_WorkPosition);//���ƴ���ļ�����
		////////////////////////////////////////
	
	 /*  pwnd->m_pOpPaneWnd->m_pF3SubItem1View->FVProcessBeforeDraw((HolePosNode *)theApp.mastprog.m_WorkPosition);
		pwnd->m_pOpPaneWnd->m_pF3SubItem1View->m_dcHole.FillSolidRect(0,0,DISPZONEWIDE,DISPZONEHEIGHT,RGB(255,255,255));//���¿ͻ��� 1. ��ɫ���ɫ 2.����֮ǰ��ͼ��*/
		//pwnd->m_pOpPaneWnd->m_pF3SubItem2View->m_dcHole.CreateCompatibleDC(GetDC());
	    //pwnd->m_pOpPaneWnd->m_pF3SubItem2View->m_dcHole.FillSolidRect(0,0,DISPZONEWIDE,DISPZONEHEIGHT,RGB(255,255,255));//���¿ͻ��� 1. ��ɫ���ɫ 2.����֮ǰ��ͼ��*/
	//	pwnd->m_pOpPaneWnd->m_pF3SubItem2View->InitDrawHoleBmp(( HolePosNode *)theApp.mastprog.m_WorkPosition);
		
		/*pwnd->BoundryFlag=pwnd->m_pOpPaneWnd->m_pF3SubItem1View->CompareBoundry(( HolePosNode *)theApp.mastprog.m_WorkPosition);
		if(pwnd->BoundryFlag==false)
		{
			MSGID msgid=BOUNDARY;
			MsgStruct *node=(MsgStruct*)malloc(sizeof(MsgStruct));
			sprintf(node->message,"�������򳬳��߽磡");
			node->messagegid=msgid;
			node->next=NULL;
			 pwnd->errormsgqueue->MessageInsert(node);
		}
		else
		{		
			MSGID msgid=DRILL;
			MsgStruct *node=(MsgStruct*)malloc(sizeof(MsgStruct));
			sprintf(node->message,"�ȴ����");
			node->messagegid=msgid;
			node->next=NULL;
            pwnd->operatemsgqueue->MessageInsert(node);

		}*/
		//pwnd->m_pInfoPaneWnd->m_pInfoView->SwitchFileName();//��ʾ������ļ�������ʽ
		//pwnd->m_pInfoPaneWnd->m_pInfoView->SwitchFV(pwnd->m_cnccontrol.Configstruct.CurrentDrillInfo.currentwork_ver);//��������ʾ��ǰ��������ϵ
		//pwnd->m_pInfoPaneWnd->m_pInfoView->SetFVValues_Origin(theApp.mastprog.m_WorkPosition->position.nXs,theApp.mastprog.m_WorkPosition->position.nYs);
		////////////////////////////////////////
		//ProcessMirro(structdrill.m_DrillEnvPara.STRUCTHOLE_VER,m_WorkPosition);	//�ø��ƵĿ�λ��Ϣ�����������任��������������ʾ
		//pwnd->m_pOpPaneWnd->m_pF3SubItem1View->m_dcHole.FillSolidRect(0,0,DISPZONEWIDE,DISPZONEHEIGHT,RGB(255,255,255));//���¿ͻ��� 1. ��ɫ���ɫ 2.����֮ǰ��ͼ��
		//pwnd->m_pOpPaneWnd->m_pF3SubItem2View->DrawHoleBmp(pwnd->codeboundary,m_WorkPosition,0,0);
		//////////////////////////////////////////////////
		
		//-------------------------------------------------
		//���²�����ÿ�ε���ʱɾ��ԭ����ִ�г��򴰿��е�CListCtrl�������У����ҽ��к�����
	/*	pwnd->m_pOpPaneWnd->m_pF3SubItem1View->FlagNum=0;
		pwnd->m_pOpPaneWnd->m_pF3SubItem1View->m_index=0;
		for(int k=pwnd->m_pOpPaneWnd->m_pF3SubItem1View->m_ListFileContents.GetItemCount();k>=-1;k--)
			pwnd->m_pOpPaneWnd->m_pF3SubItem1View->m_ListFileContents.DeleteItem(k);
	}
	else
	{
		AfxMessageBox("����ļ�����Ϊ��!");
	}
	pwnd->m_pOpPaneWnd->SwitchToView(VIEW_F3SUBITEM1);
	pwnd->m_pMenuPaneWnd->m_pProgView->OnF3();//F3����״̬
	pwnd->m_pOpPaneWnd->m_pF3SubItem1View->icopy =1;*/
	}

}
