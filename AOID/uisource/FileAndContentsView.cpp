// FileAndContentsView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AOID.h"
#include "FileAndContentsView.h"


// CFileAndContentsView

IMPLEMENT_DYNCREATE(CFileAndContentsView, CFormView)

CFileAndContentsView::CFileAndContentsView()
	: CFormView(CFileAndContentsView::IDD)
{

}

CFileAndContentsView::~CFileAndContentsView()
{
}

void CFileAndContentsView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	/*DDX_Control(pDX, IDC_SUBPATHBTN, m_subpathbtn);
	DDX_Control(pDX, IDC_MASTPATHBTN, m_mastpathbtn);
	DDX_Control(pDX, IDC_ATPPATHBTN, m_atppathbtn);
	DDX_Text(pDX, IDC_SUBPROGPATH, m_subprogpath);
	DDX_Text(pDX, IDC_ATPPROGPATH, m_atpprogpath);
	DDX_Text(pDX, IDC_MASTPROGPATH, m_mastprogpath);*/
}

BEGIN_MESSAGE_MAP(CFileAndContentsView, CFormView)
/*	ON_BN_CLICKED(IDC_MASTPATHBTN, &CFileAndContentsView::OnMastpathChange)
	ON_BN_CLICKED(IDC_SUBPATHBTN, &CFileAndContentsView::OnSubpathChange)
	ON_BN_CLICKED(IDC_ATPPATHBTN, &CFileAndContentsView::OnAtppathChange)
	ON_EN_KILLFOCUS(IDC_MASTPROGPATH, &CFileAndContentsView::OnKillfocusMastprogpath)
	ON_EN_SETFOCUS(IDC_MASTPROGPATH, &CFileAndContentsView::OnSetfocusMastprogpath)
	ON_EN_KILLFOCUS(IDC_SUBPROGPATH, &CFileAndContentsView::OnKillfocusSubprogpath)
	ON_EN_SETFOCUS(IDC_SUBPROGPATH, &CFileAndContentsView::OnSetfocusSubprogpath)
	ON_EN_KILLFOCUS(IDC_SUBPROGPATH2, &CFileAndContentsView::OnKillfocusAtpprogpath)
	ON_EN_SETFOCUS(IDC_SUBPROGPATH2, &CFileAndContentsView::OnSetfocusAtpprogpath)
	ON_BN_CLICKED(IDC_MASTPATHBTN, &CFileAndContentsView::OnBnClickedMastpathbtn)*/
END_MESSAGE_MAP()


// CFileAndContentsView ���

#ifdef _DEBUG
void CFileAndContentsView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFileAndContentsView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFileAndContentsView ��Ϣ�������


void CFileAndContentsView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	CFormView::OnInitialUpdate();
	m_mastprogpath=theApp.pwnd->m_cnccontrol.Configstruct.FileInfo.cmastprogpath;
	m_subprogpath=theApp.pwnd->m_cnccontrol.Configstruct.FileInfo.csubprogpath;
	m_atpprogpath=theApp.pwnd->m_cnccontrol.Configstruct.FileInfo.catppath;
	UpdateData(false);
}

void CFileAndContentsView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	// TODO: �ڴ����ר�ô����/����û���

	CFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}


void CFileAndContentsView::OnMastpathChange()
{
	/*// TODO: Add your control notification handler code here
	CMainFrame *pwnd=(CMainFrame *)AfxGetMainWnd();
	if(IDOK==pathchangedlg.DoModal())
	{
		m_mastprogpath=pathchangedlg.m_pathstr;//·������
		strcpy(theApp.pwnd->m_cnccontrol.Configstruct.FileInfo.cmastprogpath,m_mastprogpath);//�رճ���ʱд�뻷���ݴ��ļ�
		m_mastpathbtn.ShowWindow(false);//��ť����
		UpdateData(false);
	}*/
}


void CFileAndContentsView::OnSubpathChange()
{
/*	// TODO: Add your control notification handler code here
	if(IDOK==pathchangedlg.DoModal())
	{
		m_subprogpath=pathchangedlg.m_pathstr;
		strcpy(theApp.pwnd->m_cnccontrol.Configstruct.FileInfo.csubprogpath,m_subprogpath);
		m_subpathbtn.ShowWindow(false);
		UpdateData(false);
	}*/
}


void CFileAndContentsView::OnAtppathChange()
{
	// TODO: Add your control notification handler code here
/*	CMainFrame *pwnd=(CMainFrame *)AfxGetMainWnd();
	if(IDOK==pathchangedlg.DoModal())
	{
		m_atpprogpath=pathchangedlg.m_pathstr;
		strcpy(theApp.pwnd->m_cnccontrol.Configstruct.FileInfo.catppath,m_atpprogpath);
		m_atppathbtn.ShowWindow(false);
		UpdateData(false);
	}*/
}


void CFileAndContentsView::OnKillfocusMastprogpath()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//	m_mastpathbtn.ShowWindow(FALSE);
}


void CFileAndContentsView::OnSetfocusMastprogpath()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_mastpathbtn.ShowWindow(TRUE);

}


void CFileAndContentsView::OnKillfocusSubprogpath()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//	m_subpathbtn.ShowWindow(FALSE);
}


void CFileAndContentsView::OnSetfocusSubprogpath()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_subpathbtn.ShowWindow(TRUE);

}


void CFileAndContentsView::OnKillfocusAtpprogpath()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//	m_atppathbtn.ShowWindow(FALSE);
}


void CFileAndContentsView::OnSetfocusAtpprogpath()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_atppathbtn.ShowWindow(TRUE);
}




