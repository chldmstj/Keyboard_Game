#include "stdafx.h"
#include "class.h"

CTitle::CTitle()
{	
}

CTitle::~CTitle()
{
	Release();
}

void CTitle::Release()
{
	DeleteObject();				// 비트맵 삭제
	if (m_pMemDC)				// 메모리DC 제거
	{
		m_pMemDC->DeleteDC();
		delete m_pMemDC;
		m_pMemDC = NULL;
	}	
}

void CTitle::Load(CPaintDC& dc, CString file)
{
	// 파일로 부터 비트맵을 로드
	HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, file, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hBitmap) Attach(hBitmap);

	// 메모리 DC 생성 및 선택
	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(&dc);
	m_pMemDC->SelectObject(this);

	// 비트맵 크기 정보
	BITMAP bmpInfo;
	GetBitmap(&bmpInfo);

	m_nWidth = bmpInfo.bmWidth;
	m_nHeight = bmpInfo.bmHeight;
}

void CTitle::Draw(CPaintDC& dc, int x, int y)
{
	// dc에 이미지 출력
	dc.BitBlt(x, y, m_nWidth, m_nHeight, m_pMemDC, 0, 0, SRCCOPY);
}

////
CUI::CUI()
{
}

CUI::~CUI()
{
	Release();
}

void CUI::Release()
{
	DeleteObject();
	if (m_pMemDC)
	{
		m_pMemDC->DeleteDC();
		delete m_pMemDC;
		m_pMemDC = NULL;
	}
}

void CUI::Load(CPaintDC& dc, CString file)
{
	HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, file, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hBitmap) Attach(hBitmap);

	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(&dc);
	m_pMemDC->SelectObject(this);

	BITMAP bmpInfo;
	GetBitmap(&bmpInfo);

	m_nWidth = bmpInfo.bmWidth;
	m_nHeight = bmpInfo.bmHeight;
}

void CUI::Draw(CPaintDC& dc, int x, int y)
{
	// 스프라이트로 출력(녹색이 제외되서 출력)
	dc.TransparentBlt(x, y,
		              m_nWidth, m_nHeight, m_pMemDC, 0, 0, m_nWidth, m_nHeight, RGB(0, 255, 0));
}

void CUI::Draw(CDC* pDC, int x, int y)
{
	pDC->TransparentBlt(x, y,
		                m_nWidth, m_nHeight, m_pMemDC, 0, 0, m_nWidth, m_nHeight, RGB(0, 255, 0));
}
////

CGameOver::CGameOver()
{
}

CGameOver::~CGameOver()
{
	Release();
}

void CGameOver::Release()
{
	DeleteObject();
	if (m_pMemDC)
	{
		m_pMemDC->DeleteDC();
		delete m_pMemDC;
		m_pMemDC = NULL;
	}
}

void CGameOver::Load(CPaintDC& dc, CString file)
{
	HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, file, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hBitmap) Attach(hBitmap);

	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(&dc);
	m_pMemDC->SelectObject(this);

	BITMAP bmpInfo;
	GetBitmap(&bmpInfo);

	m_nWidth = bmpInfo.bmWidth;
	m_nHeight = bmpInfo.bmHeight;
}

void CGameOver::Draw(CPaintDC& dc, int x, int y)
{
	dc.BitBlt(x, y, m_nWidth, m_nHeight, m_pMemDC, 0, 0, SRCCOPY);
}

////
CChar::CChar()
{	
	m_nX = 400;
	m_nY = 0;
	m_nPos = 0;
}

CChar::~CChar()
{
	Release();
}

void CChar::Release()
{
	DeleteObject();
	if (m_pMemDC)
	{
		m_pMemDC->DeleteDC();
		delete m_pMemDC;
		m_pMemDC = NULL;
	}
}

