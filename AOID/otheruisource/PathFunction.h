// PathFunction.h: interface for the CPathFunction class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PATHFUNCTION_H__B22263BF_F26C_4A79_84C4_D373D20A7413__INCLUDED_)
#define AFX_PATHFUNCTION_H__B22263BF_F26C_4A79_84C4_D373D20A7413__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPathFunction  
{
public:
	bool IsSameFiletype(CString filename,CString filetype);
	CPathFunction();
	virtual ~CPathFunction();
	char GetLastChar(CString str);
	bool IsAtpFile(CString filename);
	bool IsDrlFile(CString filename);
	bool IsSsuFile(CString filename);
	bool IsDiaFile(CString filename);
	bool FileIsDirectory(CString path);
	void TraverseFolder(CString path,CListCtrl *filenamectrl,CString filetype="*.*");
	CString GetLastpath(CString path);
	int GetIconIndex(LPCTSTR lpszPath, BOOL bIsDir, BOOL bSelected);

};

#endif // !defined(AFX_PATHFUNCTION_H__B22263BF_F26C_4A79_84C4_D373D20A7413__INCLUDED_)
