#pragma once


// GameDlg 대화 상자입니다.

class GameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GameDlg)

public:
	GameDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~GameDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAMEDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()

public:
	CFrameWnd m_Frame;
	CCreateContext pContext;

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	virtual BOOL PreTranslateMessage(MSG* pMsg);
};