
// ChildView.h : CChildView 클래스의 인터페이스
//


#pragma once

#include "class.h"

#define HIT_LIMIT_TIME	1000		// 연속적중시간 (1초 이내)
#define TM_PLAY			1			// 타이머 메시지 ID


// CChildView 창

class CChildView : public CWnd
{
// 생성입니다.
public:
	CChildView();

private:
	void Init(CPaintDC& dc);
	void Title(CPaintDC& dc);
	void Play(CPaintDC& dc);
	void GameOver(CPaintDC& dc);		

	enum MODE { INIT = 0, TITLE, PLAY, GAMEOVER };		// 플레이 진행 

	MODE			m_GameMode;			// 게임모드
	CTitle			m_Title;			// 타이틀화면 클래스(비트맵)
	CGameOver		m_GameOver;			// 게임오버화면 클래스(비트맵)
	CPlay			m_Play;				// 게임진행 클래스
	DWORD			m_dwTimeTick;		// 연속적중시간 체크를 위한 시간저장변수

// 재정의입니다.
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CChildView();

	// 생성된 메시지 맵 함수
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
};

