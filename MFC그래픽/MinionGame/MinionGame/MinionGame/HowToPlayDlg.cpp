// HowToPlayDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MinionGame.h"
#include "HowToPlayDlg.h"
#include "afxdialogex.h"


// HowToPlayDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(HowToPlayDlg, CDialogEx)

HowToPlayDlg::HowToPlayDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HOWTOPLAY, pParent)
{

}

HowToPlayDlg::~HowToPlayDlg()
{
}

void HowToPlayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC_GRU, m_ctlPicGru);
}


BEGIN_MESSAGE_MAP(HowToPlayDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// HowToPlayDlg 메시지 처리기입니다.

//화면조절을 위해!--------------------------
BOOL HowToPlayDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();

	//----- 가운데에 창띄우기 -------
	int cx = (GetSystemMetrics(SM_CXSCREEN) / 2 - 435);
	int cy = (GetSystemMetrics(SM_CYSCREEN) / 2 - 525 / 2);  //창을 가운데에 위치시키기 위해

	//----화면크기조절----
	MoveWindow(cx, cy, 870, 525);//위치x,위치y,크기x,크기y
	return TRUE;
}

void HowToPlayDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	
	//----배경화면 가져오기!----
	HBITMAP hbit;
	hbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_GRU));
	m_ctlPicGru.SetBitmap(hbit);  //그루사진
	//-------------------------
}
