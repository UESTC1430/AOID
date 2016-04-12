// MachineRecordView.cpp : 实现文件
//

#include "stdafx.h"
#include "AOID.h"
#include "MachineRecordView.h"
#include "MainFrm.h"
// CMachineRecordView

IMPLEMENT_DYNCREATE(CMachineRecordView, CFormView)

CMachineRecordView::CMachineRecordView()
	: CFormView(CMachineRecordView::IDD)
{

	m_Keywords = _T("");
	m_typestr = _T("");
}

CMachineRecordView::~CMachineRecordView()
{
}

void CMachineRecordView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_Inport);
	DDX_Text(pDX, IDC_KEYWORDS, m_Keywords);
	DDX_Control(pDX, IDC_MACHINERECORDLIST, m_machinerecordlist);
	DDX_Control(pDX, IDC_TYPE, type);
	DDX_CBString(pDX, IDC_TYPE, m_typestr);
}

BEGIN_MESSAGE_MAP(CMachineRecordView, CFormView)
	ON_BN_CLICKED(IDC_BTNDATETIME, &CMachineRecordView::OnBtnDateTime)
	ON_BN_CLICKED(IDC_BUTTON1, &CMachineRecordView::OnCertern)
	ON_BN_CLICKED(IDC_BTNDATETIME, &CMachineRecordView::OnBtnDateTime)
	ON_BN_CLICKED(IDC_BUTTON1, &CMachineRecordView::OnCertern)
END_MESSAGE_MAP()


// CMachineRecordView 诊断

#ifdef _DEBUG
void CMachineRecordView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMachineRecordView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMachineRecordView 消息处理程序



void CMachineRecordView::OnBtnDateTime()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMachineRecordView::OnCertern()
{
	// TODO: 在此添加控件通知处理程序代码
}
