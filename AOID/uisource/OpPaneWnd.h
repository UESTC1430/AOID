
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

	CSoftWareInfoView	* m_pF1SubItem1View;	//结束
	CAnalysisView		* m_pF1SubItem2View;	//统计分析
	CUserAdminView		* m_pF1SubItem3View;	//用户管理
	CFileAndContentsView *m_pF1SubItem4View;	//文件与目录设置
	CMachineRecordView	* m_pF1SubItem5View;	//履历文件
	CLicenseView		* m_pF1SubItem6View;	//授权许可

	CMastProgInView		* m_pF2SubItem11View;	//生产程序	
	CSubProgInView		* m_pF2SubItem12View;	//副程序

	CCameraImageView    * m_pF3SubItem1View;	//图像对比
	CImageAnalysis      * m_TestView;           //测试用

	CUserTokenView		* m_pF5SubItem1View;	//用户标记
	CInputPortView		* m_pF5SubItem2View;	//输入端口
	COutputPortView		* m_pF5SubItem3View;	//输出端口
	CServeView			* m_pF5SubItem4View;	//伺服器诊断
	CFocusView			* m_pF5SubItem5View;	//摄像头对焦
	
	

	CLightView			* m_pF8SubItem1View;	//灯光
	CMFunctionView		* m_pF8SubItem2View;	//M功能
	CInchFunctionView	* m_pF8SubItem3View;	//寸动
	COrigFunctionView	* m_pF8SubItem4View;	//零点
	CCameraPosView		* m_pF8SubItem5View;	//摄像头设置




	CAOIDView		* m_pAOIDView;

	CView * pOldActiveView;
	UINT m_nCurrentViewID;		//记录当前view的ID





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

