
// AOIDView.h : CAOIDView ��Ľӿ�
//

#pragma once
#include "AOIDDoc.h"

class CAOIDView : public CView
{
//protected: // �������л�����
public:
	CAOIDView();
	DECLARE_DYNCREATE(CAOIDView)

// ����
public:
	CAOIDDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CAOIDView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // AOIDView.cpp �еĵ��԰汾
inline CAOIDDoc* CAOIDView::GetDocument() const
   { return reinterpret_cast<CAOIDDoc*>(m_pDocument); }
#endif

