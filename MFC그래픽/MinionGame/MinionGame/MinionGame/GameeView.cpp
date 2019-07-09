// GameeView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MinionGame.h"


#include "GameDoc.h"
#include "GameeView.h"


#include <math.h> //�����ռ��� ����
#include <atlimage.h> //CImage�� ����

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// GameeView

IMPLEMENT_DYNCREATE(GameeView, CView)

GameeView::GameeView()
{

	lx = 0;
	ly = 0;
	rx = 0;
	ry = 0;
	top = 0;
	size = 0;
	largest = 0;
	moonSize = 0;
	t = 0;
	c = 0;

	m_timecount = 0;
}

GameeView::~GameeView()
{
}

BEGIN_MESSAGE_MAP(GameeView, CView)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_CHAR()
END_MESSAGE_MAP()


// GameeView �׸����Դϴ�.

void GameeView::OnDraw(CDC* pDC)
{	

	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
	//���ȭ��-------------------
	CString strImagePath = _T("minion.png");
	CImage Image;

	HRESULT hResult = Image.Load(strImagePath);

	if (FAILED(hResult)) {
		CString strtmp = _T("ERROR: Failed to Load");
		strtmp += strImagePath + _T("\n");
		TRACE(strtmp);
		return;
	}
	Image.TransparentBlt(pDC->m_hDC, 0, 0, Image.GetWidth(), Image.GetHeight(), RGB(255, 0, 0));
	//-----------------------------
	
	
	//SCORE------------------------
	CRect rect;
	GetClientRect(&rect);
	CFont font;
	font.CreatePointFont(200, _T("����ü"));
	pDC->SetTextColor(RGB(255, 255, 0));
	pDC->SetBkColor(RGB(0, 0, 0));
	pDC->SelectObject(&font);


	//--------LARGEST:
	CString LargestMessage;
	LargestMessage.Format(_T("LARGEST : %d"), largest);
	pDC->DrawText(LargestMessage, rect, DT_TOP | DT_CENTER);

	//---------SIZE:
	CString SizeMessage;
	SizeMessage.Format(_T("SIZE : %d"), size);
	pDC->DrawText(SizeMessage, rect, DT_TOP | DT_LEFT);

	//-------------�����̴� ��----------------//
	
	ly = ry - moonSize;
	rx = lx + moonSize;  

	pDC->SetROP2(R2_COPYPEN);		//���׸��� �����ϰ� ���� �׷����� �׸��� ���

	CBrush brush, *oldbrush;

	brush.CreateSolidBrush(RGB(204, 204, 0));  //���λ�
	oldbrush = pDC->SelectObject(&brush); //����ĥ�ϱ�

	pDC->Ellipse(lx, ly, rx, ry);  //�����̴� ��

	pDC->SelectObject(oldbrush);
	brush.DeleteObject();      //����ĥ�ϱ�



	 //--------�������¿�------------

	if (frry[t][c] == ly) {
		if (largest == size) {
			size++;
			largest++;
		}
		else size++;

		moonSize += 5;
	}
	for (int i = 0; i < 9; i++) {
		pDC->SetROP2(R2_COPYPEN);
		if (colorr[i] == 0) {
			brush.CreateSolidBrush(RGB(204, 204, 0)); //���λ�
			oldbrush = pDC->SelectObject(&brush);
			pDC->Ellipse(fllx[i][0], flly[i][0], frrx[i][0], frry[i][0]);
		}
		else if (colorr[i] == 1) {
			brush.CreateSolidBrush(RGB(0, 0, 153)); // �Ķ���	
			oldbrush = pDC->SelectObject(&brush);
			pDC->Ellipse(fllx[i][1], flly[i][1], frrx[i][1], frry[i][1]);
		}
		else if (colorr[i] == 2) {
			brush.CreateSolidBrush(RGB(255, 102, 153)); //��ȫ��
			oldbrush = pDC->SelectObject(&brush);
			pDC->Ellipse(fllx[i][2], flly[i][2], frrx[i][2], frry[i][2]);
		}
		else if (colorr[i] == 3) {
			brush.CreateSolidBrush(RGB(153, 51, 204));  //�����
			oldbrush = pDC->SelectObject(&brush);
			pDC->Ellipse(fllx[i][3], flly[i][3], frrx[i][3], frry[i][3]);
		}
		pDC->SelectObject(oldbrush);
		brush.DeleteObject();
	}

}


// GameeView �����Դϴ�.

#ifdef _DEBUG
void GameeView::AssertValid() const
{
	CView::AssertValid();
}

