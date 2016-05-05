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

void CPathFunction::TraverseFolder(CString path,CListCtrl *filenamectrl,CString filetype)//遍历 path下的文件，并显示
{
	CMainFrame *pwnd=(CMainFrame*)AfxGetMainWnd();
	CFileFind finder;
	CString file;
	int j=0;
	if(!PathFileExists(path))
	{
		TRACE("路径不存在\n");
		return;
	}
	if(GetLastChar(path)==':')//针对盘符   此处若文件名最后一个字符为“：”也不影响
	{
		path +="\\*.*";
	}
		if(GetLastChar(path)=='\\')//针对OnInitialUpadate（）调用时，此时盘符有'\'
	{
		path +="*.*";
	}
	BOOL bWorking = finder.FindFile(path);//查找此路径是否存在
	int n =GetLastError();
    filenamectrl->DeleteAllItems();
	if(!bWorking)//路径不存在，则返回
		return;
	if(GetLastChar(path)!='*')//若此时路径已添加"\\*.*"，则不再添加   针对盘符
	{
		path +="\\*.*";//路径扩展为下一级路径
	}
	 bWorking = finder.FindFile(path);//查找下级路径
//*******以下代码功能：将遍历当前路径下的文件夹并显示******1
	while (bWorking)
	{
		bWorking = finder.FindNextFile();//查找当级路径下是否还有其他文件，while循环条件
		if(finder.IsHidden())//不显示隐藏文件
			continue;
		file = finder.GetFileName();
		if (finder.IsDots())
		{
			if(file==".")//不显示 .文件
				continue;
		}	
		if (finder.IsDirectory())
		{
			filenamectrl->InsertItem(j,file,GetIconIndex(file,true,false));//当前选项是文件夹，显示文件夹图标
			j++;
		}	
	}
 
   /* if( filenamectrl->GetSafeHwnd()==pwnd->m_pOpPaneWnd->m_pF2SubItem21View->m_outfilenamelist.GetSafeHwnd()||
		filenamectrl->GetSafeHwnd()==pwnd->m_pOpPaneWnd->m_pF2SubItem22View->m_listfilename.GetSafeHwnd()||
		filenamectrl->GetSafeHwnd()==pwnd->m_pOpPaneWnd->m_pF2SubItem23View->m_listfilename.GetSafeHwnd()||
		filenamectrl->GetSafeHwnd()==pwnd->m_pOpPaneWnd->m_pF2SubItem24View->m_listfilename.GetSafeHwnd()  )
          //主程序、副程序、ATP、直径表导出视图 不显示文件，不执行第2段。
		return;*/
//*******以下代码功能：将遍历当前路径下的文件并显示******2   1.2.两段代码作用是将文件夹先于文件显示在列表中 	
		bWorking = finder.FindFile(path);//查找下级路径/文件是否存在
	while (bWorking)
	{
		bWorking = finder.FindNextFile();//查找当级路径下是否还有其他文件，while循环条件
		if(finder.IsHidden())//不显示隐藏文件
			continue;
		file = finder.GetFileName();
		if (finder.IsDots())
		{
			if(file==".")//不显示 .文件
				continue;
		}
		
		if (!finder.IsDirectory())
		{
			if(!strcmp("*.*",filetype))//选择显示全部文件时，直接在listcotrl显示
			{
				filenamectrl->InsertItem(j,file,GetIconIndex(file,false,false));//当前选项是文件，显示文件图标
				j++;
			}
			else
			{
				if(IsSameFiletype(file,filetype))//选择显示filetype类型的文件时，比较文件类型之后再在listcotrl显示
				{
					filenamectrl->InsertItem(j,file,GetIconIndex(file,false,false));//当前选项是文件，显示文件图标
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

bool CPathFunction::IsAtpFile(CString filename)//判断是否为.atp/.ATP文件
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

bool CPathFunction::IsDrlFile(CString filename)//判断是否为.drl/.DRL文件
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

bool CPathFunction::IsSsuFile(CString filename)//判断是否为.ssu/.SSU文件
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

bool CPathFunction::IsDiaFile(CString filename)//判断是否为.dia/.DIA文件
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

char CPathFunction::GetLastChar(CString str)//获取字符串最后一个字符
{
	int ilong;//str长度
	char lastchar;//最后一个字符
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
	int filetypelen;//表示文件类型的字符串长度，如".cpp"长度为4
	CString LastnstrOfFilename="";//文件名后n位字符串
	CString LastnstrOfFiletype="";//文件类型后n位字符串 去除"*",如"*.atp",保存为".atp"
	filetypelen=filetype.GetLength();
	LastnstrOfFilename=filename.Right(filetypelen-1);
	LastnstrOfFiletype=filetype.Right(filetypelen-1);
	if(!stricmp(LastnstrOfFilename,LastnstrOfFiletype))//比较文件名后n位是否与文件类型后n位相同 不区分大小写
		return true;
	return false;
				
}
