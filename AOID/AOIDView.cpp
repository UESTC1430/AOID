
// AOIDView.cpp : CAOIDView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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

// CAOIDView ����/����

CAOIDView::CAOIDView()
{
	// TODO: �ڴ˴���ӹ������

}

CAOIDView::~CAOIDView()
{
}

BOOL CAOIDView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CAOIDView ����

void CAOIDView::OnDraw(CDC* /*pDC*/)
{
	CAOIDDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
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


// CAOIDView ���

#ifdef _DEBUG
void CAOIDView::AssertValid() const
{
	CView::AssertValid();
}

void CAOIDView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAOIDDoc* CAOIDView::GetDocument() const // �ǵ��԰汾��������
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


// CAOIDView ��Ϣ�������
