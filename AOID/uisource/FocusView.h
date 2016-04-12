#pragma once



// CFocusView ������ͼ

class CFocusView : public CFormView
{
	DECLARE_DYNCREATE(CFocusView)

//protected:
public:
	CFocusView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CFocusView();

public:
	enum { IDD = IDD_FOCUSVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedGetvalue();
	afx_msg void OnBnClickedAutofocus();
	afx_msg void OnBnClickedZUp();
	afx_msg void OnBnClickedZDown();
	CStatic m_focuslocation;
	CStatic m_z;
	CStatic m_picturevalue;
	afx_msg void OnPaint();
	int focuslocation;
	float camscale;
	float maxvalue;
};


