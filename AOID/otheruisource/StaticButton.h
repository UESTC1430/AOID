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
	HBITMAP FV1;//������ʾ λͼ����
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
	UINT icuroption;//��ǰѡ�е�ѡ���0������
	UINT icurbmpoption;//��ǰѡ�е�λͼ
	UINT ipopsel;		//����ʽѡ��
	HBITMAP *m_phbitmap;//ѡ�ť���
	HBITMAP *m_phebitmap;
	bool m_bgrey;

	//������ǰ��ť����갴��ʱ�Ƿ������⴦����Ϊ�������⴦��Ĭ��Ϊ��
	//��Ҫ��������������Ӧ����ʱ������
	//�˴���up����ȡ�������ϲ㰴���������и���
	int idelay;
	

	int m_mousedown;//ָʾ��ǰ����ʱ��갴�»��ǰ�������
protected:
	UINT ioptionbmpnum;//�ð�ťѡ��λͼ��Ŀ����1������chinese
	UINT icuroptionnum;//��ǰ����ӵ�ѡ����Ŀ����1������chinese
	UINT ieoptionbmpnum;//�ð�ťѡ��λͼ��Ŀ����1������english
	UINT iecuroptionnum;//��ǰ����ӵ�ѡ����Ŀ����1������english

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
