
// MinionGameDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"


// CMinionGameDlg ��ȭ ����
class CMinionGameDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CMinionGameDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MINIONGAME_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStartButton();
	afx_msg void OnBnClickedHowButton();
	afx_msg void OnBnClickedExitButton();
	CStatic m_ctlPicMoon;
};
