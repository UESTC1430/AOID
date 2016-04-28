// MastProgInView.cpp : 实现文件
//

#include "stdafx.h"
#include "AOID.h"
#include "MastProgInView.h"


// CMastProgInView

IMPLEMENT_DYNCREATE(CMastProgInView, CFormView)

CMastProgInView::CMastProgInView()
	: CFormView(CMastProgInView::IDD)
{

	m_filecontentstr = _T("");
	m_pathstr = _T("");
	filetype = _T("");
	filecount = 0;
	pathandname = _T("");
}

CMastProgInView::~CMastProgInView()
{
}

void CMastProgInView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBODRIVE, m_diskdrive);
	DDX_Control(pDX, IDC_COMBOFILENAME, m_mainprofilename);
	DDX_Control(pDX, IDC_COMBOFILETYPE, m_filetype);
	DDX_Text(pDX, IDC_EDITFILECONTENT, m_filecontentstr);
	DDX_Control(pDX, IDC_LISTFILENAME, m_filenamelist);
	DDX_Text(pDX, IDC_STATICPATH, m_pathstr);
}

BEGIN_MESSAGE_MAP(CMastProgInView, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBODRIVE, &CMastProgInView::OnSelchangeCombodrive)
	ON_CBN_SELCHANGE(IDC_COMBOFILETYPE, &CMastProgInView::OnSelchangeComboFileType)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTFILENAME, &CMastProgInView::OnDblclkListfilename)
	ON_STN_CLICKED(IDC_INPORT, &CMastProgInView::OnInport)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTFILENAME, &CMastProgInView::OnLvnItemchangedListfilename)
END_MESSAGE_MAP()


// CMastProgInView 诊断

#ifdef _DEBUG
void CMastProgInView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMastProgInView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMastProgInView 消息处理程序


void CMastProgInView::OnSelchangeCombodrive()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMastProgInView::OnSelchangeComboFileType()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMastProgInView::OnDblclkListfilename(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CMastProgInView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	// TODO: 在此添加专用代码和/或调用基类

	CFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}


void CMastProgInView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
}


void CMastProgInView::OnInport()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMastProgInView::OnLvnItemchangedListfilename(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
