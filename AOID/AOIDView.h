
// AOIDView.h : CAOIDView 类的接口
//

#pragma once
#include "AOIDDoc.h"

class CAOIDView : public CView
{
//protected: // 仅从序列化创建
public:
	CAOIDView();
	DECLARE_DYNCREATE(CAOIDView)

// 特性
public:
	CAOIDDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CAOIDView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // AOIDView.cpp 中的调试版本
inline CAOIDDoc* CAOIDView::GetDocument() const
   { return reinterpret_cast<CAOIDDoc*>(m_pDocument); }
#endif

