// GameDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MinionGame.h"
#include "GameDlg.h"
#include "afxdialogex.h"

#include "GameeView.h" 
#include "GameDoc.h"    //GameDlg->GameView



// GameDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(GameDlg, CDialogEx)

GameDlg::GameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GAMEDLG, pParent)
{
}

GameDlg::~GameDlg()
{
}

void GameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(GameDlg, CDialogEx)

	ON_WM_CREATE()
END_MESSAGE_MAP()


// GameDlg 메시지 처리기입니다.







int GameDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	//----Gamedlg->GameView, GameDoc------
	CWnd* pFrameWnd = this;
	pContext.m_pCurrentDoc = new GameDoc;
	pContext.m_pNewViewClass = RUNTIME_CLASS(GameeView);
	GameeView* pView = (GameeView*)((CFrameWnd*)pFrameWnd)->CreateView(&pContext);
	ASSERT(pView);
	pView->ShowWindow(SW_NORMAL);
	pView->MoveWindow(0, 0, 870, 469);



	return 0;
}



//Key입력받기!

BOOL GameDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	switch (pMsg->message) {
	case WM_KEYDOWN:
		if (pMsg->wParam == VK_LEFT || pMsg->wParam == VK_RIGHT) {
			return false;
		}
		break;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
