#if !defined(AFX_STATICBUTTON_H__4A73442D_EB5C_11D3_B07D_0050DAB826FF__INCLUDED_)
#define AFX_STATICBUTTON_H__4A73442D_EB5C_11D3_B07D_0050DAB826FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StaticButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStaticButton window

class CStaticButton : public CStatic
{
// Construction
public:
	CStaticButton(UINT iopnum);
	HBITMAP Up;
	HBITMAP Down;
	HBITMAP FV1;//坐标显示 位图变量
	HBITMAP FV2;
	HBITMAP FV3;
	HBITMAP FV4;
	HBITMAP FV5;
	HBITMAP FV6;
	HBITMAP FV7;
	HCURSOR Select;
	HCURSOR No;
	BOOL bActive;
	BOOL Enable;
	CRgn* Region;
	static CRect rect;
	CToolTipCtrl* cTool;
	UINT icuroption;//当前选中的选项（从0计数）
	UINT icurbmpoption;//当前选中的位图
	UINT ipopsel;		//弹出式选项
	HBITMAP *m_phbitmap;//选项按钮句柄
	HBITMAP *m_phebitmap;
	bool m_bgrey;

	//决定当前按钮在鼠标按下时是否作特殊处理，不为零作特殊处理，默认为零
	//主要解决鼠标点击过快响应不急时的问题
	//此处理将up处理取消，由上层按键处理自行更新
	int idelay;
	

	int m_mousedown;//指示当前按键时鼠标按下还是按键按下
protected:
	UINT ioptionbmpnum;//该按钮选项位图数目（从1计数）chinese
	UINT icuroptionnum;//当前已添加的选项数目（从1计数）chinese
	UINT ieoptionbmpnum;//该按钮选项位图数目（从1计数）english
	UINT iecuroptionnum;//当前已添加的选项数目（从1计数）english

// Attributes
public:
	void wSetBitmap(HBITMAP hBitmapUP, HBITMAP hBitmapDOWN, BOOL bAct = FALSE, CRgn* rgn = NULL);
	BOOL ChangeCursor(CPoint point);

	HBITMAP GetBitmapUp();
	HBITMAP GetBitmapDown();

	void SetEnable(BOOL B);
	BOOL GetEnable() { return Enable; };

	void SetRegion(CRgn* rgn);
	CRgn* GetRegion();

	void SetToolTip(LPSTR lpToolTip);
	CToolTipCtrl* GetToolTip() { return cTool; };

	void SetCursor(BOOL bSel, HCURSOR hCur);
	HCURSOR GetCursor(BOOL bSel);

	int GetOptionNum();
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaticButton)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStaticButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CStaticButton)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	void AppendBitmap(HBITMAP hBitmapUP);
	void AppendEBitmap(HBITMAP hBitmapUP);
	void InitRgn(CRgn * rgn);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATICBUTTON_H__4A73442D_EB5C_11D3_B07D_0050DAB826FF__INCLUDED_)
