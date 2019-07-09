
// ChildView.cpp : CChildView 클래스의 구현
//

#include "stdafx.h"
#include "Game.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_GameMode = INIT; 
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	
	switch (m_GameMode)
	{
	case INIT      : Init(dc); break;
	case TITLE     : Title(dc); break;
	case PLAY      : Play(dc); break;
	case GAMEOVER  : GameOver(dc); break;
	}
}

void CChildView::Init(CPaintDC& dc)
{

	// 초기화
	m_Play.Init();//생명,레벨,누적적중,점수 초기화

	// 배경 비트맵 로드
	CString strFile;
	strFile.Format(L"%stitle.bmp", BMP_PATH);
	m_Title.Load(dc, strFile);
	strFile.Format(L"%sGameOver.bmp", BMP_PATH);
	m_GameOver.Load(dc, strFile);
	strFile.Format(L"%sPlayBG.bmp", BMP_PATH);
	m_Play.Load(dc, strFile);
	
	// 캐릭터 및 UI 로드
	m_Play.LoadChar(dc);
	m_Play.LoadUI(dc);

	m_dwTimeTick = 0; //연속적중시간체크 변수
	m_GameMode = TITLE;
	Invalidate(FALSE);
}

void CChildView::Title(CPaintDC& dc)
{
	m_Title.Draw(dc, 0, 0);
}

void CChildView::Play(CPaintDC& dc)
{
	m_Play.Move(dc);			// 게임 이동처리
	m_Play.Draw(dc, 0, 0);		// 게임 출력
}

void CChildView::GameOver(CPaintDC& dc)
{
	// 비트맵
	m_GameOver.Draw(dc, 0, 0);

	// 점수
	CFont Font, *oldFont;

	Font.CreateFont(FONT_SIZE_BIG, FONT_SIZE_BIG, 0, 0, FW_DONTCARE, FALSE,
		FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		L"돋움체");

	oldFont = dc.SelectObject(&Font);

	WCHAR szScore[64];
	wsprintf(szScore, L"Score %03d", m_Play.GetScore());

	dc.SetBkMode(TRANSPARENT);

	dc.TextOut(165, 510, szScore);

	dc.SelectObject(oldFont);
	Font.DeleteObject();
}

void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{	
	switch (m_GameMode)
	{	
	case TITLE   : if (nChar == VK_RETURN || nChar == VK_SPACE) m_GameMode = PLAY; Invalidate(FALSE); break;
	case PLAY    : 
					{
						BOOL bFailed = FALSE;
						BOOL bHitTime = FALSE;
						CPaintDC dc(this);

						// 연속 적중시간이내인가?
						if (GetTickCount() - m_dwTimeTick <= HIT_LIMIT_TIME)
							bHitTime = TRUE;
						else
							bHitTime = FALSE;

						// 좌우키 입력에 따른 캐릭터 분류
						if (nChar == VK_LEFT)						
							bFailed = m_Play.Drop(dc, CChar::LEFT, bHitTime);
						else if (nChar == VK_RIGHT)
							bFailed = m_Play.Drop(dc, CChar::RIGHT, bHitTime);

						// life가 모두 소멸되면
						if (bFailed) m_GameMode = GAMEOVER;

						m_dwTimeTick = GetTickCount();
						Invalidate(FALSE);
					}
				   break;		           
	case GAMEOVER: if (nChar == VK_RETURN || nChar == VK_SPACE)
					{
						m_GameMode = TITLE;
						m_Play.Init();
						Invalidate(FALSE); 
						break;
					}
	}

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == TM_PLAY)
	{
		CPaintDC dc(this);
		Play(dc);
	}

	CWnd::OnTimer(nIDEvent);
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	SetTimer(TM_PLAY, (1000 / 60), NULL);

	return 0;
}


void CChildView::OnDestroy()
{
	CWnd::OnDestroy();

	KillTimer(TM_PLAY);
}
