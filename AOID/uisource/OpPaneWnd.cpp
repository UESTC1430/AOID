// OpPaneWnd.cpp : implementation file
//

#include "stdafx.h"
#include"AOID.h"
#include "OpPaneWnd.h"
#include "winpara.h"



/////////////////////////////////////////////////////////////////////////////
// COpPaneWnd

IMPLEMENT_DYNCREATE(COpPaneWnd, CFrameWnd)

COpPaneWnd::COpPaneWnd()
{
	m_nCurrentViewID = 0;
}

COpPaneWnd::~COpPaneWnd()
{

	delete m_pF1SubItem1View;
	delete m_pF1SubItem2View;
	delete m_pF1SubItem3View;
	delete m_pF1SubItem4View;
	delete m_pF1SubItem5View;
	delete m_pF1SubItem6View;

}


BEGIN_MESSAGE_MAP(COpPaneWnd, CFrameWnd)
	//{{AFX_MSG_MAP(COpPaneWnd)
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpPaneWnd message handlers

BOOL COpPaneWnd::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class

	m_pF1SubItem1View = new CSoftWareInfoView;		//F1�����˵�
	
	m_pF1SubItem2View = new CAnalysisView;			//F1ͳ�Ʒ���
	m_pF1SubItem3View = new CUserAdminView;			//F1�û�����
	m_pF1SubItem4View = new CFileAndContentsView;	//F1�ļ���Ŀ¼����
	m_pF1SubItem5View = new CMachineRecordView;		//F1�����ļ�
	m_pF1SubItem6View = new CLicenseView;			//F1��Ȩ���

	m_pF2SubItem11View = new CMastProgInView;		//F2�ļ�������������
	m_pF2SubItem12View = new CSubProgInView;		//F2������


	m_pF3SubItem1View = new CCameraImageView;			//F3ͼ��Ա�
	m_TestView        = new CImageAnalysis ;        //������

	m_pF5SubItem1View = new CUserTokenView;			//F5�û����
	m_pF5SubItem2View = new CInputPortView;			//F5����˿�
	m_pF5SubItem3View = new COutputPortView;		//F5����˿�  ��Ҫ����µ���ͼ
	m_pF5SubItem4View = new CServeView;			//F5�ŷ������
	m_pF5SubItem5View = new CFocusView;				//F5�Խ�����	��Ҫ����µ���ͼ
	



	m_pF8SubItem1View = new CLightView;				//F8�ƹ�
	m_pF8SubItem2View = new CMFunctionView;			//F8M����
	m_pF8SubItem3View = new CInchFunctionView;		//F8�綯
	m_pF8SubItem4View = new COrigFunctionView;		//F8���
	m_pF8SubItem5View = new CCameraPosView;			//F8����ͷ����


	m_pAOIDView = new CAOIDView;


	((CView *)m_TestView)->Create(NULL,NULL,0L,CFrameWnd::rectDefault,this, VIEW_TESTITEM,pContext);
	((CView *)m_pF1SubItem1View)->Create(NULL,NULL,0L,CFrameWnd::rectDefault,this, VIEW_F1SUBITEM1,pContext);
	((CView *)m_pF1SubItem2View)->Create(NULL,NULL,0L,CFrameWnd::rectDefault,this, VIEW_F1SUBITEM2,pContext);
	((CView *)m_pF1SubItem3View)->Create(NULL,NULL,0L,CFrameWnd::rectDefault,this, VIEW_F1SUBITEM3,pContext);
	((CView *)m_pF1SubItem4View)->Create(NULL,NULL,0L,CFrameWnd::rectDefault,this, VIEW_F1SUBITEM4,pContext);     
	((CView *)m_pF1SubItem5View)->Create(NULL,NULL,0L,CFrameWnd::rectDefault,this, VIEW_F1SUBITEM5,pContext);
	((CView *)m_pF1SubItem6View)->Create(NULL,NULL,0L,CFrameWnd::rectDefault,this, VIEW_F1SUBITEM6,pContext);
	


	((CView *)m_pF2SubItem11View)->Create(NULL,NULL,0L,CFrameWnd::rectDefault,this, VIEW_F2SUBITEM11,pContext);
	((CView *)m_pF2SubItem12View)->Create(NULL,NULL,0L,CFrameWnd::rectDefault,this, VIEW_F2SUBITEM12,pContext);


	((CView *)m_pF3SubItem1View)->Create(NULL,NULL,0L,CFrameWnd::rectDefault,this, VIEW_F3SUBITEM1,pContext);

	((CView *)m_pF5SubItem1View)->Create(NULL,NULL,0L,CFrameWnd::rectDefault,this, VIEW_F5SUBITEM1,pContext);
	((CView *)m_pF5SubItem2View)->Create(NULL,NULL,0L,CFrameWnd::rectDefault,this, VIEW_F5SUBITEM2,pContext);
	((CView *)m_pF5SubItem3View)->Create(NULL,NULL,0L,CFrameWnd::rectDefault,this, VIEW_F5SUBITEM3,pContext);
	((CView *)m_pF5SubItem4View)->Create(NULL,NULL,0L,CFrameWnd::rectDefault,this, VIEW_F5SUBITEM4,pContext);
	((CView *)m_pF5SubItem5View)->Create(NULL,NULL,0L,CFrameWnd::rectDefault,this, VIEW_F5SUBITEM5,pContext);



	((CView *)m_pF8SubItem1View)->Create(NULL,NULL,0L,CFrameWnd::rectDefault,this, VIEW_F8SUBITEM1,pContext);
	((CView *)m_pF8SubItem2View)->Create(NULL,NULL,0L,CFrameWnd::rectDefault,this, VIEW_F8SUBITEM2,pContext);
	((CView *)m_pF8SubItem3View)->Create(NULL,NULL,0L,CFrameWnd::rectDefault,this, VIEW_F8SUBITEM3,pContext);
	((CView *)m_pF8SubItem4View)->Create(NULL,NULL,0L,CFrameWnd::rectDefault,this, VIEW_F8SUBITEM4,pContext);
	((CView *)m_pF8SubItem5View)->Create(NULL,NULL,0L,CFrameWnd::rectDefault,this, VIEW_F8SUBITEM5,pContext);

	((CView *)m_pAOIDView)->Create(NULL,NULL,0L,CFrameWnd::rectDefault,this, VIEW_FRAME,pContext);
	m_pAOIDView->SetDlgCtrlID(VIEW_FRAME);


	m_nCurrentViewID = VIEW_FRAME;
	pOldActiveView = m_pAOIDView;

	m_pAOIDView->ShowWindow(SW_SHOW);
	m_pAOIDView->SetDlgCtrlID(AFX_IDW_PANE_FIRST);
	SetActiveView(m_pAOIDView);
	RecalcLayout();


	return TRUE;

	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}
