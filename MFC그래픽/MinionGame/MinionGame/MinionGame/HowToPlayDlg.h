#pragma once
#include "afxwin.h"


// HowToPlayDlg ��ȭ �����Դϴ�.

class HowToPlayDlg : public CDialogEx
{
	DECLARE_DYNAMIC(HowToPlayDlg)

public:
	HowToPlayDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~HowToPlayDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HOWTOPLAY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.


	BOOL OnInitDialog(); //ȭ������������!

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_ctlPicGru;
	afx_msg void OnPaint();
};
