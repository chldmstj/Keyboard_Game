#pragma once


// GameDlg ��ȭ �����Դϴ�.

class GameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GameDlg)

public:
	GameDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~GameDlg();

	// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAMEDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	DECLARE_MESSAGE_MAP()

public:
	CFrameWnd m_Frame;
	CCreateContext pContext;

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	virtual BOOL PreTranslateMessage(MSG* pMsg);
};