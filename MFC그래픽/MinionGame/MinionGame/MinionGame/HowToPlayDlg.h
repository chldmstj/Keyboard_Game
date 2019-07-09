#pragma once
#include "afxwin.h"


// HowToPlayDlg 대화 상자입니다.

class HowToPlayDlg : public CDialogEx
{
	DECLARE_DYNAMIC(HowToPlayDlg)

public:
	HowToPlayDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~HowToPlayDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HOWTOPLAY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.


	BOOL OnInitDialog(); //화면조절을위해!

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_ctlPicGru;
	afx_msg void OnPaint();
};
