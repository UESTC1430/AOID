// PathFunction.cpp: implementation of the CPathFunction class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AOID.h"
#include "PathFunction.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPathFunction::CPathFunction()
{

}

CPathFunction::~CPathFunction()
{

}


CString CPathFunction::GetLastpath(CString path)
{
	CString newpath;
	int n=path.GetLength();
	while(path.GetAt(n-1)!='\\')
	{
        n-=1;
	}
	newpath=path.Left(n-1);
	return newpath;
}

void CPathFunction::TraverseFolder(CString path,CListCtrl *filenamectrl,CString filetype)//���� path�µ��ļ�������ʾ
{
	CMainFrame *pwnd=(CMainFrame*)AfxGetMainWnd();
	CFileFind finder;
	CString file;
	int j=0;
	if(!PathFileExists(path))
	{
		TRACE("·��������\n");
		return;
	}
	if(GetLastChar(path)==':')//����̷�   �˴����ļ������һ���ַ�Ϊ������Ҳ��Ӱ��
	{
		path +="\\*.*";
	}
		if(GetLastChar(path)=='\\')//���OnInitialUpadate��������ʱ����ʱ�̷���'\'
	{
		path +="*.*";
	}
	BOOL bWorking = finder.FindFile(path);//���Ҵ�·���Ƿ����
	int n =GetLastError();
    filenamectrl->DeleteAllItems();
	if(!bWorking)//·�������ڣ��򷵻�
		return;
	if(GetLastChar(path)!='*')//����ʱ·�������"\\*.*"���������   ����̷�
	{
		path +="\\*.*";//·����չΪ��һ��·��
	}
	 bWorking = finder.FindFile(path);//�����¼�·��
//*******���´��빦�ܣ���������ǰ·���µ��ļ��в���ʾ******1
	while (bWorking)
	{
		bWorking = finder.FindNextFile();//���ҵ���·�����Ƿ��������ļ���whileѭ������
		if(finder.IsHidden())//����ʾ�����ļ�
			continue;
		file = finder.GetFileName();
		if (finder.IsDots())
		{
			if(file==".")//����ʾ .�ļ�
				continue;
		}	
		if (finder.IsDirectory())
		{
			filenamectrl->InsertItem(j,file,GetIconIndex(file,true,false));//��ǰѡ�����ļ��У���ʾ�ļ���ͼ��
			j++;
		}	
	}
 
   /* if( filenamectrl->GetSafeHwnd()==pwnd->m_pOpPaneWnd->m_pF2SubItem21View->m_outfilenamelist.GetSafeHwnd()||
		filenamectrl->GetSafeHwnd()==pwnd->m_pOpPaneWnd->m_pF2SubItem22View->m_listfilename.GetSafeHwnd()||
		filenamectrl->GetSafeHwnd()==pwnd->m_pOpPaneWnd->m_pF2SubItem23View->m_listfilename.GetSafeHwnd()||
		filenamectrl->GetSafeHwnd()==pwnd->m_pOpPaneWnd->m_pF2SubItem24View->m_listfilename.GetSafeHwnd()  )
          //�����򡢸�����ATP��ֱ��������ͼ ����ʾ�ļ�����ִ�е�2�Ρ�
		return;*/
//*******���´��빦�ܣ���������ǰ·���µ��ļ�����ʾ******2   1.2.���δ��������ǽ��ļ��������ļ���ʾ���б��� 	
		bWorking = finder.FindFile(path);//�����¼�·��/�ļ��Ƿ����
	while (bWorking)
	{
		bWorking = finder.FindNextFile();//���ҵ���·�����Ƿ��������ļ���whileѭ������
		if(finder.IsHidden())//����ʾ�����ļ�
			continue;
		file = finder.GetFileName();
		if (finder.IsDots())
		{
			if(file==".")//����ʾ .�ļ�
				continue;
		}
		
		if (!finder.IsDirectory())
		{
			if(!strcmp("*.*",filetype))//ѡ����ʾȫ���ļ�ʱ��ֱ����listcotrl��ʾ
			{
				filenamectrl->InsertItem(j,file,GetIconIndex(file,false,false));//��ǰѡ�����ļ�����ʾ�ļ�ͼ��
				j++;
			}
			else
			{
				if(IsSameFiletype(file,filetype))//ѡ����ʾfiletype���͵��ļ�ʱ���Ƚ��ļ�����֮������listcotrl��ʾ
				{
					filenamectrl->InsertItem(j,file,GetIconIndex(file,false,false));//��ǰѡ�����ļ�����ʾ�ļ�ͼ��
					j++;
				}
			}
		}
	}	
	finder.Close();		
}