void COpPaneWnd::SwitchToView(UINT nView)
{
	//�л���ͼ

	CView *pNewActiveView =NULL;

	switch(nView)
	{

	case VIEW_FRAME:
		pNewActiveView = (CAOIDView * ) m_pAOIDView;		
		break;
	case VIEW_F1SUBITEM1:
		pNewActiveView = (CSoftWareInfoView * ) this-> m_pF1SubItem1View;//m_pF1SubItem1View;	
		break;
	case VIEW_F1SUBITEM2:
		pNewActiveView = (CAnalysisView * ) m_pF1SubItem2View;	
		break;

	case VIEW_F1SUBITEM3:
		pNewActiveView = (CUserAdminView * ) m_pF1SubItem3View;	
		break;
	case VIEW_F1SUBITEM4:
		pNewActiveView = (CFileAndContentsView * ) m_pF1SubItem4View;	
		break;
	case VIEW_F1SUBITEM5:
		pNewActiveView = (CMachineRecordView * ) m_pF1SubItem5View;	
		break;

	case VIEW_F1SUBITEM6:
		pNewActiveView = (CLicenseView * ) m_pF1SubItem6View;	
		break;

	


	case VIEW_F2SUBITEM11:
		pNewActiveView = (CMastProgInView * ) m_pF2SubItem11View;
		break;
	case VIEW_F2SUBITEM12:
		pNewActiveView = (CSubProgInView * ) m_pF2SubItem12View;
		break;


	case VIEW_F3SUBITEM1:
		pNewActiveView = (CCameraImageView* ) m_pF3SubItem1View;
		break;
	case VIEW_TESTITEM:
		pNewActiveView = (CImageAnalysis* ) m_TestView;
		break;

	case VIEW_F4SUBITEM1:
		return;
	


	case VIEW_F5SUBITEM1://�û����
		pNewActiveView = (CUserTokenView * ) m_pF5SubItem1View;
		break;

		break;
	case VIEW_F5SUBITEM2://����˿�
		pNewActiveView = (CInputPortView * ) m_pF5SubItem2View;
		break;
	case VIEW_F5SUBITEM3://����˿�
		pNewActiveView = (COutputPortView * ) m_pF5SubItem3View;
		break;

	case VIEW_F5SUBITEM4://�ŷ�
		pNewActiveView = (CServeView * ) m_pF5SubItem4View;
		break;//��λ����
	case VIEW_F5SUBITEM5://����ͷ�Խ�
		pNewActiveView = (CFocusView * ) m_pF5SubItem5View;
		break;//��λ����



	case VIEW_F7SUBITEM1:

		break;


	case VIEW_F8SUBITEM1:

		pNewActiveView = (CLightView * ) m_pF8SubItem1View;
		break;
	case VIEW_F8SUBITEM2:
		pNewActiveView = (CMFunctionView * ) m_pF8SubItem2View;
		break;
	case VIEW_F8SUBITEM3:
		pNewActiveView = (CInchFunctionView * ) m_pF8SubItem3View;
		break;

	case VIEW_F8SUBITEM4:
		pNewActiveView = (COrigFunctionView * ) m_pF8SubItem4View;
		break;
	case VIEW_F8SUBITEM5:
		pNewActiveView = (CCameraPosView * ) m_pF8SubItem5View;
		break;

		
	default:
		break;
	}

		SetActiveView(pNewActiveView);
		int temp1=pNewActiveView->ShowWindow(SW_SHOW);
		pNewActiveView->UpdateWindow();
		pNewActiveView->SetDlgCtrlID(AFX_IDW_PANE_FIRST);

		if(pOldActiveView!=	pNewActiveView)//F5����ͼ1�ɾ�̬�б�1��2����̬�б�ֱ���б��á�����֮���л�ʱ��ִ��ѭ�����ڵ����
		{
			pOldActiveView->ShowWindow(SW_HIDE);
			pOldActiveView->UpdateWindow();
			pOldActiveView->SetDlgCtrlID(m_nCurrentViewID);
		}
		RecalcLayout();
		m_nCurrentViewID = nView;
		pOldActiveView = pNewActiveView;
}

BOOL COpPaneWnd::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default

	return true;
}
