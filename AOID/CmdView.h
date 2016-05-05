#pragma once
#include "afxwin.h"
#include"AOIDtype.h"

// CCmdView 对话框

class CCmdView : public CDialog
{
	DECLARE_DYNAMIC(CCmdView)

public:
	CCmdView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCmdView();

// 对话框数据
	enum { IDD = IDD_CMDVIEW };

	struct CmdPara CmdCode;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnButtonexe();
	afx_msg void OnButtoncancel();
	afx_msg void OnButtonhelp();
	CEdit m_CmdEdit;
	CString PreCmdText;
	CString NewCmdText;
	HWND mhwnd;
	virtual BOOL OnInitDialog();
};
