
// ChildView.h : CChildView Ŭ������ �������̽�
//


#pragma once

#include "class.h"

#define HIT_LIMIT_TIME	1000		// �������߽ð� (1�� �̳�)
#define TM_PLAY			1			// Ÿ�̸� �޽��� ID


// CChildView â

class CChildView : public CWnd
{
// �����Դϴ�.
public:
	CChildView();

private:
	void Init(CPaintDC& dc);
	void Title(CPaintDC& dc);
	void Play(CPaintDC& dc);
	void GameOver(CPaintDC& dc);		

	enum MODE { INIT = 0, TITLE, PLAY, GAMEOVER };		// �÷��� ���� 

	MODE			m_GameMode;			// ���Ӹ��
	CTitle			m_Title;			// Ÿ��Ʋȭ�� Ŭ����(��Ʈ��)
	CGameOver		m_GameOver;			// ���ӿ���ȭ�� Ŭ����(��Ʈ��)
	CPlay			m_Play;				// �������� Ŭ����
	DWORD			m_dwTimeTick;		// �������߽ð� üũ�� ���� �ð����庯��

// �������Դϴ�.
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// �����Դϴ�.
public:
	virtual ~CChildView();

	// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
};

