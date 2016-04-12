
#pragma once

// OpPaneWnd.h : header file
//

#include "AnalysisView.h"
#include "mastproginview.h"
#include "subproginview.h"
#include "softwareinfoview.h"
#include "licenseview.h"
#include "useradminview.h"
#include "FileAndContentsView.h"
#include "CameraPosView.h"
#include "MFunctionView.h"
#include "InchFunctionView.h"
#include "OrigFunctionView.h"
#include "UserTokenView.h"
#include "ServeView.h"
#include "InputPortView.h"
#include "OutputPortView.h"

#include "MachineRecordView.h"
#include "CameraImageView.h"
#include "LightView.h"
#include "FocusView.h"
#include "ImageAnalysis.h"



#include "AOIDView.h"
/////////////////////////////////////////////////////////////////////////////
// COpPaneWnd frame

class COpPaneWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(COpPaneWnd)
public:
	COpPaneWnd();           // protected constructor used by dynamic creation

// Attributes
public:

	CSoftWareInfoView	* m_pF1SubItem1View;	//����
	CAnalysisView		* m_pF1SubItem2View;	//ͳ�Ʒ���
	CUserAdminView		* m_pF1SubItem3View;	//�û�����
	CFileAndContentsView *m_pF1SubItem4View;	//�ļ���Ŀ¼����
	CMachineRecordView	* m_pF1SubItem5View;	//�����ļ�
	CLicenseView		* m_pF1SubItem6View;	//��Ȩ���

	CMastProgInView		* m_pF2SubItem11View;	//��������	
	CSubProgInView		* m_pF2SubItem12View;	//������

	CCameraImageView    * m_pF3SubItem1View;	//ͼ��Ա�
	CImageAnalysis      * m_TestView;           //������

	CUserTokenView		* m_pF5SubItem1View;	//�û����
	CInputPortView		* m_pF5SubItem2View;	//����˿�
	COutputPortView		* m_pF5SubItem3View;	//����˿�
	CServeView			* m_pF5SubItem4View;	//�ŷ������
	CFocusView			* m_pF5SubItem5View;	//����ͷ�Խ�
	
	

	CLightView			* m_pF8SubItem1View;	//�ƹ�
	CMFunctionView		* m_pF8SubItem2View;	//M����
	CInchFunctionView	* m_pF8SubItem3View;	//�綯
	COrigFunctionView	* m_pF8SubItem4View;	//���
	CCameraPosView		* m_pF8SubItem5View;	//����ͷ����




	CAOIDView		* m_pAOIDView;

	CView * pOldActiveView;
	UINT m_nCurrentViewID;		//��¼��ǰview��ID





// Operations
public:
	void SwitchToView(UINT nView);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpPaneWnd)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COpPaneWnd();

	// Generated message map functions
	//{{AFX_MSG(COpPaneWnd)
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

