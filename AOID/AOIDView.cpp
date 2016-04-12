
// AOIDView.cpp : CAOIDView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "AOID.h"
#endif

#include "AOIDDoc.h"
#include "AOIDView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAOIDView

IMPLEMENT_DYNCREATE(CAOIDView, CView)

BEGIN_MESSAGE_MAP(CAOIDView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CAOIDView 构造/析构

CAOIDView::CAOIDView()
{
	// TODO: 在此处添加构造代码

}

CAOIDView::~CAOIDView()
{
}

BOOL CAOIDView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CAOIDView 绘制

void CAOIDView::OnDraw(CDC* /*pDC*/)
{
	CAOIDDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}

void CAOIDView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CAOIDView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
//#ifndef SHARED_HANDLERS
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
//#endif
}


// CAOIDView 诊断

#ifdef _DEBUG
void CAOIDView::AssertValid() const
{
	CView::AssertValid();
}

void CAOIDView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAOIDDoc* CAOIDView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAOIDDoc)));
	return (CAOIDDoc*)m_pDocument;
}
//*****************************
#ifndef _DEBUG  // debug version in cncView.cpp
inline CAOIDDoc* CAOIDView::GetDocument()
   { return (CAOIDDoc*)m_pDocument; }
#endif
//*****************************
#endif //_DEBUG


// CAOIDView 消息处理程序
