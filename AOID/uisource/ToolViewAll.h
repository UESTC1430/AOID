#pragma once



// CToolViewAll ������ͼ

class CToolViewAll : public CFormView
{
	DECLARE_DYNCREATE(CToolViewAll)

protected:
	CToolViewAll();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CToolViewAll();

public:
	enum { IDD = IDD_TOOLVIEWALL };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};


