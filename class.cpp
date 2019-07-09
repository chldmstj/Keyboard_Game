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
	DeleteObject();				// ��Ʈ�� ����
	if (m_pMemDC)				// �޸�DC ����
	{
		m_pMemDC->DeleteDC();
		delete m_pMemDC;
		m_pMemDC = NULL;
	}	
}

void CTitle::Load(CPaintDC& dc, CString file)
{
	// ���Ϸ� ���� ��Ʈ���� �ε�
	HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, file, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hBitmap) Attach(hBitmap);

	// �޸� DC ���� �� ����
	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(&dc);
	m_pMemDC->SelectObject(this);

	// ��Ʈ�� ũ�� ����
	BITMAP bmpInfo;
	GetBitmap(&bmpInfo);

	m_nWidth = bmpInfo.bmWidth;
	m_nHeight = bmpInfo.bmHeight;
}

void CTitle::Draw(CPaintDC& dc, int x, int y)
{
	// dc�� �̹��� ���
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
	// ��������Ʈ�� ���(����� ���ܵǼ� ���)
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
	m_nPos = ((MAX_CHAR-2 - pos) * 72);	// pos�� 0~9�� ĳ������ ��ġ�� ��Ÿ����. �� ��ġ�� ȭ����ǥ�� ��ȯ�ϴ� ����	
	                                    // ���� ũ�� 72������ �����Ѵ�(������ ���ϰų� �ø����ִ�)
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
	m_nLife = 3;			// �ʱ� ����
	m_nLevel = 1;			// ���� ����
	m_nScore = 0;			// ����
	m_nAccumHitCount = 0;	// �������߼�
}

void CPlay::ReleaseChar()
{
	CChar* pChar;
	POSITION pos = m_CharList.GetHeadPosition();	// ����Ʈ�� ����������� ��� ���� ��� ��ȸ
	while(pos)
	{
		pChar = m_CharList.GetNext(pos);
		delete pChar;								// �޸𸮿��� ����
	}
	m_CharList.RemoveAll();							// ����Ʈ ��� ��� ����
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
	strFile.Format(L"%sLife.bmp", BMP_PATH);			// BMP_PATH�� ��ġ�� ��Ʈ���� �ε�
	m_Life.Load(dc, strFile);
	strFile.Format(L"%sleft.bmp", BMP_PATH);
	m_Left.Load(dc, strFile);
	strFile.Format(L"%sright.bmp", BMP_PATH);
	m_Right.Load(dc, strFile);
	for (int i = 0; i < MAX_CHAR_BMP; i++)				// ĳ���� ���۷��� ��Ʈ�� �ε�(�¿� ��� 5��)
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
	pChar->Load(dc, strFile, (n < 3) ? CChar::LEFT : CChar::RIGHT, n);	// 1~2�̸� LEFT, 3~5�� RIGHT
	m_CharList.AddTail(pChar);	// ����Ʈ�� �߰�
}

void CPlay::Move(CPaintDC& dc)
{
	int posChar=-1;									// ȭ����ǥ�� ����ϱ� ���� ��ġ 0~9
	CChar* pChar;
	POSITION pos = m_CharList.GetHeadPosition();	// ����Ʈ�� ��� ��带 ��ȸ
	while (pos)
	{
		pChar = m_CharList.GetNext(pos);
		pChar->Move(posChar);						// ĳ���� �̵�ó��
		posChar++;
	}
}

void CPlay::Draw(CPaintDC& dc, int x, int y)
{
	// ���
	dc.BitBlt(x, y, m_nWidth, m_nHeight, m_pMemDC, 0, 0, SRCCOPY);

	// �з��� ĳ���� ���
	CChar* pChar;
	POSITION pos = m_CharList.GetTailPosition();	// �Ʒ��� ���� ����Ͽ� �ڿ������� ��ġ�� ���� tail���� ��ȸ
	while (pos)
	{
		pChar = m_CharList.GetPrev(pos);			// ������ ��� ��ȸ
		pChar->Draw(dc);								// ���
	}	

	// UI ��� (�ش� ��ǥ�� �����ϸ� ���ϴ� ��ġ�� ���ġ)
	for (int i = 0; i < m_nLife; i++)
	{
		m_Life.Draw(dc, i*m_Life.GetWidth() + 10, 10);
	}
	m_Left.Draw(dc, 100, 500);
	m_Right.Draw(dc, 650, 500);

	CPoint cr[] = { {100, 200}, {100, 300}, {650, 200}, {650, 300}, {650, 400} };
	for (int i = 0; i < MAX_CHAR_BMP; i++)
	{
		m_CharRef[i].Draw(dc, cr[i].x, cr[i].y);	// ĳ���� ���۷��� ��Ʈ��
	}

	// ������ �ð�
	CFont Font, *oldFont;

	Font.CreateFont(FONT_SIZE, FONT_SIZE, 0, 0, FW_DONTCARE, FALSE,
		FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		L"����ü");

	oldFont = dc.SelectObject(&Font);	

	WCHAR szScore[64], szAC[64], szLevel[64];
	wsprintf(szScore, L"SCORE %04d", m_nScore);
	wsprintf(szAC, L"HIT %02d", m_nAccumHitCount);
	wsprintf(szLevel, L"LEVEL %d", m_nLevel);
	
	dc.SetBkMode(TRANSPARENT);			// ���ڿ��� ����� ����ó��

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
	// �з� ����
	if (pChar->GetType() == type)
	{
		m_nScore += m_nLevel;
		if (bHit)
		{
			m_nAccumHitCount++;

			// �������߿� ���� ���̵� ������, ��������
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
		else // ���������� �ƴϸ�
		{
			m_nLevel = 1;
			m_nAccumHitCount = 0;
		}
		TRACE("Score %d, Life %d, Lev %d, Count %d", m_nScore, m_nLife, m_nLevel, m_nAccumHitCount);

		delete m_CharList.RemoveHead();
		CreateChar(dc);	
	}
	else // �з�����
	{
		m_nLife--;
		if (m_nLife < 1) bFailed = TRUE;
		TRACE("Life %d", m_nLife);
	}

	return bFailed;
}