void CChar::Load(CPaintDC& dc, CString file, Type type, int num)
{
	m_nNum = num;
	m_nType = type;

	//
	HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, file, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hBitmap) Attach(hBitmap);

	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(&dc);
	m_pMemDC->SelectObject(this);

	BITMAP bmpInfo;
	GetBitmap(&bmpInfo);

	m_nWidth = bmpInfo.bmWidth;
	m_nHeight = bmpInfo.bmHeight;
}

BOOL CChar::Move(int pos)
{	
	m_nPos = ((MAX_CHAR-2 - pos) * 72);	// pos는 0~9로 캐릭터의 위치를 나타낸다. 이 위치를 화면좌표로 변환하는 수식	
	                                    // 세로 크기 72단위로 나열한다(간격을 줄일거나 늘릴수있다)
	return TRUE;
}

void CChar::Draw(CPaintDC& dc)
{
	dc.TransparentBlt(m_nX, m_nPos+m_nY, 
		              m_nWidth, m_nHeight, m_pMemDC, 0, 0, m_nWidth, m_nHeight, RGB(0, 255, 0));
}

void CChar::Draw(CDC* pDC)
{
	pDC->TransparentBlt(m_nX, m_nPos + m_nY,
						m_nWidth, m_nHeight, m_pMemDC, 0, 0, m_nWidth, m_nHeight, RGB(0, 255, 0));
}

////
	
CPlay::CPlay()
{	
}

CPlay::~CPlay()
{
	Release();
}

void CPlay::Release()
{
	DeleteObject();
	if (m_pMemDC)
	{
		m_pMemDC->DeleteDC();
		delete m_pMemDC;
		m_pMemDC = NULL;
	}

	ReleaseChar();
}

void CPlay::Init()
{
	m_nLife = 3;			// 초기 생명
	m_nLevel = 1;			// 시작 레벨
	m_nScore = 0;			// 점수
	m_nAccumHitCount = 0;	// 누적적중수
}

void CPlay::ReleaseChar()
{
	CChar* pChar;
	POSITION pos = m_CharList.GetHeadPosition();	// 리스트의 헤드포지션의 노드 부터 모두 순회
	while(pos)
	{
		pChar = m_CharList.GetNext(pos);
		delete pChar;								// 메모리에서 제거
	}
	m_CharList.RemoveAll();							// 리스트 요소 모두 제거
}

void CPlay::Load(CPaintDC& dc, CString file)
{
	HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, file, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hBitmap) Attach(hBitmap);

	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(&dc);
	m_pMemDC->SelectObject(this);

	BITMAP bmpInfo;
	GetBitmap(&bmpInfo);

	m_nWidth = bmpInfo.bmWidth;
	m_nHeight = bmpInfo.bmHeight;
}

void CPlay::LoadUI(CPaintDC& dc)
{
	CString strFile;
	strFile.Format(L"%sLife.bmp", BMP_PATH);			// BMP_PATH에 위치한 비트맵을 로드
	m_Life.Load(dc, strFile);
	strFile.Format(L"%sleft.bmp", BMP_PATH);
	m_Left.Load(dc, strFile);
	strFile.Format(L"%sright.bmp", BMP_PATH);
	m_Right.Load(dc, strFile);
	for (int i = 0; i < MAX_CHAR_BMP; i++)				// 캐릭터 레퍼런스 비트맵 로드(좌우 모두 5개)
	{
		strFile.Format(L"%s%d.bmp", BMP_PATH, i+1);
		m_CharRef[i].Load(dc, strFile);
	}
}

void CPlay::LoadChar(CPaintDC& dc)
{
	for (int i = 0; i < MAX_CHAR; i++)
	{
		CreateChar(dc);
	}	
}

void CPlay::CreateChar(CPaintDC& dc)
{
	int n;
	CChar* pChar;
	CString strFile;
	
	n = (rand() % MAX_CHAR_BMP) + 1;
	strFile.Format(L"%s%d.bmp", BMP_PATH, n);
	pChar = new CChar;
	pChar->Load(dc, strFile, (n < 3) ? CChar::LEFT : CChar::RIGHT, n);	// 1~2이면 LEFT, 3~5는 RIGHT
	m_CharList.AddTail(pChar);	// 리스트에 추가
}

