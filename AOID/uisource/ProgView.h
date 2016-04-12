#if !defined(AFX_PROGVIEW_H__0585C657_C111_4089_A423_FDC681CD7A78__INCLUDED_)
#define AFX_PROGVIEW_H__0585C657_C111_4089_A423_FDC681CD7A78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProgView.h : header file
//
#include "resource.h"
#include "staticbutton.h"
#include "winpara.h"
//#include "label.h"

/////////////////////////////////////////////////////////////////////////////
// CProgView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CProgView : public CFormView
{
public:
	CProgView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CProgView)

// Form Data
public:
	//{{AFX_DATA(CProgView)
	enum { IDD = IDD_PROGVIEW };

	//}}AFX_DATA

// Attributes
public:

	CStaticButton * m_F1button;
	CStaticButton * m_F2button;
	CStaticButton * m_F3button;
	CStaticButton * m_F4button;
	CStaticButton * m_F5button;
	CStaticButton * m_F6button;
	CStaticButton * m_F7button;
	CStaticButton * m_F8button;


	bool F1State; //f1是否存在状态，0，不存在，不能操作，1，存在可以操作
	bool F2State;
	bool F3State;
	bool F4State;
	bool F5State;
	bool F6State;
	bool F7State;
	bool F8State;

	bool RefreshTreeState;//更新不同用户命令树状态，该状态不做视图切换，0，不在更新态，1，在更新态

	int fbtnnum;//fbtnnum=i表示当前在Fi菜单，初始化在F8


	HTREEITEM hF1Item ;
	HTREEITEM hF1SubItem1,hF1SubItem2,hF1SubItem3,hF1SubItem4,hF1SubItem5,hF1SubItem6;
//	HTREEITEM hF1SubItem21,hF1SubItem22,hF1SubItem23;
//	HTREEITEM hF1SubItem51,hF1SubItem52;

	HTREEITEM hF2Item ;
	HTREEITEM hF2SubItem1,hF2SubItem2;
	HTREEITEM hF2SubItem11,hF2SubItem12,hF2SubItem13,hF2SubItem14;
	HTREEITEM hF2SubItem21,hF2SubItem22,hF2SubItem23,hF2SubItem24;

	HTREEITEM hF3Item ;
	HTREEITEM hF3SubItem1;
	//***********************
	HTREEITEM hF3SubItem2;

	HTREEITEM hF4Item ;


	HTREEITEM hF5Item ;
	HTREEITEM hF5SubItem1,hF5SubItem2,hF5SubItem3,hF5SubItem4,hF5SubItem5,hF5SubItem6,hF5SubItem7;
	

	HTREEITEM hF6Item ;
	HTREEITEM hF6SubItem1,hF6SubItem2;
	HTREEITEM hF6SubItem3,hF6SubItem4,hF6SubItem5,hF6SubItem6;
	HTREEITEM hF6SubItem7,hF6SubItem8,hF6SubItem9,hF6SubItem10;


	HTREEITEM hF7Item ;
	HTREEITEM hF7SubItem1;

	HTREEITEM hF8Item ;
	HTREEITEM hF8SubItem1,hF8SubItem2;
	HTREEITEM hF8SubItem3,hF8SubItem5,hF8SubItem6;
//	HTREEITEM hF8SubItem3,hF8SubItem4,hF8SubItem5,hF8SubItem6;
	//HTREEITEM hF8SubItem7,hF8SubItem8,hF8SubItem9;

//	HTREEITEM hF9Item ;

// Operations
public:
	void RefreshTreeByUser();//根据用户级别更新菜单树
	void GetItemByData(int idata,HTREEITEM * pitem);
	void HighLightFnButton(int num);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CProgView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CProgView)
	afx_msg void OnF1();
	afx_msg void OnF2();
	afx_msg void OnF3();
	afx_msg void OnF4();
	afx_msg void OnF5();
	afx_msg void OnF6();
	afx_msg void OnF7();
	afx_msg void OnF8();




	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CTreeCtrl m_Tree;
	CTreeCtrl m_TreeF1;
	CTreeCtrl m_TreeF2;
	CTreeCtrl m_TreeF3;
	CTreeCtrl m_TreeF4;
	CTreeCtrl m_TreeF5;
	CTreeCtrl m_TreeF6;
	CTreeCtrl m_TreeF7;
	CTreeCtrl m_TreeF8;
	afx_msg void OnSelchangedTreef1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSelchangedTreef2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSelchangedTreef3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSelchangedTreef4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSelchangedTreef5(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSelchangedTreef6(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSelchangedTreef7(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSelchangedTreef8(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnStnClickedF1();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGVIEW_H__0585C657_C111_4089_A423_FDC681CD7A78__INCLUDED_)