bool CPathFunction::FileIsDirectory(CString path)//
{
	CFileFind finder;
	CString file;
	BOOL bWorking = finder.FindFile(path);
	if(bWorking)
	{
		finder.FindNextFile();
		if (finder.IsDirectory())
		{
			return true;
		}
	}
	return false;
}

bool CPathFunction::IsAtpFile(CString filename)//�ж��Ƿ�Ϊ.atp/.ATP�ļ�
{
	int iresult = filename.Find(".atp");
	if(iresult>0||iresult==0)
	{
		return true;
	}
	iresult = filename.Find(".ATP");
	if(iresult>0||iresult==0)
	{
		return true;
	}
	return false;
}

bool CPathFunction::IsDrlFile(CString filename)//�ж��Ƿ�Ϊ.drl/.DRL�ļ�
{
	int iresult = filename.Find(".drl");
	if(iresult>0||iresult==0)
	{
		return true;
	}
	iresult = filename.Find(".DRL");
	if(iresult>0||iresult==0)
	{
		return true;
	}
	return false;
}

bool CPathFunction::IsSsuFile(CString filename)//�ж��Ƿ�Ϊ.ssu/.SSU�ļ�
{
	int iresult = filename.Find(".ssu");
	if(iresult>0||iresult==0)
	{
		return true;
	}
	iresult = filename.Find(".SSU");
	if(iresult>0||iresult==0)
	{
		return true;
	}
	return false;
}

bool CPathFunction::IsDiaFile(CString filename)//�ж��Ƿ�Ϊ.dia/.DIA�ļ�
{
	int iresult = filename.Find(".dia");
	if(iresult>0||iresult==0)
	{
		return true;
	}
	iresult = filename.Find(".DIA");
	if(iresult>0||iresult==0)
	{
		return true;
	}
	return false;
}

char CPathFunction::GetLastChar(CString str)//��ȡ�ַ������һ���ַ�
{
	int ilong;//str����
	char lastchar;//���һ���ַ�
	ilong=str.GetLength();
    lastchar =str.GetAt(ilong-1);
	return lastchar;
}

int CPathFunction::GetIconIndex(LPCTSTR lpszPath, BOOL bIsDir, BOOL bSelected)
{
	SHFILEINFO sfi;
	memset(&sfi, 0, sizeof(sfi));
	if(bIsDir)
	{
		SHGetFileInfo(lpszPath,FILE_ATTRIBUTE_DIRECTORY,&sfi,sizeof(sfi),SHGFI_SMALLICON|SHGFI_SYSICONINDEX|SHGFI_USEFILEATTRIBUTES|(bSelected ? SHGFI_OPENICON : 0));
		return sfi.iIcon;
	}
	else
	{
		SHGetFileInfo(lpszPath,FILE_ATTRIBUTE_NORMAL,&sfi,sizeof(sfi),SHGFI_SMALLICON|SHGFI_SYSICONINDEX|SHGFI_USEFILEATTRIBUTES|(bSelected ? SHGFI_OPENICON : 0));
		return sfi.iIcon;
	}
	return -1;
}

bool CPathFunction::IsSameFiletype(CString filename, CString filetype)
{
	int filetypelen;//��ʾ�ļ����͵��ַ������ȣ���".cpp"����Ϊ4
	CString LastnstrOfFilename="";//�ļ�����nλ�ַ���
	CString LastnstrOfFiletype="";//�ļ����ͺ�nλ�ַ��� ȥ��"*",��"*.atp",����Ϊ".atp"
	filetypelen=filetype.GetLength();
	LastnstrOfFilename=filename.Right(filetypelen-1);
	LastnstrOfFiletype=filetype.Right(filetypelen-1);
	if(!stricmp(LastnstrOfFilename,LastnstrOfFiletype))//�Ƚ��ļ�����nλ�Ƿ����ļ����ͺ�nλ��ͬ �����ִ�Сд
		return true;
	return false;
				
}