void CPlay::Move(CPaintDC& dc)
{
	int posChar=-1;									// 화면좌표로 출력하기 전의 위치 0~9
	CChar* pChar;
	POSITION pos = m_CharList.GetHeadPosition();	// 리스트의 모든 노드를 순회
	while (pos)
	{
		pChar = m_CharList.GetNext(pos);
		pChar->Move(posChar);						// 캐릭터 이동처리
		posChar++;
	}
}

void CPlay::Draw(CPaintDC& dc, int x, int y)
{
	// 배경
	dc.BitBlt(x, y, m_nWidth, m_nHeight, m_pMemDC, 0, 0, SRCCOPY);

	// 분류할 캐릭터 출력
	CChar* pChar;
	POSITION pos = m_CharList.GetTailPosition();	// 아래서 부터 출력하여 자연스럽게 겹치기 위해 tail부터 순회
	while (pos)
	{
		pChar = m_CharList.GetPrev(pos);			// 역방향 노드 순회
		pChar->Draw(dc);								// 출력
	}	

	// UI 출력 (해당 좌표를 조정하면 원하는 위치에 재배치)
	for (int i = 0; i < m_nLife; i++)
	{
		m_Life.Draw(dc, i*m_Life.GetWidth() + 10, 10);
	}
	m_Left.Draw(dc, 100, 500);
	m_Right.Draw(dc, 650, 500);

	CPoint cr[] = { {100, 200}, {100, 300}, {650, 200}, {650, 300}, {650, 400} };
	for (int i = 0; i < MAX_CHAR_BMP; i++)
	{
		m_CharRef[i].Draw(dc, cr[i].x, cr[i].y);	// 캐릭터 레퍼런스 비트맵
	}

	// 점수와 시간
	CFont Font, *oldFont;

	Font.CreateFont(FONT_SIZE, FONT_SIZE, 0, 0, FW_DONTCARE, FALSE,
		FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		L"돋움체");

	oldFont = dc.SelectObject(&Font);	

	WCHAR szScore[64], szAC[64], szLevel[64];
	wsprintf(szScore, L"SCORE %04d", m_nScore);
	wsprintf(szAC, L"HIT %02d", m_nAccumHitCount);
	wsprintf(szLevel, L"LEVEL %d", m_nLevel);
	
	dc.SetBkMode(TRANSPARENT);			// 문자열의 배경을 투명처리

	dc.TextOut(10,  60, szScore);
	dc.TextOut(10,  90, szAC);
	dc.TextOut(10, 120, szLevel);

	dc.SelectObject(oldFont);
	Font.DeleteObject();
}

BOOL CPlay::Drop(CPaintDC& dc, CChar::Type type, BOOL bHit)
{
	BOOL bFailed = FALSE;
	CChar* pChar = m_CharList.GetHead();
	// 분류 성공
	if (pChar->GetType() == type)
	{
		m_nScore += m_nLevel;
		if (bHit)
		{
			m_nAccumHitCount++;

			// 누적적중에 따른 난이도 레벨업, 라이프업
			if (m_nAccumHitCount == 10 || m_nAccumHitCount == 20 || m_nAccumHitCount == 30 ||
				m_nAccumHitCount == 40 || m_nAccumHitCount == 50)
			{
				m_nLevel++;				
			} 
			else if (m_nAccumHitCount == 60)
			{			
				m_nAccumHitCount = 0;
				m_nLife++;
			}
		}
		else // 누적적중이 아니면
		{
			m_nLevel = 1;
			m_nAccumHitCount = 0;
		}
		TRACE("Score %d, Life %d, Lev %d, Count %d", m_nScore, m_nLife, m_nLevel, m_nAccumHitCount);

		delete m_CharList.RemoveHead();
		CreateChar(dc);	
	}
	else // 분류실패
	{
		m_nLife--;
		if (m_nLife < 1) bFailed = TRUE;
		TRACE("Life %d", m_nLife);
	}

	return bFailed;
}