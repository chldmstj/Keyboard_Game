
// ChildView.cpp : CChildView Ŭ������ ����
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



// CChildView �޽��� ó����

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
	CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.
	
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

	// �ʱ�ȭ
	m_Play.Init();//����,����,��������,���� �ʱ�ȭ

	// ��� ��Ʈ�� �ε�
	CString strFile;
	strFile.Format(L"%stitle.bmp", BMP_PATH);
	m_Title.Load(dc, strFile);
	strFile.Format(L"%sGameOver.bmp", BMP_PATH);
	m_GameOver.Load(dc, strFile);
	strFile.Format(L"%sPlayBG.bmp", BMP_PATH);
	m_Play.Load(dc, strFile);
	
	// ĳ���� �� UI �ε�
	m_Play.LoadChar(dc);
	m_Play.LoadUI(dc);

	m_dwTimeTick = 0; //�������߽ð�üũ ����
	m_GameMode = TITLE;
	Invalidate(FALSE);
}

void CChildView::Title(CPaintDC& dc)
{
	m_Title.Draw(dc, 0, 0);
}

void CChildView::Play(CPaintDC& dc)
{
	m_Play.Move(dc);			// ���� �̵�ó��
	m_Play.Draw(dc, 0, 0);		// ���� ���
}

void CChildView::GameOver(CPaintDC& dc)
{
	// ��Ʈ��
	m_GameOver.Draw(dc, 0, 0);

	// ����
	CFont Font, *oldFont;

	Font.CreateFont(FONT_SIZE_BIG, FONT_SIZE_BIG, 0, 0, FW_DONTCARE, FALSE,
		FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		L"����ü");

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

						// ���� ���߽ð��̳��ΰ�?
						if (GetTickCount() - m_dwTimeTick <= HIT_LIMIT_TIME)
							bHitTime = TRUE;
						else
							bHitTime = FALSE;

						// �¿�Ű �Է¿� ���� ĳ���� �з�
						if (nChar == VK_LEFT)						
							bFailed = m_Play.Drop(dc, CChar::LEFT, bHitTime);
						else if (nChar == VK_RIGHT)
							bFailed = m_Play.Drop(dc, CChar::RIGHT, bHitTime);

						// life�� ��� �Ҹ�Ǹ�
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

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	SetTimer(TM_PLAY, (1000 / 60), NULL);

	return 0;
}


void CChildView::OnDestroy()
{
	CWnd::OnDestroy();

	KillTimer(TM_PLAY);
}
