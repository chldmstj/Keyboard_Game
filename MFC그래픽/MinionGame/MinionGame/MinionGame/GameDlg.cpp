// GameDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MinionGame.h"
#include "GameDlg.h"
#include "afxdialogex.h"

#include "GameeView.h" 
#include "GameDoc.h"    //GameDlg->GameView



// GameDlg ��ȭ �����Դϴ�.

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


// GameDlg �޽��� ó�����Դϴ�.







int GameDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
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



//Key�Է¹ޱ�!

BOOL GameDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	switch (pMsg->message) {
	case WM_KEYDOWN:
		if (pMsg->wParam == VK_LEFT || pMsg->wParam == VK_RIGHT) {
			return false;
		}
		break;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