//#ifndef _WIN32_WCE
void GameeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
//#endif



#endif //_DEBUG

// GameeView �޽��� ó�����Դϴ�.


int GameeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	moonSize = 60;
	lx = 0;
	ry = 450;
	ly = ry- moonSize;
	rx = lx + moonSize;		//�����̴¿�(�� �Ʒ� ��ġ�ϰ� �Ϸ�����)

	size = 3;     //1size�� 5moonSize
	largest = 3;

	//�ѹ��� ���̴� ���� ���� //
	SetTimer(0, 8500, FALSE);
	SetTimer(1, 7000, FALSE);
	SetTimer(2, 9700, FALSE);
	SetTimer(3, 8900, FALSE);
	SetTimer(4, 6100, FALSE);
	SetTimer(5, 8400, FALSE);
	SetTimer(6, 7100, FALSE);
	SetTimer(7, 8100, FALSE);
	SetTimer(8, 9100, FALSE);

	//�����������ϱ� //
	SetTimer(10, 16, FALSE);  //SetTimer(timerID, �ӵ�ms , ȣ��)
	
	return 0;
}


void GameeView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	if (nIDEvent == 10) {  // �� ����߸���
		//m_timecount = GetTickCount();
		for (int j = 0; j < 9; j++) {
			for (int i = 0; i < 4; i++) {
				flly[j][i] = flly[j][i] + 25;
				frry[j][i] = frry[j][i] + 25;
			}
		}
		Invalidate();
		for (int j = 0; j < 9; j++) {
			for (int i = 0;i<4;i++) {
				if (frry[j][i] == ly) {
					if (i == 0) {
						if (frrx[j][i] > lx && fllx[j][i] < rx) {  //���� ���� ��
							if (largest == size) {
								size++;
								largest++;
							}
							else size++;

							moonSize += 5;
							Invalidate();
						}
					}
					else {
						if (frrx[j][i] > lx && fllx[j][i] < rx) {  //���� ���� ��
							//moonSize = moonSize - 5;
							//size = size - 1;
						}
					}

				}

			}
		}
	}

	else {
		//---- �� ���� -----//
		srand((unsigned int)(time(NULL))); //���� ������ ����
		colorr[nIDEvent] = rand() % 4; // int random = (rand() % (end_number - start_number + 1)) + start_number;

		//------�� ��ġ------//
		srand((unsigned int)(time(NULL))); //���� ������ ����
		for (int i = 0; i < 4; i++) {
			top = rand() % ((nIDEvent + 1) * 100); // int random = (rand() % (end_number - start_number + 1)) + start_number;
			fllx[nIDEvent][i] = top + 0;  //top : �������� ������ ��ġ�� �ٸ��� �Ϸ��� ���� ����
			flly[nIDEvent][i] = 0;
			frrx[nIDEvent][i] = top + 50;
			frry[nIDEvent][i] = 50;
			////////////////////////////////////////////////////
			/*if (450-frry[nIDEvent][i]-m_timecount*25 == ly) {
				if (i == 0) {
					if (frrx[nIDEvent][i] > lx && fllx[nIDEvent][i] < rx) {  //���� ���� ��
						if (largest == size) {
							size++;
							largest++;
						}
						else size++;

						moonSize += 5;
						Invalidate();
					}
				}
				else {
					if (frrx[nIDEvent][i] > lx && fllx[nIDEvent][i] < rx) {  //���� ���� ��
						moonSize = moonSize - 5;
						size = size - 1;
					}
				}
				
			}*/
			

		}
		
		if (size == 0) {
			KillTimer(10);
			AfxMessageBox(_T("Game Over"), MB_OK);
		}
	}
	
	


	CView::OnTimer(nIDEvent);
}


void GameeView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	RECT CurRC;
	::GetClientRect(this->m_hWnd, &CurRC);//CurRC.top, CurRC.bottom, CurRC.left, CurRC.right

	if (lx < 0) {
		lx = CurRC.right - moonSize;
		rx = CurRC.right;
	}

	if (rx > CurRC.right) {
		lx = 0;
		rx = moonSize;
	}


	switch (nChar) {
	case VK_LEFT:
		lx = lx - 30;
		rx = rx - 30;
		break;
	case VK_RIGHT:
		lx = lx + 30;
		rx = rx + 30;
		break;
		
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

//�����Ӿ��ֱ�!
BOOL GameeView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	TRACE("OnEraseBkgnd()\n");
	return FALSE;
}

