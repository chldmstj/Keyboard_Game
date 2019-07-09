#pragma once


// GameeView ���Դϴ�.

class GameDlg;  //���� ���̾�α�
class GameeView : public CView
{
	DECLARE_DYNCREATE(GameeView)
	friend class GameDlg;  //����
protected:
	GameeView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~GameeView();
	
public:
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	int lx;
	int ly;
	int rx;
	int ry;
	int top;
	int size;
	int largest;
	int moonSize;
	int fllx[9][4];
	int flly[9][4];
	int frrx[9][4];
	int frry[9][4];
	int colorr[9];
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);


	int t;
	int c;
	

	int m_timecount;
};


