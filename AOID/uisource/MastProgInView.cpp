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
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTFILENAME, &CMastProgInView::OnLvnItemchangedListfilename)
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


void CMastProgInView::OnSelchangeCombodrive()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMastProgInView::OnSelchangeComboFileType()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMastProgInView::OnDblclkListfilename(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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




void CMastProgInView::OnInport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMastProgInView::OnLvnItemchangedListfilename(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}
