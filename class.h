#pragma once

#define MAX_CHAR        10
#define MAX_CHAR_BMP	5
#define FONT_SIZE		20
#define FONT_SIZE_BIG	34

#define BMP_PATH	L".\\bmp\\"

// 타이틀화면 클래스
class CTitle : public CBitmap
{
public:
	CTitle();
	~CTitle();

	void Release();	

	void Load(CPaintDC& dc, CString file);	// 파일로 부터 비트맵 로드
	void Draw(CPaintDC& dc, int x, int y);	// 비트맵 출력


	int	GetWidth() { return m_nWidth; }
	int	GetHeight() { return m_nHeight; }

protected:
	CDC*    m_pMemDC;		// 메모리 DC(비트맵적재)
	int		m_nWidth;
	int		m_nHeight;
};

// 게임오버화면 클래스
class CGameOver : public CBitmap
{
public:
	CGameOver();
	~CGameOver();

	void Release();

	void Load(CPaintDC& dc, CString file);
	void Draw(CPaintDC& dc, int x, int y);


	int	GetWidth() { return m_nWidth; }
	int	GetHeight() { return m_nHeight; }

protected:
	CDC*    m_pMemDC;
	int		m_nWidth;
	int		m_nHeight;
};

// 
class CUI : public CBitmap
{
public:
	CUI();
	~CUI();

	void Release();

	void Load(CPaintDC& dc, CString file);
	void Draw(CPaintDC& dc, int x, int y);
	void Draw(CDC* pDC, int x, int y);


	int	GetWidth() { return m_nWidth; }
	int	GetHeight() { return m_nHeight; }

protected:
	CDC*    m_pMemDC;
	int		m_nWidth;
	int		m_nHeight;
};

//
class CChar : public CBitmap
{
public:
	CChar();
	~CChar();

	enum Type { LEFT = 1, RIGHT};		// 이동타입

	void Release();

	void Load(CPaintDC& dc, CString file, Type type, int num);
	BOOL Move(int pos);
	void Draw(CPaintDC& dc);
	void Draw(CDC* pDC);
		
	Type GetType() { return m_nType;  }
	int	GetWidth() { return m_nWidth; }
	int	GetHeight() { return m_nHeight; }

protected:
	int		m_nNum;			// 캐릭터 번호	
	Type	m_nType;		// 좌, 우
	int		m_nPos;			// 위치(0~9)
	int		m_nX;
	int		m_nY;

	CDC*    m_pMemDC;
	int		m_nWidth;
	int		m_nHeight;
};

typedef CList<CChar*, CChar*> CharList;			// 캐릭터 대기열(생성후 적재되고, 하나씩 빠지면 추가로 생성하여적재)
// 
class CPlay : public CBitmap
{
public:
	CPlay();
	~CPlay();

	void Init();
	void Release();
	void ReleaseChar();

	void Load(CPaintDC& dc, CString file);		// 배경 비트맵 로드
	void LoadUI(CPaintDC& dc);					// UI 로드
	void LoadChar(CPaintDC& dc);                // 캐릭터 로드
	void CreateChar(CPaintDC& dc);				// 캐릭터 생성
	void Move(CPaintDC& dc);					// 이동처리
	void Draw(CPaintDC& dc, int x, int y);		// 출력
	BOOL Drop(CPaintDC& dc, CChar::Type type, BOOL bHit);	// 캐릭터 분류(대기열에서 삭제)

	int	GetWidth() { return m_nWidth; }
	int	GetHeight() { return m_nHeight; }
	int GetScore() { return m_nScore; }

protected:
	CUI	     m_Life, m_Left, m_Right, m_CharRef[MAX_CHAR_BMP]; // 생명, 좌, 우, 캐릭터레퍼런스 비트맵
	CharList m_CharList;			// 캐릭터 대기열을 연결리스트로 관리
	int		 m_nScore;
	int		 m_nLife;
	int		 m_nLevel;
	int		 m_nAccumHitCount;		// 누적 적중수

	CDC*    m_pMemDC;
	int		m_nWidth;
	int		m_nHeight;
};