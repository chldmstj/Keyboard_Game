#pragma once

#define MAX_CHAR        10
#define MAX_CHAR_BMP	5
#define FONT_SIZE		20
#define FONT_SIZE_BIG	34

#define BMP_PATH	L".\\bmp\\"

// Ÿ��Ʋȭ�� Ŭ����
class CTitle : public CBitmap
{
public:
	CTitle();
	~CTitle();

	void Release();	

	void Load(CPaintDC& dc, CString file);	// ���Ϸ� ���� ��Ʈ�� �ε�
	void Draw(CPaintDC& dc, int x, int y);	// ��Ʈ�� ���


	int	GetWidth() { return m_nWidth; }
	int	GetHeight() { return m_nHeight; }

protected:
	CDC*    m_pMemDC;		// �޸� DC(��Ʈ������)
	int		m_nWidth;
	int		m_nHeight;
};

// ���ӿ���ȭ�� Ŭ����
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

	enum Type { LEFT = 1, RIGHT};		// �̵�Ÿ��

	void Release();

	void Load(CPaintDC& dc, CString file, Type type, int num);
	BOOL Move(int pos);
	void Draw(CPaintDC& dc);
	void Draw(CDC* pDC);
		
	Type GetType() { return m_nType;  }
	int	GetWidth() { return m_nWidth; }
	int	GetHeight() { return m_nHeight; }

protected:
	int		m_nNum;			// ĳ���� ��ȣ	
	Type	m_nType;		// ��, ��
	int		m_nPos;			// ��ġ(0~9)
	int		m_nX;
	int		m_nY;

	CDC*    m_pMemDC;
	int		m_nWidth;
	int		m_nHeight;
};

typedef CList<CChar*, CChar*> CharList;			// ĳ���� ��⿭(������ ����ǰ�, �ϳ��� ������ �߰��� �����Ͽ�����)
// 
class CPlay : public CBitmap
{
public:
	CPlay();
	~CPlay();

	void Init();
	void Release();
	void ReleaseChar();

	void Load(CPaintDC& dc, CString file);		// ��� ��Ʈ�� �ε�
	void LoadUI(CPaintDC& dc);					// UI �ε�
	void LoadChar(CPaintDC& dc);                // ĳ���� �ε�
	void CreateChar(CPaintDC& dc);				// ĳ���� ����
	void Move(CPaintDC& dc);					// �̵�ó��
	void Draw(CPaintDC& dc, int x, int y);		// ���
	BOOL Drop(CPaintDC& dc, CChar::Type type, BOOL bHit);	// ĳ���� �з�(��⿭���� ����)

	int	GetWidth() { return m_nWidth; }
	int	GetHeight() { return m_nHeight; }
	int GetScore() { return m_nScore; }

protected:
	CUI	     m_Life, m_Left, m_Right, m_CharRef[MAX_CHAR_BMP]; // ����, ��, ��, ĳ���ͷ��۷��� ��Ʈ��
	CharList m_CharList;			// ĳ���� ��⿭�� ���Ḯ��Ʈ�� ����
	int		 m_nScore;
	int		 m_nLife;
	int		 m_nLevel;
	int		 m_nAccumHitCount;		// ���� ���߼�

	CDC*    m_pMemDC;
	int		m_nWidth;
	int		m_nHeight;
};